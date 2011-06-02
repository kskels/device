
include_directories(
	${PROJECT_ROOT_DIR}/inc 
    ${PROJECT_ROOT_DIR}/src/comp/pgm-reader
)

add_library(pgm-reader SHARED EXCLUDE_FROM_ALL
	pgm_reader.cpp
)

