cmake_minimum_required(VERSION 3.5)
project(bioinf_project)
set(CMAKE_CXX_STANDARD 11)

# gcc (do not use -static flag because google tests needs linker help)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O9 -std=c++11 -DNDEBUG -ffast-math -funroll-loops -msse4.2 -Wall") # -O0 -g -pg -Q for gprof  after put -03

# set dir for root folder at tuntime , e.g. cin/cout root path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# set dir for compiled libs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# create run configs executable
add_executable(debruijn.exe src/main.cpp src/helper.cpp src/helper.h)

# add libraries to executable
target_link_libraries(debruijn.exe sdsl divsufsort divsufsort64)