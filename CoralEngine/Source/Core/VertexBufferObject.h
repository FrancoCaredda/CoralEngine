#ifndef VERTEX_BUFFER_OBJECT
#define VERTEX_BUFFER_OBJECT

#include "defines.h"

#include <vector>
#include <cstdint>

class VertexBufferObject
{
public:
	VertexBufferObject(GLenum slot, GLenum usage);
	VertexBufferObject(const VertexBufferObject&) = delete;

	VertexBufferObject& operator=(const VertexBufferObject&) = delete;
	
	void Allocate(size_t size);
	// Requires Allocate call
	void Push(void* data, size_t size, int offset);
	void SendData(const std::vector<float>& vertexData);

	void Bind() const noexcept;
	void Unbind() const noexcept;

	~VertexBufferObject();
private:
	uint32_t m_BufferId;
	GLenum m_Slot;
	GLenum m_Usage;
};

#endif // !VERTEX_BUFFER_OBJECT