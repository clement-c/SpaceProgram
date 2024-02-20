#pragma once
#include "GLBuffer.hpp"
#include <map>
#include <memory>
#include <tuple>

class GLVAO
{
public:
	using AttribPointerType = std::tuple<int /* data size 1/2/3/4 */, int /* gl type */, bool /* normalize */, int /* total size */, void * /* offset */>;

	enum class DrawType
	{
		kPoints = GL_POINTS,
		kLineStrip = GL_LINE_STRIP,
		kLineLoop = GL_LINE_LOOP,
		kLines = GL_LINES,
		kLineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
		kLineAdjacency = GL_LINES_ADJACENCY,
		kTriangleStrip = GL_TRIANGLE_STRIP,
		kTriangleFan = GL_TRIANGLE_FAN,
		kTriangles = GL_TRIANGLES,
		kTriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
		kTrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
		kPatches = GL_PATCHES
	};

	DLLEXPORT GLVAO() = delete;
	DLLEXPORT GLVAO(GLVAO const &) = delete;
    DLLEXPORT ~GLVAO();
	/**
	 * @brief Creates a VAO from a GL Buffer and a description of attributes
	 * 		  (as used iun the glVertexAttribPointer function) per layout index
	 * 
	 * @param buffer 	Buffer containing the data for the vertices
	 * @param attributesLayout 	Lists the layout for each attribute. 
	 * 							The map key (int) should be the same than the `layout=key` in the vertex shader
	 */
	DLLEXPORT GLVAO(GLBuffer &buffer, std::map<int, AttribPointerType> const & attributesLayout);

	DLLEXPORT uint32_t GetId() const;

	DLLEXPORT bool Bind() const;
	DLLEXPORT bool Unbind() const;

	DLLEXPORT bool Draw(DrawType, int first = 0, int length = -1) const;

private:
	size_t m_length;
	uint32_t m_id;
	std::shared_ptr<GLBuffer> m_buffer;
};
