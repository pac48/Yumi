#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <std_msgs/msg/float32.hpp>
#include "rclcpp/rclcpp.hpp"
#include "string"
#include "yumi_packets/yumi_packets.hpp"
#include "motion_client_node_parameters.hpp"


namespace motion_client{


class MotionClientNode : public rclcpp::Node {
public:
    MotionClientNode(const std::string& name, boost::asio::ip::tcp::socket& socket)
            : rclcpp::Node(name)
    {
        socket_ = &socket;
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
                "gripper_command_L", 10, std::bind(&MotionClientNode::topic_callback, this, std::placeholders::_1));

        //socket creation
        param_listener = std::make_shared<motion_client::ParamListener>(
                get_node_parameters_interface());
        params_ = param_listener->get_params();
        RCLCPP_INFO(get_logger(), "attempting to connect to %s:%d", params_.ip_address.c_str(), params_.port_number);
        socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(params_.ip_address), params_.port_number));
        RCLCPP_INFO(get_logger(), "Connected!");
    }


    std_msgs::msg::Float32 get_latest_msg(){
        return latest_msg_;
    }

    void write_command(){
        yumi_packets::ROS_msg_gripper_force msgs;
        msgs.force = get_latest_msg().data;
        buffer_.assign(msgs);
        boost::asio::streambuf receive_buffer;
        boost::system::error_code error;
        socket_->write_some(boost::asio::buffer(&buffer_, 8), error);

    }

private:
    void topic_callback(const std_msgs::msg::Float32::SharedPtr msg) {
        latest_msg_ = *msg;
        write_command();
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
    std_msgs::msg::Float32 latest_msg_;
    boost::array<yumi_packets::ROS_msg_gripper_force , 1> buffer_;
    boost::asio::ip::tcp::socket* socket_;
    std::shared_ptr<motion_client::ParamListener> param_listener;
    motion_client::Params params_;


};

}

int main(int argc, char **argv) {

    rclcpp::init(argc, argv);
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    auto node = std::make_shared<motion_client::MotionClientNode>("motion_server_L", socket);




    rclcpp::spin(node);
    rclcpp::shutdown();
    socket.close();

    return 0;

}
