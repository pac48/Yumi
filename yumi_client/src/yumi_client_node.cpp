#include "rclcpp/rclcpp.hpp"
#include "string"
#include "yumi_client/yumi_client.hpp"


int main(int argc, char **argv) {

    rclcpp::init(argc, argv);
    auto node = std::make_shared<yumi_client::YumiClientNode>("yumi_client_node");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;

}
