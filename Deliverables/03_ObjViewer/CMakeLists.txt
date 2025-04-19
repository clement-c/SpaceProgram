set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(03a_ObjViewer src.cpp)
target_link_libraries(03a_ObjViewer Engine glad fmt)

# add_executable(03b_RscViewer src_b.cpp)
# target_link_libraries(03b_RscViewer Engine glad fmt)

include(GNUInstallDirs)
install(TARGETS 03a_ObjViewer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
# install(TARGETS 03b_RscViewer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY rsc03 DESTINATION ${CMAKE_INSTALL_BINDIR})
