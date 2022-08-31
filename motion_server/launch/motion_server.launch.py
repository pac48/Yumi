from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    motion_client_node_L = Node(
        package="motion_server",
        executable="motion_client_node",
        name="motion_client_node_L",
        output="log",
        parameters=[
            {"ip_address": '192.168.1.13'},
            {"port_number": 12000}]
    )
    motion_client_node_R = Node(
        package="motion_server",
        executable="motion_client_node",
        name="motion_client_node_R",
        output="log",
        parameters=[
            {"ip_address": '192.168.1.13'},
            {"port_number": 11000}]
    )
    #
    nodes_to_start = [
        motion_client_node_L,
        motion_client_node_R,
    ]

    return LaunchDescription(nodes_to_start)
