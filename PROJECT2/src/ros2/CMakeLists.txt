cmake_minimum_required(VERSION 3.0.2)
project(project2)


find_package(
  catkin REQUIRED COMPONENTS 
  roscpp 
  rospy 
  std_msgs
  tf
  geometry_msgs
  nav_msgs
  message_generation
  )


generate_messages(
  DEPENDENCIES 
  nav_msgs
  geometry_msgs
  std_msgs
  )

catkin_package(
  CATKIN_DEPENDS
  std_msgs
  geometry_msgs
  message_runtime
  )


catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ComputeOdometry src/ComputeOdometry.cpp)
target_link_libraries(ComputeOdometry ${catkin_LIBRARIES})


