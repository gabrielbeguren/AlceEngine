#include "Ground.hpp"

using namespace alce;

SampleScene::Ground::Ground()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SampleScene::Ground::Init()
{
    AddTag("Ground");
    sortingLayer = 0;
    rigidbody2d = std::make_shared<Rigidbody2D>();
    AddComponent(rigidbody2d);
}

void SampleScene::Ground::Start()
{
    rigidbody2d->CreateBody(
        std::make_shared<RectShape>(Vector2(1000.0f, 50.0f)),
        BodyType::kinematic_body,
        true
    );
}

void SampleScene::Ground::Update()
{
	
}

#pragma endregion