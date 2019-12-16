cmake_minimum_required(VERSION 2.8.3)
project(velocity_control)

find_package(catkin REQUIRED COMPONENTS roscpp abb_libegm)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  CATKIN_DEPENDS roscpp abb_libegm
)

###########
## Build ##
###########

include_directories(
 ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_joint_velocity_controller_node src/joint_velocity_controller_node.cpp)
set_target_properties(${PROJECT_NAME}_joint_velocity_controller_node PROPERTIES OUTPUT_NAME joint_velocity_controller_node PREFIX "")
add_dependencies(${PROJECT_NAME}_joint_velocity_controller_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_joint_velocity_controller_node ${catkin_LIBRARIES})

