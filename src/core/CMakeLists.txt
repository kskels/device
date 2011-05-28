
include_directories(
	${PROJECT_ROOT_DIR}/inc
)

add_executable(device
	core.cpp
)

target_link_libraries(device
	dl
)

