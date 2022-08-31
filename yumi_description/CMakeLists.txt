cmake_minimum_required(VERSION 3.5)
project(yumi_description)

# find dependencies
find_package(ament_cmake REQUIRED)

install(
	DIRECTORY launch meshes urdf
	DESTINATION share/yumi_description
)

ament_package()
