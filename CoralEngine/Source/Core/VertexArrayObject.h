#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include "defines.h"

#include <unordered_map>
#include <array>

class VertexArrayObject
{
public:
	typedef std::unordered_map<int, std::array<int, 3>> VertexAttribs;

	VertexArrayObject();

	void Bind() noexcept;
	void Unbind() noexcept;

	void SetVertexAttribs(const VertexAttribs& vertexAttribs);

	~VertexArrayObject();
private:
	uint32_t m_Id;
};

#endif // !VERTEX_ARRAY_OBJECT_H
