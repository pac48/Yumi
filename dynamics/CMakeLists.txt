cmake_minimum_required(VERSION 2.8.3)
project(dynamics)
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
        getM.srv
        getC.srv
        getG.srv
        getJ.srv
        getT.srv
        setTorques.srv
        getTrajTorques.srv
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
add_executable( real_robot_node src/real_robot_node.cpp) # ${RL_LIBRARIES}
target_link_libraries(real_robot_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies( real_robot_node ${${PROJECT_NAME}_EXPORTED_TARGETS})


add_executable( sim_robot_node src/sim_robot_node.cpp) # ${RL_LIBRARIES}
target_link_libraries(sim_robot_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies( sim_robot_node ${${PROJECT_NAME}_EXPORTED_TARGETS})

add_executable( vis_sim_robot_node src/vis_sim_robot_node.cpp) # ${RL_LIBRARIES}
target_link_libraries(vis_sim_robot_node ${RL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies( vis_sim_robot_node ${${PROJECT_NAME}_EXPORTED_TARGETS})




