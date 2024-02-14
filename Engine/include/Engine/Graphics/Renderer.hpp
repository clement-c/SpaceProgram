#pragma once

struct Scene;

class Renderer
{
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
    static bool RendererImplements(API api)
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

    /**
     * @brief Check whether the current host supports a given graphics API
     *
     * @param api
     * @return true
     * @return false
     */
    static bool HostSupports(API api)
    {
        return RendererImplements(api) && true; // TODO: implement checking support at runtime if api is implemented
    }

    // void Render(Scene const *scene) const;

};
