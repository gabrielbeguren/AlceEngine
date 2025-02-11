#include "Body.hpp"

using namespace alce;

Test1Scene::Body::Body()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void Test1Scene::Body::Init()
{
	AddTag("testbody");
    sortingLayer = 0;
    transform.position = Vector2(0, 50);

    rb2d = std::make_shared<Rigidbody2D>();
    AddComponent(rb2d);

    rb2d->CreateBody(std::make_shared<RectShape>(100.0f, 100.0f), dynamic_body, false, MaskType::mask_2);
    rb2d->SetFixedRotation();

    sr = std::make_shared<SpriteRenderer>();
    AddComponent(sr);

    sr->enabled = true;
    sr->AddTexture("meteor.png", "meteor");
    sr->SetTexture("meteor");

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

    Debug.Log("Ejecutando Init de Body de Test1");
}

void Test1Scene::Body::Start()
{
	
}

void Test1Scene::Body::Update()
{
	 if(Input.IsKeyDown(Keyboard::F))
    {
        ps->Emit();
    }
        
    if(Input.IsKeyDown(Keyboard::G))
    {
        // Alce.SetCurrentScene("Sample");
        Alce.GetCurrentScene()->Shell("change to Sample;");
    }


    if(Input.IsKeyPressed(Keyboard::D))
    {
        rb2d->SetHorizontalVelocity(1);
    }
    else if(Input.IsKeyPressed(Keyboard::A))
    {
        rb2d->SetHorizontalVelocity(-1);
    }
    else
    {
        rb2d->SetVerticalVelocity(0.0f);
    }

    if(Input.IsKeyPressed(Keyboard::W))
    {
        rb2d->SetVerticalVelocity(1);
    }
    else if(Input.IsKeyPressed(Keyboard::S))
    {
        rb2d->SetVerticalVelocity(-1);
    }
    else
    {
        rb2d->SetVerticalVelocity(0.0f);
    }

    if(Input.IsJoystickConnected(0))
    {
        if(Input.GetJoystick(0)->IsButtonDown(Joystick::Button::B))
        {
            Debug.Log("presionado B");
        }

        if(Input.GetJoystick(0)->IsButtonDown(Joystick::Button::LEFT_STICK))
        {
            Debug.Log("presionado LEFT_STICK");
        }
    }
}

#pragma endregion