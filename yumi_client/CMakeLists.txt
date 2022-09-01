cmake_minimum_required(VERSION 3.5)
project(yumi_client)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()
# find dependencies
find_package(ament_cmake REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
        rclcpp
        std_msgs
        sensor_msgs
        generate_parameter_library
        )
foreach (Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach ()

generate_parameter_library(yumi_client_parameters
        src/yumi_client_parameters.yaml
        )


add_library(yumi_client src/yumi_client.cpp)
target_include_directories(yumi_client PUBLIC include/)
target_link_libraries(yumi_client
        yumi_client_parameters
        )
ament_target_dependencies(yumi_client
        ${THIS_PACKAGE_INCLUDE_DEPENDS}
        )

add_executable(yumi_client_node src/yumi_client_node.cpp)
target_link_libraries(yumi_client_node
        yumi_client
        )

install(TARGETS yumi_client
        RUNTIME DESTINATION lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(TARGETS yumi_client_node
        RUNTIME DESTINATION lib/yumi_client
        ARCHIVE DESTINATION lib/yumi_client
        LIBRARY DESTINATION lib/yumi_client
        )

install(DIRECTORY include/
        DESTINATION include
        )
install(
        DIRECTORY launch
        DESTINATION share/yumi_client
)

ament_export_include_directories(
        include
)
ament_export_libraries(
        yumi_client
)

ament_package()
