#include "rclcpp/rclcpp.hpp"
#include "string"
#include "yumi_client/yumi_client.hpp"


int main(int argc, char **argv) {

    rclcpp::init(argc, argv);
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    auto node = std::make_shared<yumi_client::YumiClientNode>("yumi_client_node");


    rclcpp::spin(node);
    rclcpp::shutdown();
    socket.close();

    return 0;

}
