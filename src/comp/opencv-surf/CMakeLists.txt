
include_directories(
    ${PROJECT_ROOT_DIR}/inc   
    ${PROJECT_ROOT_DIR}/src/comp/opencv-surf/surf/inc   
)

add_library(opencv-surf SHARED
    opencv_surf.cpp
)

target_link_libraries(opencv-surf
    surf
)
    
add_subdirectory(lapack)
add_subdirectory(surf)

