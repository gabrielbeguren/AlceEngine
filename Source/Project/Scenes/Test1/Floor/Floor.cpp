#include "Floor.hpp"

using namespace alce;

Test1Scene::Floor::Floor()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void Test1Scene::Floor::Init()
{
	AddTag("Floor");

    transform.position = Vector2(0, 0);
    rb2d = std::make_shared<Rigidbody2D>();
    AddComponent(rb2d);

    RectShapePtr rs = std::make_shared<RectShape>(Vector2(1000.0f, 50.0f));

    rb2d->CreateBody(rs, BodyType::kinematic_body, true);
}

void Test1Scene::Floor::Start()
{
	
}

void Test1Scene::Floor::Update()
{
	
}

#pragma endregion