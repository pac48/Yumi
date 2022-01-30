# Yumi

This repository requires the library [abb_libegm](https://github.com/ros-industrial/abb_libegm) to be installed. You must set an environmental variable named "abb_libegm" to the path where the library is installed.
This repository requires the library [rl](https://github.com/roboticslibrary/rl) to be installed. Robotics library (rl) is c++ library for calculating robot dynamics and kinematics. 

Install abb_libegm:
On Ubuntu, clone the repository and cd into the abb_libegm folder.  
Run the follwing commands:
1) mkdir build
2) cd build/
3) cmake ..
4) make install
