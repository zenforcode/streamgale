cmake_minimum_required(VERSION 3.10)
project(TopologyServer)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(external/crow)
include_directories(${PROJECT_SOURCE_DIR}/external/crow/include
/usr/include)
add_executable(server toposerver.cpp)
target_link_libraries(server PRIVATE crow)
