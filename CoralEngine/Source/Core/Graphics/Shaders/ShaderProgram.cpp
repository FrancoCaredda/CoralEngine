#include "ShaderProgram.h"

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
