
include_directories(
	${PROJECT_ROOT_DIR}/src/core
)

add_executable(portal_unittest EXCLUDE_FROM_ALL
	${PROJECT_ROOT_DIR}/src/core/portal.cpp
	portal_unittest.cpp
)

