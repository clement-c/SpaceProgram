#include <glad/gl.h>

#include "Engine/Core/Logging.hpp"
#include "Engine/Graphics/GL/GLVAO.hpp"

#include "checkError.hpp"

GLVAO::GLVAO(std::map<int, AttribPointerType> const& attribs)
{
	m_length = 0;
	glGenVertexArrays(1, &m_id);
	glCheckError();
	glBindVertexArray(m_id);
	glCheckError();
	for (auto& idAttrib : attribs)
	{
		auto& tup = idAttrib.second;
		auto& buffer = std::get<0>(tup);
		auto data_size = std::get<1>(tup);
		m_length = (buffer.GetNumComponents() / data_size);
		auto gl_type = std::get<2>(tup);
		bool normalize = std::get<3>(tup);
		auto total_size = std::get<4>(tup);
		auto offset = std::get<5>(tup);

		buffer.Bind();
		glVertexAttribPointer(idAttrib.first, data_size, gl_type, normalize, total_size, offset);
		glEnableVertexAttribArray(idAttrib.first);
    	glCheckError();
	}
	glBindVertexArray(0);
	glCheckError();
}

uint32_t GLVAO::GetId() const
{
	return m_id;
}

bool GLVAO::Bind() const
{
	glBindVertexArray(m_id);
	glCheckError();
	return true;
}

bool GLVAO::Unbind() const
{
	glBindVertexArray(0);
	glCheckError();
	return true;
}

bool GLVAO::Draw(DrawType dt, int first, int length) const
{
	if (!Bind()) return false;
	length = (length < 0) ? (m_length - first) : length;
	glDrawArrays(static_cast<int>(dt), first, length);
	glCheckError();
	Unbind();
	return true;
}
