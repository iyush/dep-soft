#
# stats/test/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

pkg_check_modules(CHECK REQUIRED check)

include_directories(${CMAKE_SOURCE_DIR}/src ${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

add_executable(check-stats check-stats.c)

target_link_libraries(check-stats stats
	${CHECK_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})
