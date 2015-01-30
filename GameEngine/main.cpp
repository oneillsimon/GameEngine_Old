#include "Inneall.h"

#include <iostream>

#include "Engine\Components\Physics\PhysicsEngineComponent.h"
#include "Engine\Components\Physics\PhysicsObjectComponent.h"

#include "Engine\Rendering\SpriteSheet.h"
#include "Engine\Components\Rendering\SpriteRenderer.h"
#include "Engine\Components\Rendering\SpriteAnimator.h"

#include "Engine\Components\Game\Movement2D.h"

#include "Engine\Physics\Particle.h"
#include "Engine\Rendering\Shape.h"

#include "Engine\Core\Scripter.h"

#include "Engine\Components\Physics\ColliderRenderer.h"
#include "Engine\Components\Physics\RigidBodyComponent.h"

#undef main

class TestGame : public Game
{
public:
	TestGame(){};
	
	virtual void initialise(const Window& window);
protected:
private:
	//TestGame(const TestGame& other) {}
	//void operator =(const TestGame& other) {}
};

static void tests();

void TestGame::initialise(const Window& window)
{
	GameObject* cameraObj = new GameObject(Vector3(0, 0, -7.5f));

	cameraObj->addComponent(new FreeLook(window.getCentre()));
	cameraObj->addComponent(new FreeMove());
	cameraObj->addComponent(new CameraComponent(Matrix4().initPerspective(toRadians(70.0f), window.getAspectRatio(), 0.1f, 1000.0f)));

	PhysicsObject* pObj2 = new PhysicsObject(Vector3(-1.5f, 5, 0));
	pObj2->setCollider(new ColliderBox());
	pObj2->addComponent(new ColliderRenderer(true, pObj2->getCollider(), COLOUR_FIREBRICK));
	pObj2->addComponent(new FreeMove(10, Input::KEY_UP, Input::KEY_DOWN, Input::KEY_LEFT, Input::KEY_RIGHT));
	pObj2->addComponent(new Movement2D(10, Input::KEY_O, Input::KEY_P, -1, -1));
	pObj2->addComponent(new RigidBodyComponent(pObj2));
	pObj2->setMass(1);
	//addToScene2(pObj2);

	for(int i = 0; i < 4; i++)
	{
		Vector3 v;

		if(i == 0)
			v = Vector3(-1.5f, 5, 0);
		else if(i == 1)
			v = Vector3(0, 5, 1.5f);
		else if(i == 2)
			v = Vector3(1.5f, 5, 0);
		else
			v = Vector3(0, 5, -1.5f);

		//PhysicsObject* pObj3 = new PhysicsObject(Vector3(0, 5, 0));
		PhysicsObject* pObj3 = new PhysicsObject(v);
		pObj3->setCollider(new ColliderSphere());
		pObj3->addComponent(new ColliderRenderer(true, pObj3->getCollider(), COLOUR_FIREBRICK));
		pObj3->addComponent(new FreeMove(10, Input::KEY_UP, Input::KEY_DOWN, Input::KEY_LEFT, Input::KEY_RIGHT));
		pObj3->addComponent(new Movement2D(10, Input::KEY_O, Input::KEY_P, -1, -1));
		pObj3->addComponent(new RigidBodyComponent(pObj3));
		pObj3->setMass(10);
		addToScene2(pObj3);
	}

	PhysicsObject* plane = new PhysicsObject(Vector3(0.0f, -1, 0));
	plane->setCollider(new ColliderSphere());
	plane->setMass(1000);
	//plane->m_collider->m_body->setAwake(false);
	//plane->getTransform()->rotate(AXIS_Y, toRadians(45));
	//plane->addComponent(new MeshRenderer(Mesh("sphere.obj"), Material("", TEXTURE_BLANK, COLOUR_ORANGE)));
	plane->addComponent(new ColliderRenderer(true, plane->getCollider(), COLOUR_FIREBRICK));
	addToScene2(plane);

	int n = 10;
	int m = 12;

	for(int i = 0; i < n; i++)
	{
		float x = random(-m, m);
		float y = random(-m, m);
		float z = random(-m, m);

		PhysicsObject* o = new PhysicsObject(Vector3(x, y, z));
		o->addComponent(new MeshRenderer(Mesh("sphere.obj"), Material("", TEXTURE_BLANK, getRandomColour())));
		//addToScene2(o);
	}

	DirectionalLight* d = new DirectionalLight(COLOUR_WHITE, 0.04f);
	GameObject* gg = new GameObject();
	gg->addComponent(d);
	addToScene(gg);

	addToScene(cameraObj);

	int pCount = Octree::partitions.size();
	
	for(int i = 0; i < pCount; i++)
	{
		GameObject* g = new GameObject(Octree::partitions[i].centre, Quaternion(), Octree::partitions[i].max.getX());
		g->addComponent(new ColliderRenderer(false, new ColliderBox(Octree::partitions[i].min)));
		//addToScene(g);
	}

	//getRoot().addComponent(new OctreeRenderer(0));

	Game::initialise(window);
}

int main()
{
	TestGame test;
	CoreEngine engine(800, 600, 120, &test);
	engine.createWindow("Game ENGINE");
	engine.start();

	return 0;
}