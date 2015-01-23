#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(RigidBody* rigidBody, CollisionPrimitive* collider, const Vector3& position, const Quaternion& rotation, float scale) :
	GameObject(position, rotation, scale),
	m_collider(collider)
{
	m_collider->m_body = rigidBody;

	m_collider->m_body->m_owner = getTransform();

	addComponent(collider);
}

void PhysicsObject::update(float delta)
{
	m_collider->m_body->integrate(delta);

	GameObject::update(delta);
}