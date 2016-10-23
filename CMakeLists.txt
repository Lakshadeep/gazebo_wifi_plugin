cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(wifirouter SHARED WifiRouterPlugin.cc)
target_link_libraries(wifirouter ${GAZEBO_libraries})

add_library(wifireceiver SHARED WifiReceiverPlugin.cc)
target_link_libraries(wifireceiver ${GAZEBO_libraries})