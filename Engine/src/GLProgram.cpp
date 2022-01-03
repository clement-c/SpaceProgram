#include <glad/gl.h>

#include "Engine/Core/Logging.hpp"
#include "Engine/Graphics/GL/GLProgram.hpp"

#include "checkError.hpp"

std::string const GLProgram::DefaultVertexSource = R"vert(#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})vert";

std::string const GLProgram::DefaultFragmentSource = R"frag(#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.67f, 0.67f, 0.67f, 1.0f);
})frag";

GLProgram::GLProgram() {
	m_id = glCreateProgram();
	glCheckError();
}

bool GLProgram::SetShader(GLShader::Type shaderType, std::string const& src)
{
	if (m_linked) {
		CC_LOG_ERROR("Cannot set a shader after the program was linked.\n");
	}
	CC_LOG_DEBUG("Adding shader {} to program\n", static_cast<uint32_t>(shaderType));

	auto pair = m_shaders.try_emplace(shaderType, shaderType);
	auto& shader = (*pair.first).second;
	shader.SetSource(src);
	return shader.Compile();
}

int GLProgram::GetInfo(GLProgram::InfoType tp) const
{
	int v;
	glGetProgramiv(m_id, static_cast<int>(tp), &v);
	glCheckError();
	return v;
}

std::string GLProgram::GetInfoLog() const
{
	int length = GetInfo(GLProgram::InfoType::kInfoLogLength);
	if(length < 1) return "";

	char* infoLog = new char[length];
	glGetProgramInfoLog(m_id, length, NULL, infoLog);
	glCheckError();
	std::string log(infoLog);
	delete[] infoLog;

	return log;
}

bool GLProgram::Link(bool deleteShaders)
{
	if (m_linked) {
		CC_LOG_ERROR("Cannot link a program that was already linked.\n");
	}
	CC_LOG_DEBUG("Linking program...\n");

	if (m_shaders.find(GLShader::Type::kVertex) == m_shaders.cend())
	{
		CC_LOG_DEBUG("Adding the default vertex shader...\n");
		if (!SetShader(GLShader::Type::kVertex, GLProgram::DefaultVertexSource))
		{
			CC_LOG_ERROR("Failed to add the default vertex shader!\n");
			return false;
		}
	}

	if (m_shaders.find(GLShader::Type::kFragment) == m_shaders.cend())
	{
		CC_LOG_DEBUG("Adding the default fragment shader...\n");
		if (!SetShader(GLShader::Type::kFragment, GLProgram::DefaultFragmentSource))
		{
			CC_LOG_ERROR("Failed to add the default fragment shader!\n");
			return false;
		}
	}

	CC_LOG_DEBUG("  Program has {} shaders, attaching them...\n", m_shaders.size());

	for (auto& shaderPair : m_shaders)
	{
		auto& shader = shaderPair.second;
		glAttachShader(m_id, shader.GetId());
		glCheckError();
		if(glGetError() != GL_NO_ERROR) CC_LOG_WARNING("Error attaching shader\n");
	}

	glLinkProgram(m_id);
	glCheckError();

	int success = GetInfo(InfoType::kLinkStatus);
	if (success == GL_FALSE) {
		CC_LOG_ERROR("--> Error while compiling: {}\n", GetInfoLog());
		return false;
	}
	m_linked = true;

	if (m_linked && deleteShaders)
	{
		for (auto& shaderPair : m_shaders)
		{
			shaderPair.second.Delete();
		}
	}

	glValidateProgram(m_id);
	glCheckError();
	CC_LOG_DEBUG("Program validated, log: {}\n", GetInfoLog());

	return m_linked;
}

bool GLProgram::Use()
{
	if (!m_linked) if (!Link()) return false;
	glUseProgram(m_id);
	return true;
}
