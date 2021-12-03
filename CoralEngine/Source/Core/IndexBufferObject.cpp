#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject(GLenum usage)
	: m_Usage(usage)
{
	glCreateBuffers(1, &m_BufferId);
}

void IndexBufferObject::SendData(const std::vector<uint32_t>& indecies)
{
	m_Data = indecies;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		indecies.size() * sizeof(uint32_t), 
		indecies.data(), 
		m_Usage);
}

void IndexBufferObject::Bind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void IndexBufferObject::Unbind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBufferObject::~IndexBufferObject()
{
	glDeleteBuffers(1, &m_BufferId);
}
