cmake_minimum_required(VERSION 3.5)
project(yumi_packets)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif ()
# find dependencies
find_package(ament_cmake REQUIRED)

add_library(yumi_packets include/yumi_packets/yumi_packets.hpp)
set_target_properties(yumi_packets PROPERTIES LINKER_LANGUAGE CXX)


install(TARGETS yumi_packets
        RUNTIME DESTINATION lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(DIRECTORY include/
        DESTINATION include
        )

ament_export_include_directories(
        include
)
ament_export_libraries(
        yumi_packets
)

ament_package()
