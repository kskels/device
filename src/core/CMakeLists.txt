
include_directories(
	/opt/gtest/gtest-1.5.0/include
	${PROJECT_ROOT_DIR}/inc
	${PROJECT_ROOT_DIR}/src/core
)

add_executable(cfw
	portal.cpp
	core.cpp
)

target_link_libraries(cfw
	dl
)

