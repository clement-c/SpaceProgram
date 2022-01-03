#pragma once
#include "../../Core/Lib.hpp"
#include <vector>
#include <stdint.h>
#include <glad/gl.h>

struct GLBuffer
{

    enum class Type : int
    {
        kArrayBuffer = GL_ARRAY_BUFFER /* Vertex buffer */
    };

    DLLEXPORT GLBuffer(Type tp);

    DLLEXPORT bool Bind();
    DLLEXPORT bool Unbind();

    DLLEXPORT bool SetData(float* data, size_t size, int usage);

    Type GetType() const;
    uint32_t GetId() const;
    size_t GetNumEntries() const;

private:
    size_t m_num = 0;
    uint32_t m_id = 0;
    Type m_type = Type::kArrayBuffer;
};
