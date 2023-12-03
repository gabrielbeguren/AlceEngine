#include "ParticleSystem.hpp"

using namespace alce;

#pragma region Particle

void Particle::Create(Vector2 position, bool enableCollision)
{
    this->shape = std::make_shared<RectShape>(Vector2(25, 25));
    b2BodyDef bdef;

    bdef.position.Set(position.x, position.y);
    bdef.fixedRotation = false;
    bdef.type = b2BodyType::b2_dynamicBody;

    b2FixtureDef fixDef;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fixDef.restitutionThreshold = restitutionThreshold;

    if(enableCollision)
    {
        B2Mask mask = B2Mask(0x0002, 0x0001);
        fixDef.filter.categoryBits = mask.GetCategory();
        fixDef.filter.maskBits = mask.GetMask();
    }
    else
    {
        B2Mask mask = B2Mask(0x0004, 0);
        fixDef.filter.categoryBits = mask.GetCategory();
        fixDef.filter.maskBits = mask.GetMask();
    }

    b2PolygonShape boxShape;
    boxShape.SetAsBox(shape->width / 2 / PPM, shape->height / 2 / PPM);
    fixDef.shape = &boxShape;

    body = world->__world->CreateBody(&bdef);
    body->CreateFixture(&fixDef);
    fixture = body->GetFixtureList();
    body->SetTransform(position.ToMeters().Tob2Vec2(), body->GetAngle());

    body->attachedObject = this;
    contactListener = std::make_shared<ContactListener>();

    world->__world->SetContactListener(contactListener.get());
}

Particle::Particle()
{
    forbiddenComponents = {"Rigidbody2D"};
}

Particle::~Particle()
{
    if(body && world)
    {
        world->__world->DestroyBody(body);
    }
}

void Particle::SetDensity(float density)
{
    this->density = density;

    if(!body) return;

    fixture->SetDensity(density);
    body->ResetMassData();
}

void Particle::SetFriction(float friction)
{
    this->friction = friction;

    if(!body) return;

    fixture->SetFriction(friction);
    body->ResetMassData();
}

void Particle::SetRestitution(float restitution)
{
    this->restitution = restitution;

    if(!body) return;

    fixture->SetRestitution(restitution);
}

void Particle::SetRestitutionThreshold(float restitutionThreshold)
{
    this->restitutionThreshold = restitutionThreshold;

    if(!body) return;

	fixture->SetRestitutionThreshold(restitutionThreshold);
}

void Particle::ApplyForce(Vector2 force, bool wake)
{
    if(!body) return;

    body->ApplyForceToCenter(force.Tob2Vec2(), wake);
}

void Particle::ApplyLinearForce(Vector2 force, bool wake)
{
    if(!body) return;

    body->ApplyLinearImpulseToCenter(force.Tob2Vec2(), wake);
}

void Particle::SetLinearVelocity(Vector2 linearVelocity)
{
    if(!body) return;

    body->SetLinearVelocity(linearVelocity.Tob2Vec2());
}

void Particle::SetHorizontalVelocity(float vy)
{
    if(!body) return;

	float vx = body->GetLinearVelocity().x;
	body->SetLinearVelocity(b2Vec2(vx, vy));
}

void Particle::SetVerticalVelocity(float vx)
{
    if(!body) return;

	float vy = body->GetLinearVelocity().y;
	body->SetLinearVelocity(b2Vec2(vx, vy));
}

void Particle::SetAngularVelocity(float va)
{
    if(!body) return;

    body->SetAngularVelocity(va);
}

void Particle::SetAngularDamping(float ad)
{
    if(!body) return;

	body->SetAngularDamping(ad);
}

void Particle::SetLinearDamping(float ld)
{
    if(!body) return;

	body->SetLinearDamping(ld);
}

void Particle::ApplyAngularImpulse(float impulse)
{
    if(!body) return;

    body->ApplyAngularImpulse(impulse, true);
}

void Particle::ApplyTorque(float torque, bool wake)
{
    if(!body) return;

	body->ApplyTorque(torque, wake);
}

void Particle::SetAngle(float angle)
{
    if(!body) return;

	body->SetTransform(body->GetPosition(), angle);
}

void Particle::SetFixedRotation(bool flag)
{
    if(!body) return;

    body->SetFixedRotation(flag);
}

void Particle::SetLifetime(Time lifetime)
{
    this->lifetime = lifetime;
}

void Particle::Update()
{
    lifetime -= Chrono.deltaTime;

    if(!body) return;

    shapePos = Vector2(
        body->GetPosition().x * PPM,
        Kernel.GetScreenResolution().y - (body->GetPosition().y * PPM)
    );

    transform.position = body->GetPosition();
    transform.rotation = -1.0f * body->GetAngle() * DEG_PER_RAD;
}

#pragma endregion

#pragma region ParticleSystem

ParticleSystem::ParticleSystem() : Component("ParticleSystem")
{

}

#pragma region implementation


void ParticleSystem::SetDelay(Time delay)
{
    this->delay = delay;
}

void ParticleSystem::SetEmitArea(ShapePtr emitArea)
{
    this->emitArea = emitArea;

    if(emitArea->GetType() == ShapeType::polygon)
    {
        auto polygon = (PolygonShape*) emitArea.get();
        offset -= polygon->GetAverageEdgeLength() / 2.0f;
    }
}

void ParticleSystem::Emit()
{
    if(!behaviorLambda)
    {
        Debug.Warning("There is no particle behavior defined");
        return;
    }

    emit = true;
}

void ParticleSystem::Stop()
{
    if(!emit)
    {
        Debug.Warning("ParticleSystem is not emitting");
        return;
    }

    emit = false;
    elapsed.Reset();
}

#pragma endregion

#pragma region generic

void ParticleSystem::Update()
{
    if(emit && elapsed >= delay)
    {
        ParticlePtr particle = std::make_shared<Particle>();
        particle->world = ((Scene*)((GameObject*) owner)->scene)->GetWorld();
        Vector2 summonPosition;

        if(emitArea->GetType() == ShapeType::rect)
        {
            auto rect = (RectShape*) emitArea.get();
            summonPosition.x = Random.Range(transform->position.x - ((rect->width / 2) / PPM), transform->position.x + ((rect->width / 2) / PPM));
            summonPosition.y = Random.Range(transform->position.y - ((rect->height / 2) / PPM), transform->position.y + ((rect->height / 2) / PPM));
        }

        if(emitArea->GetType() == ShapeType::circle)
        {
            auto circle = (CircleShape*) emitArea.get();
            float angle = Random.Range(0.0f, 2 * Math.PI);
            float radius = Random.Range(0.0f, circle->radius / DEG_PER_RAD * 2.0f);
            summonPosition.x = transform->position.x + radius * Math.Cos(angle);
            summonPosition.y = transform->position.y + radius * Math.Sin(angle);
        }

        if(emitArea->GetType() == ShapeType::polygon)
        {
            auto polygon = (PolygonShape*) emitArea.get();
            List<Vector2> vertexList = polygon->GetVertexList();

            float minX = std::numeric_limits<float>::max();
            float maxX = std::numeric_limits<float>::lowest();
            float minY = std::numeric_limits<float>::max();
            float maxY = std::numeric_limits<float>::lowest();

            for(const Vector2& vertex: vertexList)
            {
                minX = std::min(minX, vertex.x);
                maxX = std::max(maxX, vertex.x);
                minY = std::min(minY, vertex.y);
                maxY = std::max(maxY, vertex.y);
            }

            int maxAttempts = 1000;
            for(int i = 0; i < maxAttempts; i++)
            {
                float randomX = Random.Range(minX, maxX);
                float randomY = Random.Range(minY, maxY);
                Vector2 randomPoint(randomX, randomY);
                
                if(polygon->InArea(randomPoint))
                {
                    summonPosition = randomPoint;
                    summonPosition += transform->position;
                    summonPosition += offset;
                    break;
                }
            }
        }

        particle->Create(summonPosition, enableCollision);
        particle->body->SetTransform(summonPosition.Tob2Vec2(), particle->body->GetAngle());
        particle->Config(behaviorLambda);
        particles.Add(particle);
        Kernel.GetCurrentScene()->AddGameObject(particle);
        elapsed.Reset();
    }

    particles.RemoveIf([](ParticlePtr particle) {
        if(particle->lifetime <= 0.0f) particle->Destroy();
        return particle->lifetime <= 0.0f;
    });

    elapsed += Chrono.deltaTime;
}

void ParticleSystem::Render()
{
    
}

void ParticleSystem::DebugRender()
{
    if(emitArea->GetType() == ShapeType::rect)
    {
        auto rect = (RectShape*) emitArea.get();
        sf::RectangleShape rectShape;
        rectShape.setSize(rect->GetBounds().ToVector2f());

        Vector2 rectShapePos = transform->position.ToPixels();
        rectShapePos.x -= (rect->width / 2);
        rectShapePos.y -= (rect->height / 2);

        rectShape.setPosition(rectShapePos.ToVector2f());
        rectShape.setFillColor(sf::Color::Transparent);
        rectShape.setOutlineColor(Color("#FFFF00").ToSFMLColor());
        rectShape.setOutlineThickness(1.0f);

        Kernel.GetWindow().draw(rectShape);
    }

    if(emitArea->GetType() == ShapeType::circle)
    {
        auto circle = (CircleShape*) emitArea.get();
        sf::CircleShape circleShape;
        circleShape.setFillColor(sf::Color::Transparent);
        circleShape.setOutlineColor(Color("#FFFF00").ToSFMLColor());
        circleShape.setOutlineThickness(1.0f);

        Vector2 circleShapePos = transform->position.ToPixels();
        circleShapePos.x -= circle->radius;
        circleShapePos.y -= circle->radius;
        circleShape.setPosition(circleShapePos.ToVector2f());
        circleShape.setRadius(circle->radius);

        Kernel.GetWindow().draw(circleShape);
    }

    if(emitArea->GetType() == ShapeType::polygon)
    {
        auto polygon = (PolygonShape*)emitArea.get();
        List<Vector2> vertexList = polygon->GetVertexList();

        sf::ConvexShape polygonShape;
        polygonShape.setPointCount(vertexList.Length());

        for (int i = 0; i < vertexList.Length(); ++i)
        {
            Vector2 vertex = vertexList[i];
            vertex += transform->position;
            vertex += offset;

            sf::Vector2f sfmlVertex = vertex.ToPixels().ToVector2f();
            polygonShape.setPoint(i, sfmlVertex);
        }

        polygonShape.setFillColor(sf::Color::Transparent); 
        polygonShape.setOutlineColor(Color("#FFFF00").ToSFMLColor());
        polygonShape.setOutlineThickness(1.0f);

        Kernel.GetWindow().draw(polygonShape);
    }
}

#pragma endregion

#pragma endregion