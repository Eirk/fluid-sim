cmake_minimum_required(VERSION 3.0.0)
project(fluid-sim VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/SDL")
# add_subdirectory(SDL)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/SDL")

find_package(SDL2 REQUIRED)
# message(INFO "${SDL2_LIBRARIES}")
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(fluid-sim main.c)
target_link_libraries(fluid-sim ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(fluid-sim PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(fluid-sim PRIVATE fast_fluid_dynamics.c)
