#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const Vector3& position, const Quaternion& rotation, float scale) :
	GameObject(position, rotation, scale)
{
}

void PhysicsObject::initialise()
{
	m_invInertia = Matrix4().initIdentity();// *(12.0f / (getMass()*(1 * 1 + 1 * 1)));

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			m_invInertia.setAt(i, j, m_invInertia.getAt(i, j) * (12.0f / (getMass()*(1 * 1 + 1 * 1))));
		}
	}

	//m_collider->m_owner = getTransform();
	//m_collider->m_body->m_owner = getTransform();
	//
	//Matrix3 tensor;// = Matrix3().initIdentity();
	//tensor.setBlockInteriaTensor(getTransform()->getScale(), m_collider->m_body->getMass());
	//m_collider->m_body->setIntertiaTensor(tensor);
	//
	//m_collider->m_body->calculateDerivedData();
	GameObject::initialise();
}

void PhysicsObject::update(float delta)
{
	if(getMass() < 0)
	{
		return;
	}

	Vector3 acc = m_force * m_invMass + Vector3(0, 0, 0);
	m_linearVelocity += acc * delta;
	m_linearVelocity *= LINEAR_VELOCITY_DAMP;

	getTransform()->setPosition(getTransform()->getPosition() + m_linearVelocity * delta);

	Vector3 angAcc = m_invInertia * m_torque;
	m_angualrVelocity += angAcc * delta;
	m_angualrVelocity *= ANGULAR_VELOCITY_DAMP;

	Quaternion rot = getTransform()->getRotation();
	getTransform()->setRotation(rot + rot * (m_angualrVelocity * (delta / 2.0f)));
	getTransform()->setRotation(getTransform()->getRotation().normalised());

	m_force = Vector3(0, 0, 0);
	m_torque = Vector3(0, 0, 0);

	GameObject::update(delta);
}

Vector3 PhysicsObject::getLinearVelocity() const
{
	return m_linearVelocity;
}

float PhysicsObject::getInverseMass() const
{
	return m_invMass;
}

float PhysicsObject::getMass() const
{
	return 1.0f / m_invMass;
}

Matrix4 PhysicsObject::getInverseInertiaTensor() const
{
	return m_invInertia;
}

Vector3 PhysicsObject::getAngularVelocity() const
{
	return m_angualrVelocity;
}

Collider* PhysicsObject::getCollider() const
{
	return m_collider;
}

Matrix4 PhysicsObject::buildTransform()
{
	return Matrix4().initIdentity();
}

void PhysicsObject::setLinearVelocity(const Vector3& v)
{
	m_linearVelocity = v;
}

void PhysicsObject::setMass(float mass)
{
	m_invMass = 1.0f / mass;
}

void PhysicsObject::setInverseMass(float f)
{
	m_invMass = f;
}

void PhysicsObject::setInverseInertia(const Matrix4& m)
{
	m_invInertia = m;
}

void PhysicsObject::setAngularVelocity(const Vector3& v)
{
	m_angualrVelocity = v;
}

void PhysicsObject::setCollider(Collider* c)
{
	m_collider = c;
}

Vector3 PhysicsObject::getForce()
{
	return m_force;
}

Vector3 PhysicsObject::getTorque()
{
	return m_torque;
}

void PhysicsObject::addForce(const Vector3& point, const Vector3& force)
{
	m_force += force;
	m_torque += (point - getTransform()->getPosition()).cross(force);
}