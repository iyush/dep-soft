#
# rpn/test/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

pkg_check_modules(CHECK REQUIRED check)

include_directories(${CMAKE_SOURCE_DIR}/src ${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

add_executable(check-rpn-stack check-rpn-stack.c)
add_executable(check-rpn check-rpn.c)

target_link_libraries(check-rpn-stack rpn-stack
	${CHECK_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(check-rpn rpn rpn-stack
	${CHECK_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})
