#include "Cookie.hpp"

using namespace alce;

test::Cookie::Cookie(String tag, bool flag)
{
    sortingLayer = 1;
    this->flag = flag;
    this->tag = tag;
}

void test::Cookie::Init()
{
    AddTag(tag);

    transform.position = Vector2(0, 10);

    sr = std::make_shared<SpriteRenderer>();
    sr->AddTexture("meteor.png", "meteor");
    sr->SetTexture("meteor");
    sr->enabled = true;

    //AddComponent(sr);

    ps = std::make_shared<ParticleSystem>();
    ps->SetDelay(Time({
        {"miliseconds", 250}
    }));

    ps->enableCollision = false;

    ps->Behavior([](Particle& particle) {
        
        SpriteRendererPtr psr = std::make_shared<SpriteRenderer>();
        psr->AddTexture("meteor.png", "meteor");
        psr->SetTexture("meteor");
        particle.AddComponent(psr);
        particle.SetLifetime(Time({
            {"seconds", 1.5f}
        }));

        particle.SetDensity(1.0f);
        particle.ApplyForce(Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)) * 0.6f);
    });

    ps->SetEmitArea(std::make_shared<RectShape>(transform.position, 25, 25));
    AddComponent(ps);
}

void test::Cookie::Start()
{
    ps->Emit();
}

void test::Cookie::Update()
{

}