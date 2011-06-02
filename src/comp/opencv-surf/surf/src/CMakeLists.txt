
include_directories(
    ${PROJECT_ROOT_DIR}/src/comp/opencv-surf/lapack/inc
    ${PROJECT_ROOT_DIR}/src/comp/opencv-surf/surf/inc
)

file(GLOB SURF_SOURCE_FILES "*.cpp")
add_library(surf
	${SURF_SOURCE_FILES}
)

target_link_libraries(surf
    lapack
)

