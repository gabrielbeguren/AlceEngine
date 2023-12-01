#include "Floor.hpp"

using namespace alce;

test::Floor::Floor()
{
    sortingLayer = 0;
}

void test::Floor::Init()
{
    AddTag("Floor");

    transform.position = Vector2(0, 0);
    rb2d = std::make_shared<Rigidbody2D>();
    AddComponent(rb2d);

    RectShapePtr rs = std::make_shared<RectShape>(Vector2(1000.0f, 50.0f));

    rb2d->CreateBody(rs, BodyType::kinematic_body, true);
}

void test::Floor::Start()
{

}

void test::Floor::Update()
{
    
}