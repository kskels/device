
include_directories(
    ${PROJECT_ROOT_DIR}/src/comp/opencv-surf/lapack/inc
)

file(GLOB LAPACK_SOURCE_FILES "*.c")
add_library(lapack EXCLUDE_FROM_ALL
    ${LAPACK_SOURCE_FILES}	
)

