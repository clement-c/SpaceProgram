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

    DLLEXPORT uint32_t GetId() const;

    DLLEXPORT bool Bind();
    DLLEXPORT bool Unbind();

    DLLEXPORT bool SetData(int* data, size_t size, int usage);
    DLLEXPORT bool SetData(unsigned int* data, size_t size, int usage);
    DLLEXPORT bool SetData(float* data, size_t size, int usage);
    DLLEXPORT bool SetData(double* data, size_t size, int usage);

    DLLEXPORT Type GetType() const;

    DLLEXPORT int GetDataType() const;
    DLLEXPORT size_t GetNumComponents() const;

private:
    size_t m_num = 0;
    uint32_t m_id = 0;
    int m_dataType = 0;
    Type m_type = Type::kArrayBuffer;
};
