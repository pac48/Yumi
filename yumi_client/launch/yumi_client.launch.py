from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    joint_names_L = ["yumi_joint_1_l",
                     "yumi_joint_2_l",
                     "yumi_joint_7_l",
                     "yumi_joint_3_l",
                     "yumi_joint_4_l",
                     "yumi_joint_5_l",
                     "yumi_joint_6_l",
                     "gripper_l_joint"]

    joint_names_R = ["yumi_joint_1_r",
                     "yumi_joint_2_r",
                     "yumi_joint_7_r",
                     "yumi_joint_3_r",
                     "yumi_joint_4_r",
                     "yumi_joint_5_r",
                     "yumi_joint_6_r",
                     "gripper_r_joint"]

    ymui_client_node_L = Node(
        package="yumi_client",
        executable="yumi_client_node",
        name="yumi_client_node_L",
        output="log",
        parameters=[
            {"ip_address": '192.168.1.13'},
            {"read_port": 12002},
            {"write_port": 12000},
            {"gripper_force_command_topic": 'gripper_command_L'},
            {"joint_state_topic": 'joint_state_L'},
            {"joint_names": joint_names_L}
        ]
    )
    ymui_client_node_R = Node(
        package="yumi_client",
        executable="yumi_client_node",
        name="yumi_client_node_R",
        output="log",
        parameters=[
            {"ip_address": '192.168.1.13'},
            {"read_port": 11002},
            {"write_port": 11000},
            {"gripper_force_command_topic": 'gripper_command_R'},
            {"joint_state_topic": 'joint_state_R'},
            {"joint_names": joint_names_R}
        ]
    )
    #
    nodes_to_start = [
        ymui_client_node_L,
        ymui_client_node_R,
    ]

    return LaunchDescription(nodes_to_start)
