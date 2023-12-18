#include "Raycast2d.hpp"

using namespace alce;

Raycast2D::Raycast2D() : Component("Raycast2d")
{
    
}

#pragma region implementation

#pragma endregion

#pragma region inherited

void Raycast2D::Init()
{
    contactListener = std::make_shared<ContactListener>();
}

void Raycast2D::Update()
{
    if(world == nullptr) return;

    callback.owner = (GameObject*) owner;

    b2RayCastInput rayCastInput;
    rayCastInput.p1 = transform->position.Tob2Vec2();

    Vector2 p2 = transform->position + (direction * length);
    rayCastInput.p2 = p2.Tob2Vec2();
    rayCastInput.maxFraction = 1.0f;

    world->__world->RayCast(&callback, rayCastInput.p1, rayCastInput.p2);
    world->__world->SetContactListener(contactListener.get());
}

void Raycast2D::DebugRender()
{
    Vector2 start = transform->position;
    Vector2 end = start + (direction * (length * PPM));
    Vector2 size = Vector2(0.0f, length * PPM);

    sf::RectangleShape rs;
    rs.setPosition(start.ToPixels().ToVector2f());
    rs.setFillColor(sf::Color::Transparent);
    rs.setOutlineColor(sf::Color::Red);
    rs.setOutlineThickness(1.0f);
    rs.setSize(size.ToVector2f());

    Alce.GetWindow().draw(rs);
}

#pragma endregion