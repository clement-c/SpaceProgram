#include <glad/gl.h>

#include "Engine/Graphics/GL/GLShader.hpp"
#include "Engine/Core/Logging.hpp"

#include "checkError.hpp"

GLShader::GLShader(GLShader::Type tp)
{
	m_id = glCreateShader(static_cast<GLenum>(tp));
	glCheckError();
}

uint32_t GLShader::GetId() const
{
	return m_id;
}

bool GLShader::SetSource(std::string const& src)
{
	char const* chars = src.c_str();
	glShaderSource(m_id, 1, &chars, nullptr);
	glCheckError();
	return true;
}

bool GLShader::Compile()
{
	CC_LOG_DEBUG("Compiling shader...\n");
	glCompileShader(m_id);
	int success = GetInfo(GLShader::InfoType::kCompileStatus);
	if (!success)
	{
		CC_LOG_ERROR("Error while compiling the shader: {}\n", GetInfoLog());
		return false;
	}
	return true;
}

bool GLShader::Delete()
{
	glDeleteShader(m_id);
	glCheckError();
	return true;
}

int GLShader::GetInfo(GLShader::InfoType tp) const
{
	int v;
	glGetShaderiv(m_id, static_cast<int>(tp), &v);
	glCheckError();
	return v;
}

std::string GLShader::GetInfoLog() const
{
	int length = GetInfo(GLShader::InfoType::kInfoLogLength);
	if(length < 1) return "";
	char* infoLog = new char[length];
	glGetShaderInfoLog(m_id, length, NULL, infoLog);
	glCheckError();
	std::string log(infoLog);
	delete[] infoLog;
	return log;
}
