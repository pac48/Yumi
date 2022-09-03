#include "yumi_hardware/yumi_hardware.hpp"
#include <string>
#include <vector>

namespace yumi_hardware {

    bool connect_egm(std::shared_ptr<abb::egm::EGMControllerInterface> egm_interface, boost::thread_group &thread_group,
                     boost::asio::io_service &io_service) {
        if (!egm_interface->isInitialized()) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"),
                         "EGM interface failed to initialize (e.g. due to port already bound)");
            return false;
        }
        // Spin up a thread to run the io_service.
        thread_group.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));

        RCLCPP_INFO(rclcpp::get_logger("YumiHardwareInterface"),
                    "Wait for an  EGM communication session to start...");
        bool wait = true;
        while (wait) {
            if (egm_interface->isConnected()) {
                if (egm_interface->getStatus().rapid_execution_state() ==
                    abb::egm::wrapper::Status_RAPIDExecutionState_RAPID_UNDEFINED) {
                    RCLCPP_WARN(rclcpp::get_logger("YumiHardwareInterface"),
                                "RAPID execution state is UNDEFINED (might happen first time after joy_pygame start/restart). Try to restart the RAPID program.");
                } else {
                    wait = egm_interface->getStatus().rapid_execution_state() !=
                           abb::egm::wrapper::Status_RAPIDExecutionState_RAPID_RUNNING;
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            RCLCPP_WARN(rclcpp::get_logger("YumiHardwareInterface"), "waiting");
        }
        return true;
    }


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

        // set initial values
        joint_position_command_[0] = 0.01; // mm
        joint_position_command_[1] = 0.01; // mm

        for (const auto &joint: info_.joints) {
            for (const auto &interface: joint.state_interfaces) {
                joint_state_interfaces_[interface.name].push_back(joint.name);
            }
            for (const auto &interface: joint.command_interfaces) {
                joint_command_interfaces_[interface.name].push_back(joint.name);
            }
        }

        if (joint_state_interfaces_["position"].size() != joint_state_interfaces_["velocity"].size()) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"),
                         "All joints must have a position and velocity state interface defined in the URDF");
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
        } catch (boost::system::system_error &error) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "Failed to connect with error message: %s",
                         error.what());
            return CallbackReturn::ERROR;
        }


        // Create EGM configurations.
        configuration_.use_velocity_outputs = true;

        egm_interface_l_ = std::make_shared<abb::egm::EGMControllerInterface>(io_service_egm_l_, egm_port_l,
                                                                              configuration_);
        if (!connect_egm(egm_interface_l_, thread_group_l_, io_service_egm_l_)) {
            return CallbackReturn::ERROR;

        }

        egm_interface_r_ = std::make_shared<abb::egm::EGMControllerInterface>(io_service_egm_r_, egm_port_r,
                                                                              configuration_);

        if (!connect_egm(egm_interface_r_, thread_group_r_, io_service_egm_r_)) {
            return CallbackReturn::ERROR;
        }

        return CallbackReturn::SUCCESS;
    }

    std::vector<hardware_interface::StateInterface> YumiSystem::export_state_interfaces() {
        std::vector<hardware_interface::StateInterface> state_interfaces;

        int ind = 0;
        for (const auto &joint_name: joint_state_interfaces_["position"]) {
            state_interfaces.emplace_back(joint_name, "position", &joint_position_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_state_interfaces_["velocity"]) {
            state_interfaces.emplace_back(joint_name, "velocity", &joint_velocities_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_state_interfaces_["effort"]) {
            state_interfaces.emplace_back(joint_name, "effort", &joint_effort_[ind++]);
        }

        return state_interfaces;
    }

    std::vector<hardware_interface::CommandInterface> YumiSystem::export_command_interfaces() {
        std::vector<hardware_interface::CommandInterface> command_interfaces;

        int ind = 0;
        for (const auto &joint_name: joint_command_interfaces_["position"]) {
            command_interfaces.emplace_back(joint_name, "position", &joint_position_command_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_command_interfaces_["velocity"]) {
            command_interfaces.emplace_back(joint_name, "velocity", &joint_velocities_command_[ind++]);
        }

        ind = 0;
        for (const auto &joint_name: joint_command_interfaces_["effort"]) {
            command_interfaces.emplace_back(joint_name, "effort", &joint_effort_command_[ind++]);
        }

        return command_interfaces;
    }

    return_type YumiSystem::read(const rclcpp::Time & /*time*/, const rclcpp::Duration &period) {
        int packet_size = sizeof(yumi_packets::receive_ROS_msgs);

        boost::asio::read(state_socket_r_, receive_buffer_, boost::asio::transfer_exactly(packet_size), error_);
        if (error_ && error_ != boost::asio::error::eof) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "receive failed: %s", error_.message().c_str());
            return return_type::ERROR;
        }
        yumi_packets::receive_ROS_msgs packets_r = *boost::asio::buffer_cast<yumi_packets::receive_ROS_msgs const *>(
                receive_buffer_.data());
        receive_buffer_.consume(packet_size);

        boost::asio::read(state_socket_l_, receive_buffer_, boost::asio::transfer_exactly(packet_size), error_);
        if (error_ && error_ != boost::asio::error::eof) {
            RCLCPP_ERROR(rclcpp::get_logger("YumiHardwareInterface"), "receive failed: %s", error_.message().c_str());
            return return_type::ERROR;
        }
        yumi_packets::receive_ROS_msgs packets_l = *boost::asio::buffer_cast<yumi_packets::receive_ROS_msgs const *>(
                receive_buffer_.data());
        receive_buffer_.consume(packet_size);


        double dt = period.seconds();
        for (int i = 0; i < 7; i++) {
            double joint_pos = (M_PI / 180.0) * packets_r.joint_position_msg.joints[i];
            joint_velocities_[i] = (joint_pos - joint_position_[i]) / dt;
            joint_position_[i] = joint_pos;
            joint_effort_[i] = packets_r.joint_torque_msg.joints[i];
        }

        for (int i = 7; i < 7 + 7; i++) {
            double joint_pos = (M_PI / 180.0) * packets_l.joint_position_msg.joints[i - 7];
            joint_velocities_[i] = (joint_pos - joint_position_[i]) / dt;
            joint_position_[i] = joint_pos;
            joint_effort_[i] = packets_l.joint_torque_msg.joints[i - 7];
        }
        joint_position_[14] = (1.0 / 1000.0) * packets_r.gripper_position_msg.position;
        joint_effort_[14] = packets_r.gripper_force_msg.force;
        joint_position_[15] = (1.0 / 1000.0) * packets_l.gripper_position_msg.position;
        joint_effort_[15] = packets_l.gripper_force_msg.force;

        return return_type::OK;
    }

    void write_egm(const double reference[7],
                   std::shared_ptr<abb::egm::EGMControllerInterface> egm_interface, abb::egm::wrapper::Input input,
                   abb::egm::wrapper::Joints initial_velocity,
                   abb::egm::wrapper::Joints initial_velocity2,
                   abb::egm::wrapper::Output output) {
        // Wait for a new EGM message from the EGM client (with a timeout of 500 ms).
        if (egm_interface->waitForMessage(50)) {
            // Read the message received from the EGM client.
            egm_interface->read(&input);
            if (output.mutable_robot()->mutable_joints()->mutable_velocity()->values_size() != 6) {
                output.Clear();
                initial_velocity.CopyFrom(input.feedback().robot().joints().velocity());
                output.mutable_robot()->mutable_joints()->mutable_velocity()->CopyFrom(initial_velocity);
                initial_velocity2.CopyFrom(input.feedback().external().joints().velocity());
                output.mutable_external()->mutable_joints()->mutable_velocity()->CopyFrom(initial_velocity2);
            }

            if (output.mutable_robot()->mutable_joints()->mutable_velocity()->values_size() == 6) {
                for (int i = 0; i < 7; i++) {
                    double r = reference[i] * 180.0 / M_PI;
                    if (i < 2) {
                        output.mutable_robot()->mutable_joints()->mutable_velocity()->set_values(i, r);
                    } else if (i > 2) {
                        output.mutable_robot()->mutable_joints()->mutable_velocity()->set_values(i - 1, r); \

                    } else {
                        output.mutable_external()->mutable_joints()->mutable_velocity()->set_values(0, r);
                    }                }
                // Write references back to the EGM client.
                egm_interface->write(output);
            }

        }
    }

    void write_gripper_force_command(double value, boost::array<yumi_packets::ROS_msg_gripper_force, 1> write_buffer,
                                     boost::asio::ip::tcp::socket &socket) {
        yumi_packets::ROS_msg_gripper_force data_packet;
        data_packet.force = value;
        write_buffer.assign(data_packet);
        boost::system::error_code error;
        socket.write_some(boost::asio::buffer(&write_buffer, sizeof(yumi_packets::ROS_msg_gripper_force)), error);
    }

    void write_gripper_position_command(double value, boost::array<yumi_packets::send_ROS_msgs, 1>& write_buffer,
                                     boost::asio::ip::tcp::socket &socket) {
        yumi_packets::send_ROS_msgs data_packet;
        data_packet.gripper_position_msg.position = 1000*value; //mm
        write_buffer.assign(data_packet);
        boost::system::error_code error;
        socket.write_some(boost::asio::buffer(&write_buffer, sizeof(yumi_packets::send_ROS_msgs)), error);
    }

    return_type YumiSystem::write(const rclcpp::Time & time, const rclcpp::Duration &) {
        double reference[7];
        for (int i = 0; i < 7; i++) {
            auto joint = info_.joints[i];
            double joint_vel = joint_velocities_command_[i];
            reference[i] = joint_vel;
        }
        write_egm(reference, egm_interface_l_, input_,
                  initial_velocity_,
                  initial_velocity2_,
                  output_);

        for (int i = 7; i < 7 + 7; i++) {
            auto joint = info_.joints[i];
            double joint_vel = joint_velocities_command_[i];
            reference[i - 7] = joint_vel;
        }
        write_egm(reference, egm_interface_r_, input_,
                  initial_velocity_,
                  initial_velocity2_,
                  output_);

        double gripper_position_r = joint_position_command_[0];
        if (time.seconds() - gripper_last_update_ > 1.0 && gripper_position_r != gripper_position_r_old_) {
            write_gripper_position_command(gripper_position_r, write_buffer_, motion_socket_r_);
            gripper_last_update_ = time.seconds();
            gripper_position_r_old_ = gripper_position_r;
        }

        double gripper_position_l = joint_position_command_[1];
        if (time.seconds() - gripper_last_update_ > 1.0 && gripper_position_l != gripper_position_l_old_) {
            write_gripper_position_command(gripper_position_l, write_buffer_, motion_socket_l_);
            gripper_last_update_ = time.seconds();
            gripper_position_l_old_ = gripper_position_l;
        }


        return return_type::OK;
    }

}  // namespace yumi_hardware

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(yumi_hardware::YumiSystem, hardware_interface::SystemInterface)
