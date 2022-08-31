cmake_minimum_required(VERSION 3.5)
project(dynamics)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
        RL
        rclcpp
        std_msgs
        sensor_msgs
        )
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach()

add_executable(yumi_node src/yumi_robot_node.cpp)
target_link_libraries(yumi_node ${RL_LIBRARIES})
ament_target_dependencies(yumi_node ${THIS_PACKAGE_INCLUDE_DEPENDS})


install(DIRECTORY include/
        DESTINATION include
        )

install(TARGETS yumi_node
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
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