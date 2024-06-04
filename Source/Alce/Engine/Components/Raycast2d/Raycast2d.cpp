#include "Raycast2d.hpp"

using namespace alce;

Raycast2D::Raycast2D() : Component("Raycast2d") { }

void Raycast2D::Init()
{
    contactListener = std::make_shared<ContactListener>();
}

void Raycast2D::Update()
{
    if(world == nullptr) return;

    callback.owner = (GameObject*) owner;
    callback.hit = false;

    b2RayCastInput rayCastInput;
    rayCastInput.p1 = transform->position.Tob2Vec2();
    
    // Uso de la dirección asignada al Raycast2D
    Vector2 p2 = transform->position + (direction * length);
    rayCastInput.p2 = p2.Tob2Vec2();
    rayCastInput.maxFraction = 1.0f;

    world->__world->RayCast(&callback, rayCastInput.p1, rayCastInput.p2);
    world->__world->SetContactListener(contactListener.get());

    if (callback.hit) 
    {
        if (previousImpact != callback.currentImpact) 
        {
            if (previousImpact != nullptr) 
            {
                GameObject* _owner = (GameObject*) owner;
                _owner->OnImpactEnd(previousImpact);
                previousImpact->OnImpactEnd(_owner);
            }
            previousImpact = callback.currentImpact;
        }
    } 
    else 
    {
        if (previousImpact != nullptr) 
        {
            GameObject* _owner = (GameObject*) owner;
            _owner->OnImpactEnd(previousImpact);
            previousImpact->OnImpactEnd(_owner);
            previousImpact = nullptr;
        }
    }
}

void Raycast2D::DebugRender()
{
    Vector2 start = transform->position;
    Vector2 end = start + (direction * length);

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = start.ToPixels().ToVector2f();
    line[0].color = sf::Color::Red;
    line[1].position = end.ToPixels().ToVector2f();
    line[1].color = sf::Color::Red;

    Alce.GetWindow().draw(line);
}