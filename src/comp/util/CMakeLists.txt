
include_directories(
	${PROJECT_ROOT_DIR}/inc 
)

add_library(pgm_reader SHARED EXCLUDE_FROM_ALL
	pgm_reader.cpp
)

