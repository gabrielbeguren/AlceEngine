#include "Wall.hpp"

using namespace alce;

test::Wall::Wall(const Vector2& position)
{
    transform.position = position;
}

void test::Wall::Init()
{
    AddTag(ConcatString({"Wall ", GenerateUUID()}));

    rb2d = std::make_shared<Rigidbody2D>();
    AddComponent(rb2d);

    RectShapePtr rs = std::make_shared<RectShape>(50.0f, 400.0f);

    rb2d->CreateBody(rs, BodyType::static_body, false);
}

void test::Wall::Start()
{
    
}
