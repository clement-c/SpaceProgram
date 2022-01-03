cmake_minimum_required(VERSION 3.15)

project(SpaceProgram VERSION 0.1 LANGUAGES CXX C)

set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
endif()

message(STATUS "---- Building for ${CMAKE_BUILD_TYPE} ----")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../Install/${CMAKE_BUILD_TYPE}/")
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/share")

add_subdirectory(Engine)
add_subdirectory(Deliverables)
