#include "GameComponent.h"
#include "../Physics/PhysicsObject.h"

class TestComponent : public GameComponent
{
public:
	int number;
	PhysicsObject obj;

	TestComponent(const PhysicsObject& obj) :
		obj(obj)
	{

	}

	virtual void input(const Input& input, float delta)
	{
		if(input.getKey(Input::KEY_Y))
		{
			obj.setVelocity(Vector3(0, 0, 2));
		}
	}
};