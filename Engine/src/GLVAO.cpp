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
		std::get<0>(tup).Bind();
		m_length = (std::get<0>(tup).GetNumEntries() / std::get<1>(tup));
		glVertexAttribPointer(idAttrib.first, std::get<1>(tup), std::get<2>(tup), std::get<3>(tup), std::get<4>(tup), std::get<5>(tup));
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
	length = (length < 1) ? (m_length - first) : length;
	glDrawArrays(static_cast<int>(dt), first, length);
	glCheckError();
	Unbind();
	return true;
}
