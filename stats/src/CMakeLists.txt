#
# stats/src/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

include_directories(${PROJECT_BINARY_DIR}/src)

add_library(stats stats.c)

add_executable(ds main.c)
target_link_libraries(ds stats)


