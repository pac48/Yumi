#include "yumi_hardware/yumi_hardware.hpp"
#include <string>
#include <vector>

namespace yumi_hardware {


    CallbackReturn YumiSystem::on_init(const hardware_interface::HardwareInfo &info) {
        if (hardware_interface::SystemInterface::on_init(info) != CallbackReturn::SUCCESS) {
            return CallbackReturn::ERROR;
        }

        // allocate memory to store all interfaces
        joint_position_.assign(info_.joints.size(), 0);
        joint_velocities_.assign(info_.joints.size(), 0);
        joint_effort_.assign(info_.joints.size(), 0);
        joint_position_command_.assign(info_.joints.size(), 0);
        joint_velocities_command_.assign(info_.joints.size(), 0);
        joint_effort_command_.assign(info_.joints.size(), 0);

        for (const auto &joint: info_.joints) {
            for (const auto &interface: joint.state_interfaces) {
                joint_interfaces[interface.name].push_back(joint.name);
            }
        }

        if (joint_interfaces["position"].size() != joint_interfaces["velocity"].size()){
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "All joints must have a position and velocity interface defined in the URDF");
            return CallbackReturn::ERROR;
        }

        // yumi hardware parameters
        std::string robot_ip = info_.hardware_parameters["robot_ip"];
        int state_server_port_l = std::stoi(info_.hardware_parameters["state_server_port_l"]);
        int state_server_port_r = std::stoi(info_.hardware_parameters["state_server_port_r"]);
        int motion_server_port_l = std::stoi(info_.hardware_parameters["motion_server_port_l"]);
        int motion_server_port_r = std::stoi(info_.hardware_parameters["motion_server_port_r"]);
        int egm_port_l = std::stoi(info_.hardware_parameters["egm_port_l"]);
        int egm_port_r = std::stoi(info_.hardware_parameters["egm_port_r"]);

        //socket creation
        try {
            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"), "attempting to connect to left state server %s:%d",
                        robot_ip.c_str(),
                        state_server_port_l);
            state_socket_l_.connect(
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(robot_ip),
                                                   state_server_port_l));
            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"), "Connected to left state server!");

            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"),
                        "attempting to connect to left motion server %s:%d",
                        robot_ip.c_str(),
                        motion_server_port_l);
            motion_socket_l_.connect(
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(robot_ip),
                                                   motion_server_port_l));
            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"), "Connected to left motion server!");

            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"),
                        "attempting to connect to right state server %s:%d",
                        robot_ip.c_str(),
                        state_server_port_r);
            state_socket_r_.connect(
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(robot_ip),
                                                   state_server_port_r));
            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"), "Connected to right state server!");

            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"),
                        "attempting to connect to right motion server %s:%d",
                        robot_ip.c_str(),
                        motion_server_port_r);
            motion_socket_r_.connect(
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(robot_ip),
                                                   motion_server_port_r));
            RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"), "Connected to right motion server!");
        } catch (boost::system::system_error& error){
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "Failed to connect with error message: %s", error.what());
            return CallbackReturn::ERROR;
        }


        // Boost components for managing asynchronous UDP socket(s).
        boost::thread_group thread_group_l;
        boost::thread_group thread_group_r;

        // Create EGM configurations.
        abb::egm::BaseConfiguration configuration;
        configuration.use_velocity_outputs = true;

        egm_interface_l = std::make_shared<abb::egm::EGMControllerInterface>(io_service_egm_l_, egm_port_l, configuration);
        if(!egm_interface_l->isInitialized())
        {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "EGM interface failed to initialize (e.g. due to port already bound)");
            return CallbackReturn::ERROR;
        }
        // Spin up a thread to run the io_service.
        thread_group_l.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_egm_l_));

        egm_interface_r = std::make_shared<abb::egm::EGMControllerInterface>(io_service_egm_r_, egm_port_r, configuration);
        if(!egm_interface_r->isInitialized())
        {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "EGM interface failed to initialize (e.g. due to port already bound)");
            return CallbackReturn::ERROR;
        }
        // Spin up a thread to run the io_service.
        thread_group_r.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_egm_r_));

        return CallbackReturn::SUCCESS;
    }

    std::vector<hardware_interface::StateInterface> YumiSystem::export_state_interfaces() {
        std::vector<hardware_interface::StateInterface> state_interfaces;

        int ind = 0;
        for (const auto &joint_name: joint_interfaces["position"]) {
            state_interfaces.emplace_back(joint_name, "position", &joint_position_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_interfaces["velocity"]) {
            state_interfaces.emplace_back(joint_name, "velocity", &joint_velocities_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_interfaces["effort"]) {
            state_interfaces.emplace_back(joint_name, "effort", &joint_effort_[ind++]);
        }

        return state_interfaces;
    }

    std::vector<hardware_interface::CommandInterface> YumiSystem::export_command_interfaces() {
        std::vector<hardware_interface::CommandInterface> command_interfaces;

        int ind = 0;
        for (const auto &joint_name: joint_interfaces["position"]) {
            command_interfaces.emplace_back(joint_name, "position", &joint_position_command_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_interfaces["velocity"]) {
            command_interfaces.emplace_back(joint_name, "velocity", &joint_velocities_command_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_interfaces["effort"]) {
            command_interfaces.emplace_back(joint_name, "effort", &joint_effort_command_[ind++]);
        }

        return command_interfaces;
    }

    return_type YumiSystem::read(const rclcpp::Time & /*time*/, const rclcpp::Duration &period) {
        int packet_size = sizeof(yumi_packets::ROS_msgs);

        boost::asio::read(state_socket_l_, receive_buffer_, boost::asio::transfer_exactly(packet_size), error_);
        if (error_ && error_ != boost::asio::error::eof) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "receive failed: %s", error_.message().c_str());
            return return_type::ERROR;
        }
        yumi_packets::ROS_msgs packets_l = *boost::asio::buffer_cast<yumi_packets::ROS_msgs const *>(
                    receive_buffer_.data());
        receive_buffer_.consume(packet_size);

        boost::asio::read(state_socket_r_, receive_buffer_, boost::asio::transfer_exactly(packet_size), error_);
        if (error_ && error_ != boost::asio::error::eof) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "receive failed: %s", error_.message().c_str());
            return return_type::ERROR;
        }
        yumi_packets::ROS_msgs packets_r = *boost::asio::buffer_cast<yumi_packets::ROS_msgs const *>(
                receive_buffer_.data());
        receive_buffer_.consume(packet_size);

        double dt = period.seconds();
        for (int i = 0; i < 7; i++) {
            auto joint = info_.joints[i];
            double joint_pos = packets_l.joint_position_msg.joints[i];
            joint_velocities_[i] = (joint_pos-joint_position_[i])/dt;
            joint_position_[i] = joint_pos;
            joint_effort_[i] = packets_l.joint_torque_msg.joints[i];
        }
        joint_position_[7] = packets_l.gripper_position_msg.position;
        joint_effort_[7] = packets_l.gripper_force_msg.force;

        for (int i = 8; i < 8+7; i++) {
            auto joint = info_.joints[i];
            double joint_pos = packets_r.joint_position_msg.joints[i-8];
            joint_velocities_[i] = (joint_pos-joint_position_[i-8])/dt;
            joint_position_[i] = joint_pos;
            joint_effort_[i] = packets_r.joint_torque_msg.joints[i-8];
        }
        joint_position_[15] = packets_l.gripper_position_msg.position;
        joint_effort_[15] = packets_l.gripper_force_msg.force;

        return return_type::OK;
    }

    return_type YumiSystem::write(const rclcpp::Time &, const rclcpp::Duration &) {
        return return_type::OK;
    }

}  // namespace yumi_hardware

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(yumi_hardware::YumiSystem, hardware_interface::SystemInterface)
