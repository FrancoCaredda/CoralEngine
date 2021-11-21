#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
{
	m_Id = glCreateProgram();

	// TODO: EXCEPTIONS
}

void ShaderProgram::AttachShader(const Shader& shader)
{
	glAttachShader(m_Id, shader.m_Id);
}

bool ShaderProgram::Link()
{
	glLinkProgram(m_Id);
	
	int status;
	glGetProgramiv(m_Id, GL_LINK_STATUS, &status);

	if (!status)
		return false;

	glValidateProgram(m_Id);

	glGetProgramiv(m_Id, GL_VALIDATE_STATUS, &status);

	if (!status)
		return false;

	return true;
}

void ShaderProgram::SetUniformVector(const std::string& name, float x) noexcept
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniform1f(m_Uniforms[name], x);
		return;
	}

	m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());
	glUniform1f(m_Uniforms[name], x);
}

void ShaderProgram::SetUniformVector(const std::string& name, const glm::vec2& vector) noexcept
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniform2fv(m_Uniforms[name], 1, glm::value_ptr(vector));
		return;
	}

	m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());
	glUniform2fv(m_Uniforms[name], 1, glm::value_ptr(vector));
}

void ShaderProgram::SetUniformVector(const std::string& name, const glm::vec3& vector) noexcept
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniform3fv(m_Uniforms[name], 1, glm::value_ptr(vector));
		return;
	}

	m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());
	glUniform3fv(m_Uniforms[name], 1, glm::value_ptr(vector));
}

void ShaderProgram::SetUniformVector(const std::string& name, const glm::vec4& vector) noexcept
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniform4fv(m_Uniforms[name], 1, glm::value_ptr(vector));
		return;
	}

	m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());
	glUniform4fv(m_Uniforms[name], 1, glm::value_ptr(vector));
}

void ShaderProgram::SetUniformMatrix(const std::string& name, const glm::mat4& matrix) noexcept
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniformMatrix4fv(m_Uniforms[name], 1, false, glm::value_ptr(matrix));
		return;
	}

	m_Uniforms[name] = glGetUniformLocation(m_Id, name.c_str());
	glUniformMatrix4fv(m_Uniforms[name], 1, false, glm::value_ptr(matrix));
}

void ShaderProgram::Use()
{
	glUseProgram(m_Id);
}

void ShaderProgram::Unuse()
{
	glUseProgram(0);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_Id);
}
