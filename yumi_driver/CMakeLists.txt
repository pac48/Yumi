cmake_minimum_required(VERSION 3.5)
project(yumi_driver)


if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()
# find dependencies
find_package(ament_cmake REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
        rclcpp
        rcpputils
        hardware_interface
        abb_libegm
        )
foreach (Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach ()
find_package(Boost COMPONENTS thread REQUIRED)

add_library(
        yumi_hardware
        SHARED
        src/yumi_hardware.cpp
)

target_include_directories(
        yumi_hardware
        PUBLIC
        include
)

ament_target_dependencies(
        yumi_hardware
        ${THIS_PACKAGE_INCLUDE_DEPENDS}
)
target_link_libraries(yumi_hardware
        Boost::thread
    )

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(yumi_hardware PRIVATE "YUMI_HARDWARE_DLL")

pluginlib_export_plugin_description_file(hardware_interface yumi_hardware_plugin_description.xml)

install(
        DIRECTORY include
        DESTINATION include
)

install(
        TARGETS yumi_hardware
        RUNTIME DESTINATION lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)

ament_package()
