
include_directories(
	${PROJECT_ROOT_DIR}/inc 
)

add_library(experiment SHARED EXCLUDE_FROM_ALL
	experiment.cpp
)

add_dependencies(experiment
    pgm-reader
    opencv-surf
)

