
include_directories(
	${PROJECT_ROOT_DIR}/inc 
)

add_library(example SHARED EXCLUDE_FROM_ALL
	example.cpp
)

