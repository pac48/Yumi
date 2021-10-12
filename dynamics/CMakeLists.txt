cmake_minimum_required(VERSION 2.8.3)
project(dynamics)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(RL REQUIRED)
#find_package(catkin REQUIRED roscpp message_generation)
find_package(catkin REQUIRED COMPONENTS
        roscpp
        message_generation
        )

generate_messages(
        DEPENDENCIES
        std_msgs
)


catkin_package(
        CATKIN_DEPENDS
        roscpp
        std_msgs
        message_runtime
)
include_directories(
        ${catkin_INCLUDE_DIRS}
        ${RL_INCLUDE_DIRS}
)

add_dependencies(${${PROJECT_NAME}_EXPORTED_TARGETS})
add_executable(yumi_node src/yumi_robot_node.cpp)

target_link_libraries(yumi_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies(yumi_node ${${PROJECT_NAME}_EXPORTED_TARGETS})