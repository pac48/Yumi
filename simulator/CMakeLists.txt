cmake_minimum_required(VERSION 2.8.3)
project(simulator)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#find_package(RL COMPONENTS MDL REQUIRED)
#find_package(catkin REQUIRED roscpp message_generation)
find_package(catkin REQUIRED COMPONENTS
        RL
        roscpp
        message_generation
        )

add_service_files(
        FILES
        getStaticTorques.srv
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
)

link_directories(/usr/local/include)

add_executable( dynamics_node src/dynamics_node.cpp)
target_link_libraries( dynamics_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies( dynamics_node ${${PROJECT_NAME}_EXPORTED_TARGETS})
