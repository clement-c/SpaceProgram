cmake_minimum_required(VERSION 3.15)

project(Engine VERSION 0.1)

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(_External)


set(LIB_NAME "Engine")
set(ENGINE_SOURCE_FILES "src/Application.cpp" "src/Camera.cpp" "src/checkError.hpp" "src/Engine.cpp" "src/Entity.cpp" "src/GLBuffer.cpp"
    "src/GLProgram.cpp" "src/GLShader.cpp" "src/GLVAO.cpp" "src/Maths.cpp" "src/Renderer.cpp" "src/ResourceManager.cpp"
    "src/Scene.cpp" "src/Window.cpp" "src/WindowsManager.cpp")

add_library(${LIB_NAME} SHARED ${ENGINE_SOURCE_FILES})

# ===== Core libraries =====

target_compile_definitions(${LIB_NAME} PUBLIC CC_LOG_LEVEL=CC_DEBUG_LEVEL PRIVATE CC_ENGINE_EXPORTS) # CC_LOG_LEVEL=CC_DEBUG_LEVEL
target_include_directories(${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)
set(core_libraries glad glm::glm fmt glfw)

#  ===== Graphics backends =====

if(${ENGINE_IMPLEMENT_OPENGL})
    find_package(OpenGL REQUIRED)
endif()

if(${ENGINE_IMPLEMENT_VULKAN})
    find_package(Vulkan REQUIRED)
endif()

# Add libraries for OpenGL
if(${ENGINE_IMPLEMENT_OPENGL})
    target_compile_definitions(${LIB_NAME} PUBLIC GLAD_API_CALL_EXPORT PRIVATE ENGINE_IMPLEMENTS_OPENGL)
    target_sources(${LIB_NAME} PRIVATE src/RendererBackendOpenGL.cpp)

    message(STATUS "OpenGL backend enabled")
    set(graphics_libraries OpenGL::GL)
endif()

# Add libraries for Vulkan
if(${ENGINE_IMPLEMENT_VULKAN})
    # target_compile_definitions(${LIB_NAME} PUBLIC VULKAN_API_CALL_EXPORT PRIVATE ENGINE_IMPLEMENTS_VULKAN)
    # target_sources(${LIB_NAME} PRIVATE src/RendererBackendVulkan.cpp)

    # message(STATUS "Vulkan backend enabled")
    # set(graphics_libraries ${graphics_libraries} Vulkan::Vulkan)
endif()

target_link_libraries(${LIB_NAME} PRIVATE ${core_libraries} ${graphics_libraries})


# Define installation targets
install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME})

install(EXPORT ${LIB_NAME}Config DESTINATION share/${LIB_NAME}/cmake)
export(TARGETS ${LIB_NAME} FILE ${LIB_NAME}Config.cmake)
