set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(02_GLSphere src.cpp)
target_link_libraries(02_GLSphere Engine glad fmt)
# target_include_directories(02_GLSphere PRIVATE ${CMAKE_INSTALL_INCLUDEDIR})

include(GNUInstallDirs)

install(TARGETS 02_GLSphere RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
