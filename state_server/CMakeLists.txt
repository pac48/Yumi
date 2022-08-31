cmake_minimum_required(VERSION 3.5)
project(state_server)


if(NOT CMAKE_CXX_STANDARD)
 set(CMAKE_CXX_STANDARD 17)
endif()


# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
        rclcpp
        std_msgs
        sensor_msgs
        )

find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
 find_package(${Dependency} REQUIRED)
endforeach()

add_executable(client_node_R src/client_node_R.cpp)
add_executable(client_node_L src/client_node_L.cpp )
add_executable(joint_state src/joint_state.cpp)

ament_target_dependencies(client_node_R ${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_target_dependencies(client_node_L ${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_target_dependencies(joint_state ${THIS_PACKAGE_INCLUDE_DEPENDS})


install(DIRECTORY include/
        DESTINATION include
        )

install(TARGETS client_node_R
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(TARGETS client_node_L
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(TARGETS joint_state
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