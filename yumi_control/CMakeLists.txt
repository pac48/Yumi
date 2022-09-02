cmake_minimum_required(VERSION 3.5)
project(yumi_control)

find_package(ament_cmake REQUIRED)

install(
    DIRECTORY config launch
    DESTINATION share/yumi_control
)

ament_package()
