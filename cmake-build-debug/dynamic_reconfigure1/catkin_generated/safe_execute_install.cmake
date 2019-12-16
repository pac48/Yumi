execute_process(COMMAND "/home/paul/Yumi_WS/src/cmake-build-debug/dynamic_reconfigure1/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/paul/Yumi_WS/src/cmake-build-debug/dynamic_reconfigure1/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
