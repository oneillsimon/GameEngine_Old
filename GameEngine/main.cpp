#include "Engine\GameEngine.h"
#include "Engine\Core\GameMath.h"
#include "Engine\Components\FreeLook.h"
#include "Engine\Components\FreeMove.h"

#undef main

class TestGame : public Game
{
public:
	TestGame() { }
	
	virtual void init(const Window& window);
protected:
private:
	TestGame(const TestGame& other) {}
	void operator =(const TestGame& other) {}
};

void TestGame::init(const Window& window)
{
	Material bricks("bricks", Texture("bricks.jpg"), 0.5f, 4, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
	Material bricks2("bricks2", Texture("bricks2.jpg"), 1, 8, Texture("bricks2_normal.jpg"), Texture("bricks2_disp.jpg"), 0.04f, -1.0f);

	IndexedModel square;
	{
		square.addVertex(1.0f, -1.0f, 0.0f);  square.addTexCoord(Vector2(1.0f, 1.0f));
		square.addVertex(1.0f, 1.0f, 0.0f);   square.addTexCoord(Vector2(1.0f, 0.0f));
		square.addVertex(-1.0f, -1.0f, 0.0f); square.addTexCoord(Vector2(0.0f, 1.0f));
		square.addVertex(-1.0f, 1.0f, 0.0f);  square.addTexCoord(Vector2(0.0f, 0.0f));
		square.addFace(0, 1, 2); square.addFace(2, 1, 3);
	}
	Mesh customMesh("square", square.finalize());

	/*GameObject* objTerrain = new GameObject(Vector3(0, -1, 5), Quaternion(), 32.0f);
	objTerrain->addComponent(new MeshRenderer(Mesh("terrain02.obj"), Material("bricks.jpg")));

	addToScene(objTerrain);*/

	addToScene((new GameObject(Vector3(0, -1, 5), Quaternion(), 32.0f))
		->addComponent(new MeshRenderer(Mesh("terrain02.obj"), Material("bricks"))));

	addToScene((new GameObject(Vector3(1, 1, 1), Quaternion(Vector3(1, 0, 0), GameMath::toRadians(-45)), 32.0f))
		->addComponent(new FreeLook(window.getCentre()))
		->addComponent(new FreeMove(10.0f, Input::KEY_W, Input::KEY_S, Input::KEY_A, Input::KEY_D))
		->addComponent(new CameraComponent(Matrix4().initPerspective(GameMath::toRadians(70.0f), window.getAspectRatio(), 0.1f, 1000.0f))));
	
	addToScene((new GameObject(Vector3(7,0,7)))
		->addComponent(new PointLight(Colour(0,255,0), 0.4f, Attenuation(0,0,1))));

	addToScene((new GameObject(Vector3(100, 100, 100), Quaternion(Vector3(1,0,0), GameMath::toRadians(-45))))
		->addComponent(new DirectionalLight(Colour(255,255,255), 0.4f, 10, 80.0f, 1.0f)));

	addToScene((new GameObject(Vector3(20,-11.0f,5), Quaternion(Vector3(1,0,0), GameMath::toRadians(-60.0f)) * Quaternion(Vector3(0,1,0), GameMath::toRadians(90.0f))))
		->addComponent(new SpotLight(Colour(0,255,255), 0.4f, Attenuation(0,0,0.02f), GameMath::toRadians(91.1f), 7, 1.0f, 0.5f)));
		
	addToScene((new GameObject(Vector3(0, 2, 0), Quaternion(Vector3(0,1,0), 0.4f), 1.0f))
		->addComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
		->addComponent(new FreeMove(10.0f, Input::KEY_UP, Input::KEY_DOWN, Input::KEY_LEFT, Input::KEY_RIGHT))
		->addChild((new GameObject(Vector3(0, 0, 25)))
			->addComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))));
	
	addToScene((new GameObject(Vector3(24,-12,5), Quaternion(Vector3(0,1,0), GameMath::toRadians(30.0f))))
		->addComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
		
	addToScene((new GameObject(Vector3(0,0,7), Quaternion(), 1.0f))
		->addComponent(new MeshRenderer(Mesh("square"), Material("bricks2"))));
}

#include <iostream>
#include "Engine\Physics\BoundingSphere.h"
#include "Engine\Physics\AABB.h"
#include "Engine\Physics\Plane.h"

int main()
{
	BoundingSphere sphere1(Vector3(0, 0, 0), 1.0f);
	BoundingSphere sphere2(Vector3(0, 3, 0), 1.0f);
	BoundingSphere sphere3(Vector3(0, 0, 2), 1.0f);
	BoundingSphere sphere4(Vector3(1, 0, 0), 1.0f);

	IntersectionData sphere1IntSphere2 = sphere1.intersectBoundingSphere(sphere2);
	IntersectionData sphere1IntSphere3 = sphere1.intersectBoundingSphere(sphere3);
	IntersectionData sphere1IntSphere4 = sphere1.intersectBoundingSphere(sphere4);

	std::cout << "Sphere1 intersect Sphere2: " << sphere1IntSphere2.getDoesIntersect() << ", Distance: " << sphere1IntSphere2.getDistance() <<std::endl;
	std::cout << "Sphere1 intersect Sphere3: " << sphere1IntSphere3.getDoesIntersect() << ", Distance: " << sphere1IntSphere3.getDistance() <<std::endl;
	std::cout << "Sphere1 intersect Sphere4: " << sphere1IntSphere4.getDoesIntersect() << ", Distance: " << sphere1IntSphere4.getDistance() <<std::endl;

	AABB aabb1(Vector3(0, 0, 0), Vector3(1, 1, 1));
	AABB aabb2(Vector3(1, 1, 1), Vector3(2, 2, 2));
	AABB aabb3(Vector3(1, 0, 0), Vector3(2, 1, 1));
	AABB aabb4(Vector3(0, 0, -2), Vector3(1, 1, -1));
	AABB aabb5(Vector3(0, 0.5f, 0), Vector3(1, 1.5f, 1));

	IntersectionData aabb1Intaabb2 = aabb1.intersectAABB(aabb2);
	IntersectionData aabb1Intaabb3 = aabb1.intersectAABB(aabb3);
	IntersectionData aabb1Intaabb4 = aabb1.intersectAABB(aabb4);
	IntersectionData aabb1Intaabb5 = aabb1.intersectAABB(aabb5);

	std::cout << "AABB1 intersect AABB2: " << aabb1Intaabb2.getDoesIntersect() << ", Distance: " << aabb1Intaabb2.getDistance() << std::endl;
	std::cout << "AABB1 intersect AABB3: " << aabb1Intaabb3.getDoesIntersect() << ", Distance: " << aabb1Intaabb3.getDistance() << std::endl;
	std::cout << "AABB1 intersect AABB4: " << aabb1Intaabb4.getDoesIntersect() << ", Distance: " << aabb1Intaabb4.getDistance() << std::endl;
	std::cout << "AABB1 intersect AABB5: " << aabb1Intaabb5.getDoesIntersect() << ", Distance: " << aabb1Intaabb5.getDistance() << std::endl;

	Plane plane1(Vector3(0, 1, 0), 0);

	IntersectionData plane1IntSphere1 = plane1.intersectSphere(sphere1);
	IntersectionData plane1IntSphere2 = plane1.intersectSphere(sphere2);
	IntersectionData plane1IntSphere3 = plane1.intersectSphere(sphere3);
	IntersectionData plane1IntSphere4 = plane1.intersectSphere(sphere4);

	std::cout << "Plane 1 intersect Sphere1: " << plane1IntSphere1.getDoesIntersect() << ", Distance: " << plane1IntSphere1.getDistance() << std::endl;
	std::cout << "Plane 1 intersect Sphere2: " << plane1IntSphere2.getDoesIntersect() << ", Distance: " << plane1IntSphere2.getDistance() << std::endl;
	std::cout << "Plane 1 intersect Sphere3: " << plane1IntSphere3.getDoesIntersect() << ", Distance: " << plane1IntSphere3.getDistance() << std::endl;
	std::cout << "Plane 1 intersect Sphere4: " << plane1IntSphere4.getDoesIntersect() << ", Distance: " << plane1IntSphere4.getDistance() << std::endl;

	getchar();

	/*TestGame game;
	CoreEngine engine(800, 600, 60, &game);
	engine.createWindow("Game ENGINE");
	engine.start();

	return 0;*/
}