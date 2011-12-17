
include_directories(
	${PROJECT_ROOT_DIR}/inc
	${PROJECT_ROOT_DIR}/src/core
)

add_executable(cfw
	portal.cpp
	core.cpp
)

target_link_libraries(cfw
    boost_program_options
	dl
)

