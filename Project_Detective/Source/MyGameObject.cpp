#include "MyGameObject.h"

#include "Components/Sprite.h"
#include "Components/Transform.h"

void MyGameObject::Start()
{
	Shader fragmentShader(GL_FRAGMENT_SHADER);
	Shader vertexShader(GL_VERTEX_SHADER);

	fragmentShader.Load("Assets/Shaders/Rectangle.frag.glsl");
	vertexShader.Load("Assets/Shaders/Rectangle.vert.glsl");

	fragmentShader.Compile();
	vertexShader.Compile();

	m_Program = new ShaderProgram();
	m_Program->AttachShader(fragmentShader);
	m_Program->AttachShader(vertexShader);

	m_Program->Link();

	Sprite* sprite = AddComponent<Sprite>();
	m_Transform = AddComponent<Transform>();

	sprite->SetShaderProgram(m_Program);
}

void MyGameObject::Update(float deltaTime)
{
	m_Transform->Translate(glm::vec3(m_Speed * deltaTime, 0.0f, 0.0f));
	//glm::vec3 position = m_Transform->GetPosition();


	//if (position.x <= 0 || position.x >= 600)
		//m_Speed *= -1;
}

MyGameObject::~MyGameObject()
{
	delete m_Program;
}
