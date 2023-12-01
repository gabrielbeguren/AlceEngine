#include "TestScene.hpp"

#include "Floor/Floor.hpp"
#include "TestBody/TestBody.hpp"
#include "Wall/Wall.hpp"
#include "Cookie/Cookie.hpp"

using namespace alce;

test::TestScene::TestScene() : Scene("test")
{
    DebugMode();
    InitPhysics(Vector2(0.0f, -0.1f));
}

void test::TestScene::Init()
{
    test::FloorPtr floor = std::make_shared<test::Floor>();
    AddGameObject(floor);

    test::WallPtr wall1 = std::make_shared<test::Wall>(Vector2(-300, 30));
    AddGameObject(wall1);    
    
    test::WallPtr wall2 = std::make_shared<test::Wall>(Vector2(300, 30));
    AddGameObject(wall2);

    test::TestBodyPtr testBody = std::make_shared<test::TestBody>();
    AddGameObject(testBody);

    test::CookiePtr cookie1 = std::make_shared<test::Cookie>("cookie1", true);
    test::CookiePtr cookie2 = std::make_shared<test::Cookie>("cookie2");
    test::CookiePtr cookie3 = std::make_shared<test::Cookie>("cookie3");
    test::CookiePtr cookie4 = std::make_shared<test::Cookie>("cookie4");
    test::CookiePtr cookie5 = std::make_shared<test::Cookie>("cookie5");

    cookie1->SetParent(cookie2);
    AddGameObject(cookie1);

    cookie2->SetParent(cookie3);
    AddGameObject(cookie2);

    cookie3->SetParent(cookie4);
    AddGameObject(cookie3);

    cookie4->SetParent(cookie5);
    AddGameObject(cookie4);

    AddGameObject(cookie5);
}

void test::TestScene::Start()
{
    
}