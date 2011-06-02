cmake_minimum_required(VERSION 2.6)
project(device)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_ROOT_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_ROOT_DIR}/bin)

add_subdirectory(${PROJECT_ROOT_DIR}/src/core CMakeFiles/Core)
add_subdirectory(${PROJECT_ROOT_DIR}/src/comp CMakeFiles/Comp)

add_custom_target(clean-gen
    rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile 
)

