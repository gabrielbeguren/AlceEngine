#include "test.hpp"

using namespace alce;

NewTestScene::test::test()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region generic

void NewTestScene::test::Init()
{
    camera = std::make_shared<Camera>();
    AddComponent(camera);    

	ps = std::make_shared<ParticleSystem>();
    ps->enableCollision = false;
    ps->Behavior([](Particle& particle) {

        SpriteRendererPtr p_sr = std::make_shared<SpriteRenderer>();
        particle.AddComponent(p_sr);

        p_sr->enabled = true;
        p_sr->AddTexture("meteor.png", "p_meteor");
        p_sr->SetTexture("p_meteor");

        particle.SetLifetime(Time({
            {"seconds", 1.0f}
        }));
        particle.ApplyForce(Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)) * 0.3f);
        particle.sortingLayer = 1;
        particle.SetDensity(0.5f);
        particle.SetFixedRotation();
    });

    List<Vector2> vertexarr = {
        Vector2(0.0f, 0.0f), 
        Vector2(2.0f, 0.0f),
        Vector2(1.0f, 2.0f) 
    };

    ps->SetEmitArea(std::make_shared<PolygonShape>(vertexarr));
    ps->SetDelay(Time({
        {"seconds", 0.5f}
    }));

    AddComponent(ps);
}

void NewTestScene::test::Start()
{
	
}

void NewTestScene::test::Update()
{
	if(Input.IsKeyDown(Keyboard::F))
    {
        ps->Emit();
    }

    if(Input.IsKeyDown(Keyboard::G))
    {
        ps->Stop();
    }
}

#pragma endregion