cmake_minimum_required(VERSION 3.5)
project(motion_server)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()
# find dependencies
find_package(ament_cmake REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
        rclcpp
        std_msgs
        sensor_msgs
        )
foreach (Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach ()
find_package(generate_parameter_library REQUIRED)
generate_parameter_library(motion_client_node_parameters
        src/motion_client_parameters.yaml
        )


#add_executable(motion_node_R src/client_node_motion_R.cpp)
add_executable(motion_client_node src/motion_client_node.cpp)

target_link_libraries(motion_client_node
        motion_client_node_parameters
        )

## Specify libraries to link a library or executable target against
ament_target_dependencies(motion_client_node
        ${THIS_PACKAGE_INCLUDE_DEPENDS}
        )


install(TARGETS motion_client_node
        RUNTIME DESTINATION lib/motion_server
        ARCHIVE DESTINATION lib/motion_server
        LIBRARY DESTINATION lib/motion_server
        )

install(
        DIRECTORY launch
        DESTINATION share/motion_server
)
ament_export_dependencies(
        ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

ament_export_include_directories(
        include
)
ament_export_libraries(
        ${PROJECT_NAME}
)
ament_package()
