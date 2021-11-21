#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "defines.h"
#include "Shader.h"

#include "glm/glm.hpp"

#include <unordered_map>

class CORAL_API ShaderProgram
{
public:
	ShaderProgram();

	void AttachShader(const Shader& shader);
	bool Link();

	void SetUniformVector(const std::string& name, float x) noexcept;
	void SetUniformVector(const std::string& name, const glm::vec2& vector) noexcept;
	void SetUniformVector(const std::string& name, const glm::vec3& vector) noexcept;
	void SetUniformVector(const std::string& name, const glm::vec4& vector) noexcept;

	void SetUniformMatrix(const std::string& name, const glm::mat4& matrix) noexcept;

	void Use();
	void Unuse();

	~ShaderProgram();
private:
	uint32_t m_Id;
	std::unordered_map<std::string, int> m_Uniforms;
};


#endif // !SHADER_PROGRAM