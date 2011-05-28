cmake_minimum_required(VERSION 2.6)
project(device)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_ROOT_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_ROOT_DIR}/bin)

add_subdirectory(${PROJECT_ROOT_DIR}/src/core CMakeLists/Core)
add_subdirectory(${PROJECT_ROOT_DIR}/src/comp CMakeLists/Comp)

