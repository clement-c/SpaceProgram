include(GNUInstallDirs)

add_library(glad SHARED src/gl.c)

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
    
target_compile_definitions(glad INTERFACE GLAD_API_CALL_EXPORT PRIVATE GLAD_API_CALL_EXPORT GLAD_API_CALL_EXPORT_BUILD)

install(TARGETS glad EXPORT gladConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glad)

install(EXPORT gladConfig DESTINATION share/glad/cmake)
export(TARGETS glad FILE gladConfig.cmake)
