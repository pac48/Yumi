#include "yumi_client_parameters.hpp"
#include "yumi_packets/yumi_packets.hpp"
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>


namespace yumi_client {
    struct AllROSMessages {
        std_msgs::msg::Float32MultiArray joint_position_msg;
        std_msgs::msg::Float32MultiArray joint_torque_msg;
        std_msgs::msg::Float32 gripper_position_msg;
        std_msgs::msg::Float32 gripper_force_msg;
    };

    class YumiClientNode : public rclcpp::Node {
    public:
        YumiClientNode(const std::string &name);

        ~YumiClientNode();

        AllROSMessages get_latest_msgs();

        void publish_latest_msgs();

    private:
        void gripper_force_command_callback(const std_msgs::msg::Float32::SharedPtr msg);

        // ROS types
        rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr gripper_force_command_subscription_;
        rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_publisher_;
        AllROSMessages latest_msgs_;

        // tcp connection
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket read_socket_ = boost::asio::ip::tcp::socket(io_service);
        boost::asio::ip::tcp::socket write_socket_ = boost::asio::ip::tcp::socket(io_service);
        boost::array<yumi_packets::ROS_msg_gripper_force, 1> write_buffer_;
        boost::asio::streambuf receive_buffer_;
        boost::system::error_code error_;

        // parameters
        std::shared_ptr<ParamListener> param_listener;
        Params params_;
    };

}