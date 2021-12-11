#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

#include <glm/glm.hpp>
#include <defines.h>
#include <GameObjects/GameObject.h>
class Manifold;

class CORAL_API PhysicsComponent
{
private:
	AGameObject* m_Owner;

	double m_Mass = 0;
	double m_InvertedMass = 0;

	double m_Elasticity = 0.4;
	double m_StaticFriction = 0.1;
	double m_DynamicFriction = 0.08;

	glm::vec2 m_Velocity = { 0, 0 };
	glm::vec2 m_Acceleration = { 0, 0 };

	static double s_GravityScale;
	static glm::vec2 s_GravityDirection;

	void UpdateVelocity(float deltaTime);
	void UpdatePosition(float deltaTime);
public:
	PhysicsComponent(AGameObject* owner);
	AGameObject* GetOwner() const;

	void SetVelocity(double vx, double vy);
	void SetVelocity(const glm::vec2& vel);

	void SetAcceleration(double ax, double ay);
	void SetAcceleration(const glm::vec2& acc);

	void SetMass(double mass);
	void SetElasticity(double e);

	static void SetGravityScale(double scale);
	static void SetGravityDirection(const glm::vec2 &dir);


	double GetMass() const;
	double GetInvertedMass() const;
	double GetElasticity() const;

	glm::vec2 GetVelocity() const;
	glm::vec2 GetAcceleration() const;


	static void ResolveCollision(Manifold& m);
	static void PositionalCorrection(Manifold& m);

	void Update(float deltaTime);
};

#endif