# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "simulato: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(simulato_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" NAME_WE)
add_custom_target(_simulato_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "simulato" "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(simulato
  "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simulato
)

### Generating Module File
_generate_module_cpp(simulato
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simulato
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(simulato_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(simulato_generate_messages simulato_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" NAME_WE)
add_dependencies(simulato_generate_messages_cpp _simulato_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simulato_gencpp)
add_dependencies(simulato_gencpp simulato_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simulato_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(simulato
  "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/simulato
)

### Generating Module File
_generate_module_eus(simulato
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/simulato
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(simulato_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(simulato_generate_messages simulato_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" NAME_WE)
add_dependencies(simulato_generate_messages_eus _simulato_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simulato_geneus)
add_dependencies(simulato_geneus simulato_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simulato_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(simulato
  "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simulato
)

### Generating Module File
_generate_module_lisp(simulato
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simulato
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(simulato_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(simulato_generate_messages simulato_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" NAME_WE)
add_dependencies(simulato_generate_messages_lisp _simulato_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simulato_genlisp)
add_dependencies(simulato_genlisp simulato_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simulato_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(simulato
  "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/simulato
)

### Generating Module File
_generate_module_nodejs(simulato
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/simulato
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(simulato_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(simulato_generate_messages simulato_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" NAME_WE)
add_dependencies(simulato_generate_messages_nodejs _simulato_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simulato_gennodejs)
add_dependencies(simulato_gennodejs simulato_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simulato_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(simulato
  "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simulato
)

### Generating Module File
_generate_module_py(simulato
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simulato
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(simulato_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(simulato_generate_messages simulato_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/paul/Yumi_WS/src/simulator/srv/getTorques.srv" NAME_WE)
add_dependencies(simulato_generate_messages_py _simulato_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simulato_genpy)
add_dependencies(simulato_genpy simulato_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simulato_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simulato)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simulato
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(simulato_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/simulato)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/simulato
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(simulato_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simulato)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simulato
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(simulato_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/simulato)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/simulato
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(simulato_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simulato)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simulato\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simulato
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(simulato_generate_messages_py std_msgs_generate_messages_py)
endif()
