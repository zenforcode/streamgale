cmake_minimum_required(VERSION 3.10)

project(TopologyServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Crow as a subdirectory
add_subdirectory(external/crow)

# Find ASIO
find_path(ASIO_INCLUDE_DIR asio.hpp
    PATHS
        /usr/include
        /usr/local/include
        ${CMAKE_SOURCE_DIR}/external/asio/include
    NO_DEFAULT_PATH
)

# Find Crow
find_path(CROW_INCLUDE_DIR crow.h
    PATHS
        ${PROJECT_SOURCE_DIR}/external/crow/include
    NO_DEFAULT_PATH
)

# Ensure dependencies are found
if(NOT ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "Asio not found!")
endif()

if(NOT CROW_INCLUDE_DIR)
    message(FATAL_ERROR "Crow not found!")
endif()

# Print found paths
message(STATUS "Found Asio in: ${ASIO_INCLUDE_DIR}")
message(STATUS "Found Crow in: ${CROW_INCLUDE_DIR}")

# Add executable
add_executable(toposerver toposerver.cpp)

# Include directories
target_include_directories(toposerver PRIVATE ${ASIO_INCLUDE_DIR} ${CROW_INCLUDE_DIR})

# Link Crow library
target_link_libraries(toposerver PRIVATE crow)
