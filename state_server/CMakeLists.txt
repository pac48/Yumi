cmake_minimum_required(VERSION 3.5)
project(state_server)


if(NOT CMAKE_CXX_STANDARD)
 set(CMAKE_CXX_STANDARD 17)
endif()


# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
        rclcpp
        std_msgs
        yumi_packets
        sensor_msgs
        generate_parameter_library
        )

find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
 find_package(${Dependency} REQUIRED)
endforeach()

generate_parameter_library(state_client_node_parameters
        src/state_client_parameters.yaml
        )

add_executable(state_client_node src/state_client_node.cpp)
#add_executable(client_node_L src/client_node_L.cpp )
add_executable(joint_state src/joint_state.cpp)

ament_target_dependencies(state_client_node ${THIS_PACKAGE_INCLUDE_DEPENDS})
#ament_target_dependencies(client_node_L ${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_target_dependencies(joint_state ${THIS_PACKAGE_INCLUDE_DEPENDS})


install(DIRECTORY include/
        DESTINATION include
        )

install(TARGETS state_client_node
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

#install(TARGETS client_node_L
#        RUNTIME DESTINATION bin
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#        )

install(TARGETS joint_state
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

ament_package()