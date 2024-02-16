set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(01_GLWindowTriangle src.cpp)
target_link_libraries(01_GLWindowTriangle Engine glad)

include(GNUInstallDirs)

install(TARGETS 01_GLWindowTriangle RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
