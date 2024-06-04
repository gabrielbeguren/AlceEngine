#include "Player.hpp"

using namespace alce;

SampleScene::Player::Player()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SampleScene::Player::Init()
{
    AddTag("Player");
    sortingLayer = 0;

    transform.position = Vector2(0, 50);

    camera = std::make_shared<Camera>();
    AddComponent(camera);

    rigidbody2d = std::make_shared<Rigidbody2D>();
    AddComponent(rigidbody2d);

    spriteRenderer = std::make_shared<SpriteRenderer>();
    AddComponent(spriteRenderer);   

    animation = std::make_shared<Animation2d>();
    AddComponent(animation);

    leftRaycast2d = std::make_shared<Raycast2D>();
    AddComponent(leftRaycast2d);

    rightRaycast2d = std::make_shared<Raycast2D>();
    AddComponent(rightRaycast2d);
}

void SampleScene::Player::Start()
{   
    transform.position = Vector2(0.0f, 0.0f);
    velocity = 1.5f;

    rigidbody2d->CreateBody(
        std::make_shared<RectShape>(Vector2(40.0f, 60.0f)),
        BodyType::dynamic_body,
        true,
        MaskType::mask_2
    );
    rigidbody2d->SetFixedRotation();

    spriteRenderer->AddTexture("player/idle.png", "idle");
    //spriteRenderer->SetTexture("idle");

    animation->AddAnimation("player/bear-sheet.png", "walk", 1, 4, 54, 63);
    animation->transform->scale = Vector2(0, 0);
    animation->PlayAnimation("walk");

    leftRaycast2d->direction = Vector2(-0.447f, -0.894f);
    leftRaycast2d->length = 1.2f;

    rightRaycast2d->direction = Vector2(0.447f, -0.894f);
    rightRaycast2d->length = 1.2f;
}

void SampleScene::Player::OnImpact(GameObject* other)
{
    grounded = true;
}

void SampleScene::Player::OnImpactEnd(GameObject* other)
{
    grounded = false;
}

void SampleScene::Player::Update()
{
    if(Input.IsKeyPressed(Keyboard::A))
    {
        rigidbody2d->SetHorizontalVelocity(-velocity);
    }
    else if(Input.IsKeyPressed(Keyboard::D))
    {
        rigidbody2d->SetHorizontalVelocity(velocity);
    }
    else
    {
        rigidbody2d->SetHorizontalVelocity(0.0f);
    }

    if (Input.IsKeyDown(Keyboard::Space) && grounded)
    {
        rigidbody2d->ApplyLinearForce(Vector2(0.0f, 60.0f));
    }
}

#pragma endregion