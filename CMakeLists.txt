cmake_minimum_required(VERSION 3.0.0)
project(fluid-sim VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)
# message(INFO "${SDL2_LIBRARIES}")
include_directories(${SDL2_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_executable(fluid-sim main.cpp)

target_link_libraries(fluid-sim ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(fluid-sim PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(fluid-sim PRIVATE fast_fluid_dynamics.c)
