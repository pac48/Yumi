cmake_minimum_required(VERSION 3.5)
project(r6bot_controller)

find_package(ament_cmake REQUIRED)

install(
    DIRECTORY config launch
    DESTINATION share/r6bot_controller
)

ament_package()
