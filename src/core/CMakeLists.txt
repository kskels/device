
include_directories(
	${PROJECT_ROOT_DIR}/inc
	${PROJECT_ROOT_DIR}/src/core
)

add_executable(device
	portal.cpp
	core.cpp
)

target_link_libraries(device
	dl
)

