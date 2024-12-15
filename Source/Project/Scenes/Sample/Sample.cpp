#include "Sample.hpp"
#include "Tree/Tree.hpp"
#include "Ground/Ground.hpp"
#include "Player/Player.hpp"

using namespace alce;

SampleScene::Sample::Sample() : Scene("Sample")
{
	persist = true;
	DevelopmentMode(true);
	InitPhysics(Vector2(0.0f, 0.0f));
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SampleScene::Sample::Init()
{
	SampleScene::PlayerPtr player = std::make_shared<SampleScene::Player>();
	AddGameObject(player, "player");

	SampleScene::GroundPtr ground = std::make_shared<SampleScene::Ground>();
	AddGameObject(ground, "ground");

	SampleScene::TreePtr tree1 = std::make_shared<SampleScene::Tree>(Vector2(5, 3.5));
	AddGameObject(tree1, "tree1");	
	
	SampleScene::TreePtr tree2 = std::make_shared<SampleScene::Tree>(Vector2(3, 3.5));
	AddGameObject(tree2, "tree2");
}

void SampleScene::Sample::Start()
{
	
}

#pragma endregion