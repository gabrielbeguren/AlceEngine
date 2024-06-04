#include "Sample.hpp"
#include "Ground/Ground.hpp"
#include "Player/Player.hpp"

using namespace alce;

SampleScene::Sample::Sample() : Scene("Sample")
{
	DebugMode(true);
	InitPhysics(Vector2(0.0f, -1.0f));
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SampleScene::Sample::Init()
{
	SampleScene::PlayerPtr player = std::make_shared<SampleScene::Player>();
	AddGameObject(player);

	SampleScene::GroundPtr ground = std::make_shared<SampleScene::Ground>();
	AddGameObject(ground);
 
}

void SampleScene::Sample::Start()
{
	
}

#pragma endregion