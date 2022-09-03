import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from control_msgs.action import GripperCommand


class GripperActionClient(Node):

    def __init__(self):
        super().__init__('gripper_client')
        self._action_client = ActionClient(self, GripperCommand, '/gripper_controller_r/gripper_cmd')

    def send_goal(self):
        goal_msg = GripperCommand.Goal()
        goal_msg.command.position = 0.018
        goal_msg.command.max_effort = 20.0

        self._action_client.wait_for_server()

        return self._action_client.send_goal_async(goal_msg)


def main(args=None):
    rclpy.init(args=args)

    action_client = GripperActionClient()

    future = action_client.send_goal()

    rclpy.spin_until_future_complete(action_client, future)


if __name__ == '__main__':
    main()
