#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "Shader.h"

class CORAL_API ShaderProgram
{
public:
	ShaderProgram();

	void AttachShader(const Shader& shader);
	bool Link();

	void Use();
	void Unuse();

	~ShaderProgram();
private:
	uint32_t m_Id;
};


#endif // !SHADER_PROGRAM