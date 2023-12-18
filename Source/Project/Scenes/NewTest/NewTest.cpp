#include "NewTest.hpp"
#include "test/test.hpp"

using namespace alce;

NewTestScene::NewTest::NewTest() : Scene("NewTest")
{
	DebugMode(true);
	InitPhysics(Vector2(0.0f, -9.8f));
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region generic

void NewTestScene::NewTest::Init()
{
	AddGameObject(std::make_shared<NewTestScene::test>());
}

void NewTestScene::NewTest::Start()
{
	
}

#pragma endregion