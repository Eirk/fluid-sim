cmake_minimum_required(VERSION 3.0.0)
project(fluid-sim VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(fluid-sim main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(fluid-sim PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(fluid-sim PRIVATE fast_fluid_dynamics.c)
