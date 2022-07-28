cmake_minimum_required (VERSION 3.20.2)
project (LOGGER)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories (./include)

link_libraries(pthread)

set (main ./main.cpp)
aux_source_directory(./src SOURCES)

# gdb debug
set(CMAKE_BUILD_TYPE "DEBUG")


add_executable (LOGGER ${main} ${SOURCES})

