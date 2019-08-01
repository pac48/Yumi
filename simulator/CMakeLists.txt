cmake_minimum_required(VERSION 2.8.3)
project(simulator)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(RL REQUIRED)
#find_package(catkin REQUIRED roscpp message_generation)
find_package(catkin REQUIRED COMPONENTS
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
        ${RL_INCLUDE_DIRS}
)
#link_directories(/usr/local/include)


#add_library(Robot src/Robot.h)
#target_link_libraries(${RL_LIBRARIES})
add_dependencies(${${PROJECT_NAME}_EXPORTED_TARGETS})
add_executable( dynamics_node src/dynamics_node2.cpp) # ${RL_LIBRARIES}
target_link_libraries(dynamics_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies( dynamics_node ${${PROJECT_NAME}_EXPORTED_TARGETS})

#add_executable( dynamics_node src/dynamics_node.cpp)
#target_link_libraries( dynamics_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
#add_dependencies( dynamics_node ${${PROJECT_NAME}_EXPORTED_TARGETS})

#add_executable( robot src/Robot.cpp)
# target_link_libraries( robot ${RL_LIBRARIES} ${catkin_LIBRARIES})
# add_dependencies( robot ${${PROJECT_NAME}_EXPORTED_TARGETS})


