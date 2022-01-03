#pragma once
#include <glad/gl.h>
#include <stdint.h>
#include <string>

class GLShader
{
public:
	enum class Type
	{
		kCompute = GL_COMPUTE_SHADER,
		kVertex = GL_VERTEX_SHADER,
		kTesselationControl = GL_TESS_CONTROL_SHADER,
		kTesselationEvaluation = GL_TESS_EVALUATION_SHADER,
		kGeometry = GL_GEOMETRY_SHADER,
		kFragment = GL_FRAGMENT_SHADER
	};

	enum class InfoType
	{
		kShaderType = GL_SHADER_TYPE,
		kDeleteStatus = GL_DELETE_STATUS,
		kCompileStatus = GL_COMPILE_STATUS,
		kInfoLogLength = GL_INFO_LOG_LENGTH,
		kShaderSourceLength = GL_SHADER_SOURCE_LENGTH
	};

	GLShader(Type tp);

	uint32_t GetId() const;

	bool SetSource(std::string const& src);
	bool Compile();
	bool Delete();

	int GetInfo(InfoType) const;
	std::string GetInfoLog() const;

private:
	uint32_t m_id;
};
