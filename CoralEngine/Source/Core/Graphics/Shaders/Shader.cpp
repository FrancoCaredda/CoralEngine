#include "Shader.h"

#include <fstream>

Shader::Shader(GLenum type)
{
	m_Id = glCreateShader(type);

	//TODO: exception
}

void Shader::Load(const std::string& fileName)
{
	FILE* file = fopen(fileName.c_str(), "rt");

	if (!file)
	{
		printf("File is wasn\'t opened!");
		return;
	}

	char line[BUFFER_SIZE] = { 0 };
	std::string source;

	while (fgets(line, BUFFER_SIZE, file) != nullptr)
	{
		source += line;

		if (feof(file) || ferror(file))
			break;
	}

	const char* csource = source.c_str();
	int length = strlen(csource);

	glShaderSource(m_Id, 1, &csource, 0);

	fclose(file);
}

bool Shader::Compile()
{
	glCompileShader(m_Id);

	int status;
	glGetShaderiv(m_Id, GL_COMPILE_STATUS, &status);

	return status;
}

Shader::~Shader()
{
	glDeleteShader(m_Id);
}
