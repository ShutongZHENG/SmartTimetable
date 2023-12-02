cmake_minimum_required(VERSION 3.0.0)
set( CMAKE_CXX_FLAGS "-std=c++11" )
project(SmartTimetable VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# 指定包含的头文件目录
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(SmartTimetable ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
