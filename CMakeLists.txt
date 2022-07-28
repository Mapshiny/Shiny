cmake_minimum_required (VERSION 3.20.2)
project (LOGGER)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories (./include)
include_directories (./include/Interface)
include_directories (./include/zip)

file (GLOB_RECURSE SOURCES ./src/*.cpp)


#aux_source_directory(./src SOURCES)

link_libraries(pthread z)

set (main ./main.cpp)



# gdb debug
#set(CMAKE_BUILD_TYPE "DEBUG")


add_executable (LOGGER ${main} ${SOURCES})

