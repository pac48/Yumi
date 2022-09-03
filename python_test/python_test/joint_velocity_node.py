import rclpy
from rclpy.node import Node

from std_msgs.msg import Float64MultiArray
from math import sin

yumi_joints = ["yumi_joint_1_r",
               "yumi_joint_2_r",
               "yumi_joint_7_r",
               "yumi_joint_3_r",
               "yumi_joint_4_r",
               "yumi_joint_5_r",
               "yumi_joint_6_l",
               "yumi_joint_1_l",
               "yumi_joint_2_l",
               "yumi_joint_7_l",
               "yumi_joint_3_l",
               "yumi_joint_4_l",
               "yumi_joint_5_l",
               "yumi_joint_6_l"]
velocity_command_topic = "/velocity_controller/commands"


class VelocityPublisher(Node):

    def __init__(self):
        super().__init__('velocity_publisher')
        self.publisher_ = self.create_publisher(Float64MultiArray, velocity_command_topic, 10)
        self.timer_period = 1.0 / 60.0  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)
        self.time = 0.0

    def timer_callback(self):
        msg = Float64MultiArray()
        num = .05 * sin(.5 * self.time)
        msg.data = [num for joint in yumi_joints]
        self.publisher_.publish(msg)
        self.time += self.timer_period


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = VelocityPublisher()

    rclpy.spin(minimal_publisher)

    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
