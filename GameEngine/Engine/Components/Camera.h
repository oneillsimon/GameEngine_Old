#pragma once

#include "../Core/3DMath.h"
#include "GameComponent.h"

class Camera : public GameComponent
{
private:
	Matrix4 m_projection;

public:
	Camera(Matrix4& projection);

	virtual void addToCoreEngine(CoreEngine* coreEgine);

	Matrix4 getViewProjection();
};