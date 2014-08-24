#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

void PhysicsEngine::addObject(const PhysicsObject& object)
{
	m_objects.push_back(object);
}

void PhysicsEngine::simulate(float delta)
{
	for(unsigned int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i].integrate(delta);
	}
}

void PhysicsEngine::handleCollisions()
{
	for(unsigned int i = 0; i < m_objects.size(); i++)
	{
		for(unsigned int j = i + 1; j < m_objects.size(); j++)
		{
			IntersectionData intersectData = m_objects[i].getCollider().intersect(m_objects[j].getCollider());

			if(intersectData.getDoesIntersect())
			{
				Vector3 direction = intersectData.getDirection().normalised();
				Vector3 otherDirection = Vector3(direction.reflect(m_objects[i].getVelocity().normalised()));

				m_objects[i].setVelocity(Vector3(m_objects[i].getVelocity().reflect(otherDirection)));
				m_objects[j].setVelocity(Vector3(m_objects[j].getVelocity().reflect(direction)));
			}
		}
	}
}