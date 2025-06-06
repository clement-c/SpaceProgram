cmake_minimum_required(VERSION 3.15)

project(SpaceProgram VERSION 0.1 LANGUAGES CXX C)

set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
endif()

option(ENGINE_BUILD_DOC "Build documentation" OFF)
option(ENGINE_BUILD_TESTS "Build tests" ON)

option(ENGINE_IMPLEMENT_OPENGL "Enable OpenGL backend" ON)
option(ENGINE_IMPLEMENT_VULKAN "Enable Vulkan backend" OFF)

# add_compile_definitions(CC_LOG_LEVEL CC_SUCCESS_LEVEL)

include(GNUInstallDirs)

if(${ENGINE_BUILD_DOC})
  find_package(Doxygen REQUIRED)
  if(DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM)
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs" DESTINATION ${CMAKE_INSTALL_DOCDIR})
  else()
    message("Doxygen needs to be installed to generate the doxygen documentation")
  endif()
endif()

message(STATUS "---- Building for ${CMAKE_BUILD_TYPE} ----")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../Install/${CMAKE_BUILD_TYPE}/")
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/share")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Engine)

if(${ENGINE_BUILD_TESTS})
  enable_testing()
  add_subdirectory(Tests)
endif()

add_subdirectory(Deliverables)
