cmake_minimum_required(VERSION 3.5)
project(velocity_control)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
        rclcpp
        abb_libegm
        )

find_package(ament_cmake REQUIRED)
foreach (Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach ()

set_target_properties(${PROJECT_NAME}_joint_velocity_controller_node PROPERTIES OUTPUT_NAME joint_velocity_controller_node PREFIX "")
add_dependencies(${PROJECT_NAME}_joint_velocity_controller_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_joint_velocity_controller_node ${catkin_LIBRARIES})

add_executable(yumi_joint_velocity_controller_node src/joint_velocity_controller_node.cpp)

ament_target_dependencies(yumi_joint_velocity_controller_node ${THIS_PACKAGE_INCLUDE_DEPENDS})


install(DIRECTORY include/
        DESTINATION include
        )

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )