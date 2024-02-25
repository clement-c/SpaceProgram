#include "Engine/Renderer.hpp"
#include "Engine/Core/Logging.hpp"

#ifdef ENGINE_IMPLEMENTS_OPENGL
#include "Engine/Graphics/GL/RendererBackendOpenGL.hpp"
#endif

#ifdef ENGINE_IMPLEMENTS_VULKAN
#include "Engine/Graphics/Vulkan/RendererBackendVulkan.hpp"
#endif

#ifdef ENGINE_IMPLEMENTS_DIRECT3D
#include "Engine/Graphics/Direct3D/RendererBackendDirect3D.hpp"
#endif

bool Renderer::RendererImplements(API api)
{
    switch (api)
    {
    case API::kVulkan:
#ifdef ENGINE_IMPLEMENTS_VULKAN
        return true;
#else
        return false;
#endif
    case API::kOpenGL45:
#ifdef ENGINE_IMPLEMENTS_OPENGL
        return true;
#else
        return false;
#endif
    case API::kDirect3D12:
#ifdef ENGINE_IMPLEMENTS_DIRECT3D
        return true;
#else
        return false;
#endif
    default:
        return false;
    }
}

bool Renderer::HostSupports(Renderer::API api)
{
    return RendererImplements(api) && true; // TODO: implement checking support at runtime if api is implemented
}

bool Renderer::Initialize(Renderer::API api)
{
    if (m_backend)
        return true;

    if (!RendererImplements(api))
    {
        CC_LOG_ERROR("Engine does not implement the required renderer in this distribution.");
        return false;
    }
    else if (!HostSupports(api))
    {
        CC_LOG_ERROR("Host does not support the required renderer.");
        return false;
    }
    else
    {
        if (api == API::kOpenGL45)
        {
            CC_LOG_DEBUG("Initializing renderer with OpenGL 4.5...\n");
            RendererBackendOpenGL backend;
            m_backend = std::make_unique<RendererBackendOpenGL>();
            // TODO: check that initialization actually worked before putting in unique_ptr
            return m_backend->Initialize();
        }
        else if (api == API::kVulkan)
        {
            CC_LOG_ERROR("Vulkan renderer not implemented yet.");
            return false;
        }
        else if (api == API::kDirect3D12)
        {
            CC_LOG_ERROR("Direct3D renderer not implemented yet.");
            return false;
        }
        // initialize backend
        return true;
    }

}

int32_t Renderer::Upload(TriangulatedMesh const &mesh)
{
    if (m_backend)
        return m_backend->Upload(mesh);
    else
        return 0;
}

// bool SetRenderTarget(Window);
// bool SetRenderTarget(Framebuffer);

bool Renderer::TransformEntity(int32_t mesh_gpu_id, Matrix44 const &transform)
{
    if (m_backend)
        return m_backend->SetMatrix(mesh_gpu_id, transform);
    else
        return false;
}

bool Renderer::Render()
{
    if (m_backend)
        return m_backend->RenderAll();
    else
        return false;
}

bool Renderer::DisableEntity(uint32_t mesh_gpu_id)
{
    CC_LOG_ERROR("Renderer::DisableEntity not implmented");
    return false;
}

bool Renderer::DeleteEntity(uint32_t mesh_gpu_id)
{
    CC_LOG_ERROR("Renderer::DeleteEntity not implmented");
    return false;
}

bool Renderer::UpdateCamera(Camera const &camera) noexcept
{
    if (m_backend)
        return m_backend->UpdateCamera(camera);
    else
        return false;
}

void Renderer::SetViewport(int width, int height) noexcept
{
    if (m_backend)
        m_backend->SetViewport(width, height);
}
