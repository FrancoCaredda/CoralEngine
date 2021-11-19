#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLenum slot, GLenum usage)
	: m_Slot(slot), m_Usage(usage)
{
	glCreateBuffers(1, &m_BufferId);
}

void VertexBufferObject::SendData(const std::vector<float>& vertexData)
{
	glBufferData(m_Slot,
		vertexData.size() * sizeof(float), 
		vertexData.data(),
		m_Usage);
}

void VertexBufferObject::Bind() const noexcept
{
	glBindBuffer(m_Slot, m_BufferId);
}

void VertexBufferObject::Unbind() const noexcept
{
	glBindBuffer(m_Slot, 0);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_BufferId);
}
