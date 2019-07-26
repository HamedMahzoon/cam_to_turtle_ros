cmake_minimum_required(VERSION 2.8.3)
project(cam_to_turtle)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  opencv_apps
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs
)

include_directories( ${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node src/cam_to_turtle_node.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )

add_executable(test_input_sig_pub src/test_input_sig_pub.cpp)
add_dependencies(test_input_sig_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_input_sig_pub  ${catkin_LIBRARIES} )
