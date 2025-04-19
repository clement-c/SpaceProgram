add_subdirectory(fmt)
add_subdirectory(glad)
add_subdirectory(glm)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)


set(IMGUI_DIR ./imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)
file(GLOB IMGUI_SRC "${IMGUI_DIR}/*.cpp" "${IMGUI_DIR}/backends/*.cpp")
