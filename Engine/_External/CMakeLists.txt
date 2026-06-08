add_subdirectory(fmt)

if(${ENGINE_BUILD_RENDERER})
    add_subdirectory(glad)
    add_subdirectory(glm)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
set(_imgui_cpps "${IMGUI_DIR}/imgui.cpp" "${IMGUI_DIR}/imgui_draw.cpp" "${IMGUI_DIR}/imgui_widgets.cpp" "${IMGUI_DIR}/imgui_tables.cpp" "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp")

set(IMGUI_PUBLIC_HEADERS "${IMGUI_DIR}/imgui.h" "${IMGUI_DIR}/imconfig.h")
if(${ENGINE_IMPLEMENTS_OPENGL})
    list(APPEND _imgui_cpps "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")
endif()
if(${ENGINE_IMPLEMENTS_VULKAN})
    list(APPEND _imgui_cpps "${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp")
endif()

#FIXME: Create an actual static library for imgui and install it along with necessary headers
add_library(imgui STATIC ${_imgui_cpps})
set_target_properties(imgui PROPERTIES PUBLIC_HEADER "${IMGUI_PUBLIC_HEADERS}")
target_include_directories(imgui PUBLIC "${IMGUI_DIR}" "${IMGUI_DIR}/backends")
target_link_libraries(imgui PRIVATE glfw OpenGL::GL)
install(FILES ${IMGUI_PUBLIC_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/imgui)
