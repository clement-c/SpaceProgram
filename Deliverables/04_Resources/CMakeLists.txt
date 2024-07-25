set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(03_Resources src.cpp)
target_link_libraries(03_Resources Engine glad fmt)

include(GNUInstallDirs)

install(TARGETS 03_Resources RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
