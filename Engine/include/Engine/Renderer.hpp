#pragma once

#include <memory>
#include <stdint.h>

#include "Core/Lib.hpp"
#include "Graphics/RendererBackendI.hpp"

// Manipulated objects
struct Camera;
struct Material;
struct Matrix44;
struct TriangulatedMesh;

// Interface

class Renderer
{
public:
    enum class API
    {
        kVulkan,
        kOpenGL45,
        kDirect3D12
    };

    /**
     * @brief Checks whether the engine was compiled with support for a given API
     *
     * @param api
     * @return true
     * @return false
     */
    DLLEXPORT static bool RendererImplements(API api);

    /**
     * @brief Check whether the current host supports a given graphics API
     *
     * @param api
     * @return true
     * @return false
     */
    DLLEXPORT static bool HostSupports(API api);

    /**
     * @brief
     *
     * @param api
     * @return true
     * @return false
     */
    DLLEXPORT bool Initialize(API api = API::kOpenGL45);

    // Define targets
    // bool SetRenderTarget(Window);
    // bool SetRenderTarget(Framebuffer);

    // Managing meshes
    DLLEXPORT int32_t Upload(TriangulatedMesh const &);
    DLLEXPORT bool TransformEntity(int32_t mesh_gpu_id, Matrix44 const &transform);
    DLLEXPORT bool Render();

    DLLEXPORT bool UpdateCamera(Camera const&) noexcept;
    void SetViewport(int width, int height) noexcept;

private:
    std::unique_ptr<RendererBackendI> m_backend = nullptr;
};
