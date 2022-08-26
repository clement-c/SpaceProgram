
add_executable(02_GLSphere src.cpp)
target_link_libraries(02_GLSphere Engine glad)

include(GNUInstallDirs)

install(TARGETS 02_GLSphere RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
