#include "Shader.h"

Shader::Shader()
{
	m_Id = glCreateProgram();
	
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexSource = CORAL_STD_VERTEX_SHADER;
	const char* fragmentSource = CORAL_STD_FRAGMENT_SHADER;

	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	ShaderInfoLog(vertexShader, GL_COMPILE_STATUS);
	ShaderInfoLog(fragmentShader, GL_COMPILE_STATUS);

	glAttachShader(m_Id, vertexShader);
	glAttachShader(m_Id, fragmentShader);

	glLinkProgram(m_Id);
	ProgramInfoLog(GL_LINK_STATUS);

	glValidateProgram(m_Id);
	ProgramInfoLog(GL_VALIDATE_STATUS);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Bind() noexcept
{
	glUseProgram(m_Id);
}

void Shader::Unbind() noexcept
{
	glUseProgram(0);
}

void Shader::SetUniformVector(const std::string& name, float value)
{
	if (m_Uniforms.find(name) == m_Uniforms.end())
		m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());

	if (m_Uniforms[name] == -1)
	{
		std::string message = "Uniform " + name + " does not exist!";
		throw std::exception(message.c_str());
	}

	glUniform1f(m_Uniforms[name], value);
}

void Shader::SetUniformVector(const std::string& name, const glm::vec2& vector)
{
	if (m_Uniforms.find(name) == m_Uniforms.end())
		m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());

	if (m_Uniforms[name] == -1)
	{
		std::string message = "Uniform " + name + " does not exist!";
		throw std::exception(message.c_str());
	}

	glUniform2fv(m_Uniforms[name], 1, glm::value_ptr(vector));
}

void Shader::SetUniformVector(const std::string& name, const glm::vec3& vector)
{
	if (m_Uniforms.find(name) == m_Uniforms.end())
		m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());

	if (m_Uniforms[name] == -1)
	{
		std::string message = "Uniform " + name + " does not exist!";
		throw std::exception(message.c_str());
	}

	glUniform3fv(m_Uniforms[name], 1, glm::value_ptr(vector));
}

void Shader::SetUniformVector(const std::string& name, const glm::vec4& vector)
{
	if (m_Uniforms.find(name) == m_Uniforms.end())
		m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());

	if (m_Uniforms[name] == -1)
	{
		std::string message = "Uniform " + name + " does not exist!";
		throw std::exception(message.c_str());
	}

	glUniform4fv(m_Uniforms[name], 1, glm::value_ptr(vector));
}

void Shader::SetUniformMatrix(const std::string& name, const glm::mat4& matrix)
{
	if (m_Uniforms.find(name) == m_Uniforms.end())
		m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());

	if (m_Uniforms[name] == -1)
	{
		std::string message = "Uniform " + name + " does not exist!";
		throw std::exception(message.c_str());
	}

	glUniformMatrix4fv(m_Uniforms[name], 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::ShaderInfoLog(uint32_t shaderId, GLenum param)
{
	char Buffer[BUFFER_SIZE];
	int status;
	glGetShaderiv(shaderId, param, &status);

	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(shaderId, BUFFER_SIZE, nullptr, Buffer);
		std::cerr << Buffer << std::endl;
		throw std::exception(Buffer);
	}
	else 
	{
		std::cout << "Shader compilation complete!" << std::endl;
	}
}

void Shader::ProgramInfoLog(GLenum param)
{
	char Buffer[BUFFER_SIZE];
	int status;
	glGetProgramiv(m_Id, param, &status);

	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(m_Id, BUFFER_SIZE, nullptr, Buffer);
		std::cerr << Buffer << std::endl;
		throw std::exception(Buffer);
	}
}
