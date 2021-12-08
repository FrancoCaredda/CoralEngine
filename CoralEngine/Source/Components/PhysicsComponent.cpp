#include "PhysicsComponent.h"
#include <Components/BoxCollider.h>
#include <Components/Transform.h>

#include <iostream>

double PhysicsComponent::s_GravityScale = 9.8;
glm::vec2 PhysicsComponent::s_GravityDirection = {0, -1};

PhysicsComponent::PhysicsComponent(AGameObject* owner) : m_Owner(owner)
{}

AGameObject* PhysicsComponent::GetOwner() const
{
	return m_Owner;
}

void PhysicsComponent::SetVelocity(double vx, double vy)
{
	m_Velocity.x = vx;
	m_Velocity.y = vy;
}

void PhysicsComponent::SetVelocity(const glm::vec2& vel)
{
	m_Velocity = vel;
}

void PhysicsComponent::SetAcceleration(double ax, double ay)
{
	m_Acceleration.x = ax;
	m_Acceleration.y = ay;
}

void PhysicsComponent::SetAcceleration(const glm::vec2& acc)
{
	m_Acceleration = acc;
}

void PhysicsComponent::SetMass(double mass)
{
	m_Mass = mass;

	if (abs(mass) < 0.0000001)
	{
		m_InvertedMass = 0;
	}
	else
	{
		m_InvertedMass = (double)1 / mass;
	}
}

void PhysicsComponent::SetElasticity(double e)
{
	m_Elasticity = e;
}

double PhysicsComponent::GetMass() const
{
	return m_Mass;
}

void PhysicsComponent::SetGravityScale(double scale)
{
	s_GravityScale = scale;
}

double PhysicsComponent::GetInvertedMass() const
{
	return m_InvertedMass;
}

void PhysicsComponent::SetGravityDirection(const glm::vec2 &dir)
{
	s_GravityDirection = glm::normalize(dir);
}

double PhysicsComponent::GetElasticity() const
{
	return m_Elasticity;
}

glm::vec2 PhysicsComponent::GetVelocity() const
{
	return m_Velocity;
}

glm::vec2 PhysicsComponent::GetAcceleration() const
{
	return m_Acceleration;
}

glm::vec2 operator* (const glm::vec2& vec, double scalar)
{
	glm::vec2 res = vec;
	res.x *= scalar;
	res.y *= scalar;

	return res;
}

glm::vec2 operator* (double scalar, const glm::vec2& vec)
{
	return vec*scalar;
}

void PhysicsComponent::ResolveCollision( Manifold& m)
{
	// calculating relative speed
	glm::vec2 rv = m.B->GetVelocity() - m.A->GetVelocity();

	// calculating relative speed along the nolmal
	double velAlongNormal = glm::dot(rv, m.normal);

	// dont do anything if objects move in different directions
	if (velAlongNormal > 0)
		return;

	std::cout << "Test\n";

	// calculating less elasticity
	double e = std::min(m.A->GetElasticity(), m.B->GetElasticity());

	// calculating momentum of force
	double j = -(1 + e) * velAlongNormal;
	j /= m.A->GetInvertedMass() + m.B->GetInvertedMass();

	// applies a momentum of force
	glm::vec2 impulse = j * m.normal;

	m.A->SetVelocity(m.A->GetVelocity() - (m.A->GetInvertedMass() * impulse) );
	m.B->SetVelocity(m.B->GetVelocity() + (m.B->GetInvertedMass() * impulse) );

	//=========================================
	// RESOLIVING FRICTION
	//=========================================
	// calculating tangent vector
	glm::vec2 tangent = rv - (glm::dot(rv, m.normal) * m.normal);

	if (abs(glm::length(tangent)) > 0.0000001)
	{
		tangent = glm::normalize(tangent);
	}

	// calculating momentum of friction force
	double jt = -glm::dot(rv, tangent);
	jt /= (m.A->m_InvertedMass + m.B->m_InvertedMass);

	// calculating friction coefficient
	double mu = sqrt(m.A->m_StaticFriction * m.A->m_StaticFriction + m.B->m_StaticFriction * m.B->m_StaticFriction);

	glm::vec2 frictionImpulse;
	if (abs(jt) < j * mu)
	{
		frictionImpulse = jt * tangent;
		if (m.B->GetOwner()->GetName() == "Box1") 
		{
			std::cout << m.B->GetOwner()->GetName() <<"  Static  " << m.A->GetOwner()->GetName() << std::endl;
		}
	}
	else
	{
		if (m.B->GetOwner()->GetName() == "Box1")
		{
			std::cout << m.B->GetOwner()->GetName() << "  Dynamic  " << m.A->GetOwner()->GetName() << std::endl;
		}
		double dynamicFriction = sqrt(m.A->m_DynamicFriction * m.A->m_DynamicFriction +
										m.B->m_DynamicFriction * m.B->m_DynamicFriction);
		frictionImpulse = -j * tangent * dynamicFriction;
	}

	m.A->SetVelocity(m.A->GetVelocity() - (m.A->GetInvertedMass() * frictionImpulse));
	m.B->SetVelocity(m.B->GetVelocity() + (m.B->GetInvertedMass() * frictionImpulse));
}

void PhysicsComponent::PositionalCorrection(Manifold& m)
{
	const double percent = 0.2; // usually from 0.2 to 0.8
	const float slop = 0.01;	// usually from 0.01 to 0.1

	glm::vec2 correction = std::max(m.penetration - slop, 0.0f) / 
		(m.A->GetInvertedMass() + m.B->GetInvertedMass()) * percent * m.normal;

	m.A->GetOwner()->GetTransform()->Translate(glm::vec3(-m.A->GetInvertedMass() * correction, 0));
	m.B->GetOwner()->GetTransform()->Translate(glm::vec3(m.B->GetInvertedMass() * correction, 0));
}

void PhysicsComponent::Update(float deltaTime)
{
	UpdateVelocity(deltaTime);

	UpdatePosition(deltaTime);
}

void PhysicsComponent::UpdateVelocity(float deltaTime)
{
	m_Velocity += m_Acceleration * deltaTime;
	// using gravity
	m_Velocity += s_GravityScale * s_GravityDirection * deltaTime * m_Mass;
}

void PhysicsComponent::UpdatePosition(float deltaTime)
{
	m_Owner->GetComponent<Transform>()->Translate(glm::vec3(m_Velocity * deltaTime, 0));
}
