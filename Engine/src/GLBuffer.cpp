#include <glad/gl.h>

#include "Engine/Core/Logging.hpp"
#include "Engine/Graphics/GL/GLBuffer.hpp"

#include "checkError.hpp"

GLBuffer::GLBuffer(Type tp) : m_type{ static_cast<int>(tp) } {
    glGenBuffers(1, &m_id);
    glCheckError();
}

bool GLBuffer::Bind()
{
    glBindBuffer(static_cast<int>(m_type), m_id);
    glCheckError();
    return true;
}

bool GLBuffer::Unbind()
{
    glBindBuffer(static_cast<int>(m_type), 0);
    glCheckError();
    return true;
}

bool GLBuffer::SetData(float* data, size_t bufferSize, int usage)
{
    Bind();
    m_num = bufferSize / sizeof(float);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(float), data, usage);
    glCheckError();
    Unbind();
    m_dataType = GL_FLOAT;
    return true;
}

bool GLBuffer::SetData(unsigned int* data, size_t bufferSize, int usage)
{
    Bind();
    m_num = bufferSize / sizeof(unsigned int);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(unsigned int), data, usage);
    glCheckError();
    Unbind();
    m_dataType = GL_UNSIGNED_INT;
    return true;
}

bool GLBuffer::SetData(int* data, size_t bufferSize, int usage)
{
    Bind();
    m_num = bufferSize / sizeof(int);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(int), data, usage);
    glCheckError();
    Unbind();
    m_dataType = GL_INT;
    return true;
}

bool GLBuffer::SetData(double* data, size_t bufferSize, int usage)
{
    Bind();
    m_num = bufferSize / sizeof(double);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(double), data, usage);
    glCheckError();
    Unbind();
    m_dataType = GL_DOUBLE;
    return true;
}

int GLBuffer::GetDataType() const
{
    return m_dataType;
}

GLBuffer::Type GLBuffer::GetType() const
{
    return m_type;
}

uint32_t GLBuffer::GetId() const
{
    return m_id;
}

size_t GLBuffer::GetNumComponents() const
{
    return m_num;
}
