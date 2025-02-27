cmake_minimum_required(VERSION 3.10)

project(supervisor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for vcpkg toolchain
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "Using vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(WARNING "VCPKG_ROOT is not set, vcpkg may not be available.")
endif()


# Find ASIO
find_path(ASIO_INCLUDE_DIR asio.hpp
    PATHS
        /usr/include
        /usr/local/include
)

# Find Crow
find_package(Crow CONFIG REQUIRED)


# Ensure dependencies are found
if(NOT ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "Asio not found!")
endif()

if(NOT CROW_INCLUDE_DIR)
    message(FATAL_ERROR "Crow not found! Expected in ${PROJECT_SOURCE_DIR}/external/crow/include")
endif()


# Print found paths
message(STATUS "Found Asio in: ${ASIO_INCLUDE_DIR}")
message(STATUS "Found Crow in: ${CROW_INCLUDE_DIR}")

# Add executable
add_executable(toposerver toposerver.cpp)
target_link_libraries(toposerver PRIVATE Crow::Crow asio::asio)

# Include directories
target_include_directories(toposerver PRIVATE ${ASIO_INCLUDE_DIR} ${CROW_INCLUDE_DIR})

