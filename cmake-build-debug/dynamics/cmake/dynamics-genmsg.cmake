# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "dynamics: 0 messages, 8 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(dynamics_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" ""
)

get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" NAME_WE)
add_custom_target(_dynamics_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dynamics" "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)
_generate_srv_cpp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
)

### Generating Module File
_generate_module_cpp(dynamics
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(dynamics_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(dynamics_generate_messages dynamics_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_cpp _dynamics_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dynamics_gencpp)
add_dependencies(dynamics_gencpp dynamics_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dynamics_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)
_generate_srv_eus(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
)

### Generating Module File
_generate_module_eus(dynamics
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(dynamics_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(dynamics_generate_messages dynamics_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_eus _dynamics_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dynamics_geneus)
add_dependencies(dynamics_geneus dynamics_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dynamics_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)
_generate_srv_lisp(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
)

### Generating Module File
_generate_module_lisp(dynamics
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(dynamics_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(dynamics_generate_messages dynamics_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_lisp _dynamics_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dynamics_genlisp)
add_dependencies(dynamics_genlisp dynamics_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dynamics_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)
_generate_srv_nodejs(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
)

### Generating Module File
_generate_module_nodejs(dynamics
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(dynamics_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(dynamics_generate_messages dynamics_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_nodejs _dynamics_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dynamics_gennodejs)
add_dependencies(dynamics_gennodejs dynamics_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dynamics_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)
_generate_srv_py(dynamics
  "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
)

### Generating Module File
_generate_module_py(dynamics
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(dynamics_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(dynamics_generate_messages dynamics_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getJ.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getM.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getT.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getG.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getTrajTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/setTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getStaticTorques.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/unhrobotics/ROS_WS/src/dynamics/srv/getC.srv" NAME_WE)
add_dependencies(dynamics_generate_messages_py _dynamics_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dynamics_genpy)
add_dependencies(dynamics_genpy dynamics_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dynamics_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dynamics
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(dynamics_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dynamics
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(dynamics_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dynamics
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(dynamics_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dynamics
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(dynamics_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dynamics
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(dynamics_generate_messages_py std_msgs_generate_messages_py)
endif()
