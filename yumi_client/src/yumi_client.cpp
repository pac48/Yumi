#include "yumi_client/yumi_client.hpp"


namespace yumi_client {

    namespace conversions {

        std_msgs::msg::Float32 get_msg(const yumi_packets::ROS_msg_gripper_force &data_packet) {
            std_msgs::msg::Float32 msg;
            msg.data = data_packet.force;

            return msg;
        }

        std_msgs::msg::Float32 get_msg(const yumi_packets::ROS_msg_gripper_position &data_packet) {
            std_msgs::msg::Float32 msg;
            msg.data = data_packet.position;

            return msg;
        }

        std_msgs::msg::Float32MultiArray get_msg(const yumi_packets::ROS_msg_joint_data &data_packet) {
            std_msgs::msg::Float32MultiArray msg;
            msg.data.reserve(7);
            for (int i = 0; i < 7; i++) {
                msg.data[i] = data_packet.joints[i];
            }

            return msg;
        }

        AllROSMessages get_msg(const yumi_packets::ROS_msgs &data_packet) {
            AllROSMessages msgs;
            msgs.joint_position_msg = get_msg(data_packet.joint_position_msg);
            msgs.joint_torque_msg = get_msg(data_packet.joint_torque_msg);
            msgs.gripper_position_msg = get_msg(data_packet.gripper_position_msg);
            msgs.gripper_force_msg = get_msg(data_packet.gripper_force_msg);

            return msgs;
        }
    }


    YumiClientNode::YumiClientNode(const std::string &name)
            : rclcpp::Node(name) {

        // get parameters
        param_listener = std::make_shared<yumi_client::ParamListener>(
                get_node_parameters_interface());
        params_ = param_listener->get_params();

        gripper_force_command_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
                params_.gripper_force_command_topic, 10,
                std::bind(&YumiClientNode::gripper_force_command_callback, this, std::placeholders::_1));

        joint_state_publisher_ = this->create_publisher<sensor_msgs::msg::JointState>(params_.joint_state_topic, 10);

        //socket creation
        RCLCPP_INFO(get_logger(), "attempting to connect to %s:%d", params_.ip_address.c_str(),
                    params_.port_number);
        socket_.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(params_.ip_address),
                                                       params_.port_number));
        RCLCPP_INFO(get_logger(), "Connected!");
    }

    YumiClientNode::~YumiClientNode() {
        socket_.close();
    }

    AllROSMessages YumiClientNode::get_latest_msgs() {
        int packet_size = sizeof(yumi_packets::ROS_msgs);
        boost::asio::read(socket_, receive_buffer_, boost::asio::transfer_exactly(packet_size), error_);
        if (error_ && error_ != boost::asio::error::eof) {
            RCLCPP_ERROR(get_logger(), "receive failed: %s", error_.message().c_str());
        } else {
            auto const *data = boost::asio::buffer_cast<yumi_packets::ROS_msgs const *>(
                    receive_buffer_.data());
            latest_msgs_ = conversions::get_msg(*data);
        }
        receive_buffer_.consume(packet_size);
        return latest_msgs_;
    }

    void YumiClientNode::publish_latest_msgs() {
        sensor_msgs::msg::JointState joint_state_msg;

        auto joints_pos = latest_msgs_.joint_position_msg.data;
        auto joints_torque = latest_msgs_.joint_torque_msg.data;
        if (joints_pos.size() != joints_pos.size() || joints_pos.size() != params_.joint_names.size()) {
            RCLCPP_ERROR(get_logger(), "size mismatch between joint_names parameter and received values");
            return;
        }
        for (int i = 0; i < params_.joint_names.size(); i++) {
            joint_state_msg.name.push_back(params_.joint_names[i]);
            joints_pos[i] *= (M_PI / 180.0);
            joint_state_msg.position.push_back(joints_pos[i]);
            joint_state_msg.effort.push_back(joints_torque[i]);
        }

        joint_state_msg.header.stamp = get_clock()->now();
        joint_state_publisher_->publish(joint_state_msg);
    }

    void YumiClientNode::gripper_force_command_callback(const std_msgs::msg::Float32::SharedPtr msg) {
        yumi_packets::ROS_msg_gripper_force data_packet;
        data_packet.force = msg->data;
        write_buffer_.assign(data_packet);
        boost::system::error_code error;
        socket_.write_some(boost::asio::buffer(&write_buffer_, sizeof(yumi_packets::ROS_msg_gripper_force)), error);
    }


}