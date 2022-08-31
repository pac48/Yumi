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


add_executable(motion_node_R src/client_node_motion_R.cpp)
add_executable(motion_node_L src/client_node_motion_L.cpp)

## Specify libraries to link a library or executable target against
ament_target_dependencies(motion_node_R
        ${THIS_PACKAGE_INCLUDE_DEPENDS}
        )
ament_target_dependencies(motion_node_L
        ${THIS_PACKAGE_INCLUDE_DEPENDS}
        )

install(DIRECTORY include/
        DESTINATION include
        )

install(TARGETS motion_node_R
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
install(TARGETS motion_node_L
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
