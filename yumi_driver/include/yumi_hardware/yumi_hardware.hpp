#pragma once

#include "string"
#include "unordered_map"
#include "vector"

#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"

#include <abb_libegm/egm_controller_interface.h>
#include "yumi_packets/yumi_packets.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>


using hardware_interface::return_type;

namespace yumi_hardware
{
using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class HARDWARE_INTERFACE_PUBLIC YumiSystem : public hardware_interface::SystemInterface
{
public:
  CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  return_type read(const rclcpp::Time & time, const rclcpp::Duration & period) override;

  return_type write(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/) override;

protected:
  /// The size of this vector is (standard_interfaces_.size() x nr_joints)
  std::vector<double> joint_position_command_;
  std::vector<double> joint_velocities_command_;
  std::vector<double> joint_effort_command_;
  std::vector<double> joint_position_;
  std::vector<double> joint_velocities_;
  std::vector<double> joint_effort_;

  std::unordered_map<std::string, std::vector<std::string>> joint_interfaces = {
    {"position", {}}, {"velocity", {}}};


    // tcp connection
    boost::asio::io_service io_service_state_socket_l_;
    boost::asio::io_service io_service_state_socket_r_;
    boost::asio::io_service io_service_motion_socket_l_;
    boost::asio::io_service io_service_motion_socket_r_;
    boost::asio::io_service io_service_egm_l_;
    boost::asio::io_service io_service_egm_r_;

    boost::asio::ip::tcp::socket state_socket_l_ = boost::asio::ip::tcp::socket(io_service_state_socket_l_);
    boost::asio::ip::tcp::socket state_socket_r_ = boost::asio::ip::tcp::socket(io_service_state_socket_r_);
    boost::asio::ip::tcp::socket motion_socket_l_ = boost::asio::ip::tcp::socket(io_service_motion_socket_l_);
    boost::asio::ip::tcp::socket motion_socket_r_ = boost::asio::ip::tcp::socket(io_service_motion_socket_r_);
    boost::array<yumi_packets::ROS_msg_gripper_force, 1> write_buffer_;
    boost::asio::streambuf receive_buffer_;
    boost::system::error_code error_;

    //EGM interface
    std::shared_ptr<abb::egm::EGMControllerInterface> egm_interface_l;
    std::shared_ptr<abb::egm::EGMControllerInterface> egm_interface_r;

};

}  // namespace yumi_hardware
