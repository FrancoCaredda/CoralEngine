#include "VertexArrayObject.h"

#define VOID_POINTER(X) (const void*)(X)

VertexArrayObject::VertexArrayObject()
{
	glCreateVertexArrays(1, &m_Id);

	//TODO: Exception when vao isn't created
}

void VertexArrayObject::Bind() noexcept
{
	glBindVertexArray(m_Id);
}

void VertexArrayObject::Unbind() noexcept
{
	glBindVertexArray(0);
}

void VertexArrayObject::SetVertexAttribs(const VertexAttribs& vertexAttribs)
{
	for (auto i = vertexAttribs.cbegin(); i != vertexAttribs.cend(); i++)
	{
		glVertexAttribPointer(i->first, i->second[0],
			GL_FLOAT, false,
			i->second[1] * sizeof(float),
			VOID_POINTER(i->second[2] * sizeof(float)));
	}

	for (auto i = vertexAttribs.cbegin(); i != vertexAttribs.cend(); i++)
	{
		glEnableVertexAttribArray(i->first);
	}
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_Id);
}
