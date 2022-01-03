#pragma once
#include "GLBuffer.hpp"
#include <map>
#include <memory>
#include <tuple>

class GLVAO
{
public:

	using AttribPointerType = std::tuple<GLBuffer&, int /* data size 1/2/3/4 */, int /* gl type */, bool /* normalize */, int /* total size */, void* /* offset */>;

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
	DLLEXPORT GLVAO(GLVAO const&) = delete;
	DLLEXPORT GLVAO(std::map<int, AttribPointerType> const&);

	DLLEXPORT uint32_t GetId() const;
	DLLEXPORT bool Bind() const;
	DLLEXPORT bool Unbind() const;

	DLLEXPORT bool Draw(DrawType, int first = 0, int length = 0) const;

private:
	size_t m_length;
	uint32_t m_id;
	std::shared_ptr<GLBuffer> m_buffer;
};
