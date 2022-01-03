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
    return true;
}

GLBuffer::Type GLBuffer::GetType() const
{
    return m_type;
}

uint32_t GLBuffer::GetId() const
{
    return m_id;
}

size_t GLBuffer::GetNumEntries() const
{
    return m_num;
}
