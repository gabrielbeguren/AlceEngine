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
    sortingLayer = 1;

    transform.position = Vector2(0, 50);

    camera = std::make_shared<Camera>();
    AddComponent(camera);

    rigidbody2d = std::make_shared<Rigidbody2D>();
    AddComponent(rigidbody2d);

    animation = std::make_shared<Animation2d>();
    AddComponent(animation);

    leftRaycast2d = std::make_shared<Raycast2D>();
    AddComponent(leftRaycast2d);

    rightRaycast2d = std::make_shared<Raycast2D>();
    AddComponent(rightRaycast2d);

    canvas = std::make_shared<Canvas>();
    AddComponent(canvas);
}

void SampleScene::Player::Start()
{   
    walking = false;
    status = "idle-forward";

    transform.position = Vector2(0.0f, 0.0f);
    velocity = 1.0f;

    rigidbody2d->CreateBody(
        std::make_shared<RectShape>(Vector2(40.0f, 65.0f)),
        BodyType::dynamic_body,
        true,
        MaskType::mask_2
    );
    rigidbody2d->SetFixedRotation();

    animation->AddAnimation("player/walk-forward.png", "walk-forward", 1, 4, 54, 63);
    animation->AddAnimation("player/walk-backward.png", "walk-backward", 1, 4, 54, 63);
    animation->AddAnimation("player/idle-forward.png", "idle-forward", 1, 1, 54, 63);
    animation->AddAnimation("player/idle-backward.png", "idle-backward", 1, 1, 54, 63);
    animation->AddAnimation("player/jump-forward.png", "jump-forward", 1, 1, 54, 63);
    animation->AddAnimation("player/jump-backward.png", "jump-backward", 1, 1, 54, 63);


    animation->transform->scale = Vector2(0, 0);
    leftRaycast2d->direction = Vector2(-0.447f, -0.894f);
    leftRaycast2d->length = 1.5f;

    rightRaycast2d->direction = Vector2(0.447f, -0.894f);
    rightRaycast2d->length = 1.5f;


    TextPtr text = std::make_shared<Text>();
    canvas->AddElement(text);
    text->position = Vector2(20, 20);
    text->padding = Vector2(10, 10);

    text->font = "fonts/Merriweather/Merriweather-Black.ttf";
    *text += "<color='green'>Alce Engine</color> Sample Project";
    *text += "\nby @gabrielbeguren";
    text->borderRadius = 4;
    text->backgroundColor = Colors::Black;

    TextInputPtr ti = std::make_shared<TextInput>();
    canvas->AddElement(ti);
    ti->width = 500;
    ti->height = 35;
    ti->backgroundColor = Color("#3d3d3d");
    ti->textColor = Colors::White;
    ti->borderWidth = 1;
    ti->cursorColor = Colors::White;
    ti->positionType = UIElement::Relative;
    ti->position = Vector2(0.01, 0.925f);
    ti->fontSize = TextInput::Small;
    ti->onSubmit = [=](){
        Debug.Log(ti->GetText());
    };

    ButtonPtr button = std::make_shared<Button>(); 
    canvas->AddElement(button);
    button->position = Vector2(20, 100);
    button->borderRadius = 2;
    button->borderWidth = 1;
    button->borderColor = Colors::White;
    button->onClick = [](){
        Debug.Log("Click!");
    };

    ImagePtr image = std::make_shared<Image>();
    canvas->AddElement(image);
    image->position = Vector2(300, 25);
    image->AddTexture("meteor.png", "meteor");
    image->SetTexture("meteor");
}

void SampleScene::Player::OnImpact(GameObject* other)
{
    if(other->HasTag("Ground"))
    {
        grounded = true;
        if(status == "jump-forward") status = "idle-forward";
        if(status == "jump-backward") status = "idle-backward";
    }
}

void SampleScene::Player::OnImpactEnd(GameObject* other)
{
    if(other->HasTag("Ground"))
    {
        grounded = false;
        if(status == "idle-forward") status = "jump-forward";
        if(status == "idle-backward") status = "jump-backward";
    }
}

void SampleScene::Player::Update()
{
    if(Input.IsKeyPressed(Keyboard::A))
    {
        rigidbody2d->SetHorizontalVelocity(-velocity);
        if(grounded) status = "walk-backward";
        else status = "jump-backward";
    }
    else if(Input.IsKeyPressed(Keyboard::D))
    {
        rigidbody2d->SetHorizontalVelocity(velocity);
        if(grounded) status = "walk-forward";
        else status = "jump-forward";
    }
    else
    {
        rigidbody2d->SetHorizontalVelocity(0.0f);
        
        if(grounded)
        {
            if(status == "walk-forward") status = "idle-forward";
            if(status == "walk-backward") status = "idle-backward";
        }
    }

    if (Input.IsKeyDown(Keyboard::Space) && grounded)
    {
        rigidbody2d->ApplyLinearForce(Vector2(0.0f, 60.0f));

        if(status == "walk-forward") status = "jump-forward";
        if(status == "idle-forward") status = "jump-forward";
        if(status == "walk-backward") status = "jump-backward";
        if(status == "idle-backward") status = "jump-backward";
        grounded = false; 
    }

    AnimationManager();
}
#pragma endregion

void SampleScene::Player::AnimationManager()
{
    if(status == "idle-forward")
    {
        if(animation->GetCurrentAnimation() != "idle-forward")
            animation->PlayAnimation("idle-forward");
    }

    if(status == "idle-backward")
    {
        if(animation->GetCurrentAnimation() != "idle-backward")
            animation->PlayAnimation("idle-backward");
    }

    if(status == "walk-forward")
    {
        if(animation->GetCurrentAnimation() != "walk-forward")
            animation->PlayAnimation("walk-forward");
    }

    if(status == "walk-backward")
    {
        if(animation->GetCurrentAnimation() != "walk-backward")
            animation->PlayAnimation("walk-backward");
    }

    if(status == "jump-forward")
    {
        if(animation->GetCurrentAnimation() != "jump-forward")
            animation->PlayAnimation("jump-forward");
    }

    if(status == "jump-backward")
    {
        if(animation->GetCurrentAnimation() != "jump-backward")
            animation->PlayAnimation("jump-backward");
    }
}