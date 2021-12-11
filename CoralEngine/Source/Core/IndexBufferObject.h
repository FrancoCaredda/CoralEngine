#ifndef INDEX_BUFFER_OBJECT
#define INDEX_BUFFER_OBJECT

#include "defines.h"

#include <vector>

class IndexBufferObject
{
public:
	IndexBufferObject(GLenum usage);
	IndexBufferObject(const IndexBufferObject&) = delete;

	void SendData(const std::vector<uint32_t>& indecies);

	void Bind() const noexcept;
	void Unbind() const noexcept;

	inline std::vector<uint32_t> GetData() const noexcept { return m_Data; }

	~IndexBufferObject();
private:
	uint32_t m_BufferId;
	GLenum m_Slot;
	GLenum m_Usage;

	std::vector<uint32_t> m_Data;
};

#endif