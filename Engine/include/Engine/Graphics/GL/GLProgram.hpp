#pragma once

#include "../../Core/Lib.hpp"

#include "GLShader.hpp"
#include <string>
#include <unordered_map>

class GLProgram
{
public:
	enum class InfoType
	{
		kDeleteStatus = GL_DELETE_STATUS,
		kLinkStatus = GL_LINK_STATUS,
		kValidateStatus = GL_VALIDATE_STATUS,
		kInfoLogLength = GL_INFO_LOG_LENGTH,
		kAttachedShaders = GL_ATTACHED_SHADERS,
		kActiveAtomicCounterBuffers = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
		kActiveAttributes = GL_ACTIVE_ATTRIBUTES,
		kActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
		kActiveUniforms = GL_ACTIVE_UNIFORMS,
		kActiveUniformBlocks = GL_ACTIVE_UNIFORM_BLOCKS,
		kActiveUniformMaxNameLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
		kActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH,
		kComputeWorkGroupSize = GL_COMPUTE_WORK_GROUP_SIZE,
		kProgramBinaryLength = GL_PROGRAM_BINARY_LENGTH,
		kTransformFeedbackBufferMode = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
		kTransformFeedbackVaryings = GL_TRANSFORM_FEEDBACK_VARYINGS,
		kTransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
		kGeometryVerticesOut = GL_GEOMETRY_VERTICES_OUT,
		kGeometryInputType = GL_GEOMETRY_INPUT_TYPE,
		kGeometryOutputType = GL_GEOMETRY_OUTPUT_TYPE
	};

	DLLEXPORT static std::string const DefaultVertexSource;
	DLLEXPORT static std::string const DefaultFragmentSource;

	DLLEXPORT GLProgram();
	DLLEXPORT GLProgram(std::string const &vtxSource, std::string const &fragSource);

	DLLEXPORT uint32_t GetId() const;
	DLLEXPORT int GetInfo(InfoType) const;
	DLLEXPORT std::string GetInfoLog() const;

	DLLEXPORT bool SetShader(GLShader::Type shaderType, std::string const &src);
	DLLEXPORT GLShader *const GetShader(GLShader::Type shaderType);

	DLLEXPORT bool Link(bool deleteShaders = true);
	DLLEXPORT bool Use();

	DLLEXPORT bool SetUniform(std::string const uniformName, int value);			 // GLShader::Type,
	DLLEXPORT bool SetUniform(std::string const uniformName, float value);			 // GLShader::Type,
	DLLEXPORT bool SetUniform(std::string const uniformName, double value);			 // GLShader::Type,
	DLLEXPORT bool SetUniform(std::string const uniformName, Vector3 const &value); // GLShader::Type,
	DLLEXPORT bool SetUniform(std::string const uniformName, Matrix44 const &value); // GLShader::Type,
	// bool SetUniform(GLShader::Type, std::string const uniformName, glm::mat4 const&);

	DLLEXPORT int GetNumActiveUniforms() const;
	DLLEXPORT std::string GetUniformName(int index) const;

private:
	std::unordered_map<GLShader::Type, GLShader> m_shaders;
	uint32_t m_id = 0;
	bool m_linked = false;
};
