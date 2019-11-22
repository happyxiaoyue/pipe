cmake_minimum_required(VERSION 3.0.0)
project(pipe_test VERSION 0.1.0)

include(CTest)
enable_testing()

# set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_FLAGS "-std=c99")

link_libraries(pthread)


add_executable(pipe_test main.c pipe.c pipe_util.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
