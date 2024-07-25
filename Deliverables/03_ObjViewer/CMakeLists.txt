set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(03_ObjViewer src.cpp)
target_link_libraries(03_ObjViewer Engine glad fmt)
# target_include_directories(02_GLSphere PRIVATE ${CMAKE_INSTALL_INCLUDEDIR})

include(GNUInstallDirs)
install(TARGETS 03_ObjViewer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY rsc03 DESTINATION ${CMAKE_INSTALL_BINDIR})
