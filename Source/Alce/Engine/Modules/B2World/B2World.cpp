#include "B2World.hpp"
#include "../Debug/Debug.hpp"
#include "../Chrono/Chrono.hpp"

using namespace alce;

B2World::B2World()
{
    __world = new b2World(Vector2(0.0f, -9.8f).Tob2Vec2());
}

B2World::B2World(Vector2 gravity)
{
    __world = new b2World(gravity.Tob2Vec2());
}

void B2World::SetGravity(Vector2 gravity)
{
    __world->SetGravity(gravity.Tob2Vec2());
}

void B2World::SetVelocityIterations(int velocityIterations)
{
    this->velocityIterations = velocityIterations;
}

void B2World::SetPositionIterations(int positionIterations)
{
    this->positionIterations = positionIterations;
}

void B2World::Step()
{
    __world->Step(timeStep * Chrono.deltaTime.ToMiliseconds(), velocityIterations, positionIterations);
}