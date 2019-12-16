cmake_minimum_required(VERSION 2.8.3)
project(pub_goal)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
)

set( sources
  src/main.cpp
)

set( headers
)

catkin_package(
  LIBRARIES pub_goal
  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node ${headers} ${sources})

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

