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
	Transform* transform = AddComponent<Transform>();

	sprite->SetShaderProgram(m_Program);
}

void MyGameObject::Update(float deltaTime)
{
}

MyGameObject::~MyGameObject()
{
	delete m_Program;
}
