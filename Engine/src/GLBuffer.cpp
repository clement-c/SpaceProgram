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

bool GLBuffer::SetData(float const* data, size_t bufferSize, GLBuffer::Usage usage)
{
    Bind();
    m_num = bufferSize / sizeof(float);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(float), data, static_cast<int>(usage));
    glCheckError();
    Unbind();
    m_dataType = GL_FLOAT;
    return true;
}

bool GLBuffer::SetData(unsigned int const* data, size_t bufferSize, GLBuffer::Usage usage)
{
    Bind();
    m_num = bufferSize / sizeof(unsigned int);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(unsigned int), data, static_cast<int>(usage));
    glCheckError();
    Unbind();
    m_dataType = GL_UNSIGNED_INT;
    return true;
}

bool GLBuffer::SetData(int const* data, size_t bufferSize, GLBuffer::Usage usage)
{
    Bind();
    m_num = bufferSize / sizeof(int);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(int), data, static_cast<int>(usage));
    glCheckError();
    Unbind();
    m_dataType = GL_INT;
    return true;
}

bool GLBuffer::SetData(double const* data, size_t bufferSize, GLBuffer::Usage usage)
{
    Bind();
    m_num = bufferSize / sizeof(double);
    glBufferData(static_cast<int>(m_type), m_num * sizeof(double), data, static_cast<int>(usage));
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
