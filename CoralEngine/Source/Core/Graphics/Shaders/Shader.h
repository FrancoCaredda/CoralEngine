#ifndef SHADER_H
#define SHADER_H

#include "defines.h"

#include <string>

class CORAL_API Shader
{
public:
	Shader(GLenum type);

	void Load(const std::string& fileName);
	bool Compile();

	~Shader();

	friend class ShaderProgram;
private:
	uint32_t m_Id;
	GLenum m_Type;
};

#endif // !SHADER_H
