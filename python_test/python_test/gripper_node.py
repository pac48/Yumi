import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from control_msgs.action import GripperCommand
from sensor_msgs.msg import Joy


class GripperActionClient(Node):

    def __init__(self):
        super().__init__('gripper_client')
        self._action_client = ActionClient(self, GripperCommand, '/gripper_controller_r/gripper_cmd')
        self.subscription = self.create_subscription(
            Joy,
            '/joy',
            self.listener_callback,
            10)
        self.closed = -1

    def listener_callback(self, msg):
        tmp = msg.buttons[0] == 1
        if not tmp is self.closed:
            self.closed = tmp
            self.send_goal(self.closed)

    def send_goal(self, open: bool):
        goal_msg = GripperCommand.Goal()
        if open:
            goal_msg.command.position = 1.0
        else:
            goal_msg.command.position = 0.0
        goal_msg.command.max_effort = 20.0

        self._action_client.wait_for_server()

        return self._action_client.send_goal_async(goal_msg)


def main(args=None):
    rclpy.init(args=args)

    action_client = GripperActionClient()

    future = action_client.send_goal(True)

    rclpy.spin_until_future_complete(action_client, future)

    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
