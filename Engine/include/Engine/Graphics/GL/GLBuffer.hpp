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

    enum class Usage : int
    {
        StreamDraw = GL_STREAM_DRAW,
        StreamRead = GL_STREAM_READ,
        StreamCopy = GL_STREAM_COPY,
        StaticDraw = GL_STATIC_DRAW,
        StaticRead = GL_STATIC_READ,
        StaticCopy = GL_STATIC_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY
    };

    DLLEXPORT GLBuffer(Type tp = Type::kArrayBuffer);
    DLLEXPORT ~GLBuffer();

    DLLEXPORT uint32_t GetId() const;

    DLLEXPORT bool Bind();
    DLLEXPORT bool Unbind();

    DLLEXPORT bool SetData(int const* data, size_t size, Usage usage);
    DLLEXPORT bool SetData(unsigned int const* data, size_t size, Usage usage);
    DLLEXPORT bool SetData(float const* data, size_t size, Usage usage);
    DLLEXPORT bool SetData(double const* data, size_t size, Usage usage);

    DLLEXPORT Type GetType() const;

    DLLEXPORT int GetDataType() const;
    DLLEXPORT size_t GetNumComponents() const;

private:
    size_t m_length = 0;
    uint32_t m_id = 0;
    int m_dataType = 0;
    Type m_type = Type::kArrayBuffer;
};
