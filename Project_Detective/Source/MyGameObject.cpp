#include "MyGameObject.h"

#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"
#include "Components/PhysicsComponent.h"



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
	sprite->SetShaderProgram(m_Program);
	
	BoxCollider* collider = AddComponent<BoxCollider>();
	//m_Transform = AddComponent<Transform>();

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
}

void MyGameObject::Update(float deltaTime)
{
	//GetComponent<Transform>()->Translate(glm::vec3(m_Speed * deltaTime, 0.0f, 0.0f));
	//glm::vec3 position = m_Transform->GetPosition();
	PhysicsComponent* physics = GetComponent<PhysicsComponent>();
	physics->Update(deltaTime);

	if (GetComponent<Transform>()->GetPosition().x <= 0)
		physics->SetVelocity(abs(physics->GetVelocity().x), physics->GetVelocity().y);
	if (GetComponent<Transform>()->GetPosition().x >= 600 - GetComponent<BoxCollider>()->GetWidth())
		physics->SetVelocity(abs(physics->GetVelocity().x) * -1, physics->GetVelocity().y);

	if (GetComponent<Transform>()->GetPosition().y <= 0)
		physics->SetVelocity(physics->GetVelocity().x, abs(physics->GetVelocity().y));
	if (GetComponent<Transform>()->GetPosition().y >= 480 - GetComponent<BoxCollider>()->GetHeight())
		physics->SetVelocity(physics->GetVelocity().x, abs(physics->GetVelocity().y)*-1);
}

MyGameObject::~MyGameObject()
{
	delete m_Program;
}
