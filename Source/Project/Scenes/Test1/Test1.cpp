#include "Test1.hpp"
#include "Floor/Floor.hpp"
#include "Body/Body.hpp"

using namespace alce;

Test1Scene::Test1::Test1() : Scene("Test1")
{
	DevelopmentMode(true);
	InitPhysics(Vector2(0.0f, -2));
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void Test1Scene::Test1::Init()
{
	// Test1Scene::BodyPtr body = std::make_shared<Test1Scene::Body>();
	// AddGameObject(body);	

	// Test1Scene::FloorPtr floor = std::make_shared<Test1Scene::Floor>();
	// AddGameObject(floor);
}

void Test1Scene::Test1::Start()
{
	
}

#pragma endregion