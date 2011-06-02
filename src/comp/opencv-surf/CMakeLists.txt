
include_directories(
    ${PROJECT_ROOT_DIR}/inc   
    surf/inc   
    lapack/inc
)

file(GLOB LAPACK_SOURCE_FILES "lapack/src/*.c")
file(GLOB SURF_SOURCE_FILES "surf/src/*.cpp")

add_library(opencv-surf SHARED EXCLUDE_FROM_ALL
    ${LAPACK_SOURCE_FILES}
    ${SURF_SOURCE_FILES}
    opencv_surf.cpp
)

