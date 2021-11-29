#ifndef SHADER_H
#define SHADER_H

#include "defines.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <unordered_map>
#include <iostream>

#define CORAL_STD_VERTEX_SHADER "#version 330 core\n"\
								"layout(location = 0) in vec2 a_Position;\n"\
								"uniform mat4 u_Model;\n"\
								"uniform mat4 u_View;\n"\
								"uniform mat4 u_Projection;\n"\
								"void main()\n"\
								"{\n"\
									"gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0, 1.0);\n"\
								"}\n"

#define CORAL_STD_FRAGMENT_SHADER "#version 330 core\n"\
								  "uniform vec4 u_Color;\n"\
								  "void main()\n"\
								  "{\n"\
										"gl_FragColor = u_Color;\n"\
								  "}\n"

class Shader
{
public:
	Shader();

	void Bind() noexcept;
	void Unbind() noexcept;

	void SetUniformVector(const std::string& name, float value);
	void SetUniformVector(const std::string& name, const glm::vec2& vector);
	void SetUniformVector(const std::string& name, const glm::vec3& vector);
	void SetUniformVector(const std::string& name, const glm::vec4& vector);

	void SetUniformMatrix(const std::string& name, const glm::mat4& matrix);

	~Shader();
private:
	void ShaderInfoLog(uint32_t shaderId, GLenum param);
	void ProgramInfoLog(GLenum param);
private:
	uint32_t m_Id;
	std::unordered_map<std::string, int> m_Uniforms;
};

#endif // !SHADER_H
