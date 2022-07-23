cmake_minimum_required (VERSION 3.20.2)
project (LOGGER)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories (./include)



set (main ./main.cpp)
aux_source_directory(./src SOURCES)



add_executable (LOGGER ${main} ${SOURCES})

