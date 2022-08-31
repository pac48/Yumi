cmake_minimum_required(VERSION 3.5)
project(yumi_launch)

# find dependencies
find_package(ament_cmake REQUIRED)


install(
        DIRECTORY launch
        DESTINATION share/r6bot_description
)


ament_package()