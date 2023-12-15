#include "Animation2d.hpp"

using namespace alce;

Animation2d::Animation2d() : Component("Animation2d")
{
    cardinals.Set("top-left", std::make_shared<Vector2>());
    cardinals.Set("top-right", std::make_shared<Vector2>());
    cardinals.Set("bottom-left", std::make_shared<Vector2>());
    cardinals.Set("bottom-right", std::make_shared<Vector2>());
}

#pragma region implementation

void Animation2d::AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight)
{
    spritesheets.Set(name, new sf::Sprite());
    spritesheets[name]->setTexture(*Alce.GetTexture(spritesheetFile));

    List<RectShape*> frames;

    int x = 0, y = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            frames.Add(new RectShape(Vector2(x, y), frameWidth, frameHeight));
            x += frameWidth;
        }

        y += frameHeight;
        x = 0;
    }

    animations.Set(name, frames);
}

void Animation2d::DeleteAnimation(String name)
{
    animations.RemoveByKey(name);
}

void Animation2d::SetOriginMode(OriginMode originMode)
{
    this->originMode = originMode;
}

void Animation2d::PlayAnimation(String name, AnimationMode mode)
{
    if(!enabled) return;

    if(!animations.HasKey(name))
    {
        Debug.Warning("There is not animation named \"{}\" in the stack", {name});
        return;
    }

    currentAnimation = name;
    currentMode = mode;
    isPlaying = true;

    msSinceLastFrame = 0;

    DetermineNumFrames();
    DetermineFirstFrameNum();
    SetTextureRectForFrame();
}

void Animation2d::SetAnimationMode(AnimationMode mode)
{
    currentMode = mode;
}

#pragma region AnimationEngine

void Animation2d::DetermineNumFrames()
{
    numFrames = animations[currentAnimation].Length();
}

void Animation2d::DetermineFirstFrameNum()
{
    switch(currentMode)
    {
    case AnimationMode::LoopForwards:
    case AnimationMode::OnceForwards:
    case AnimationMode::FirstFrameOnly:
        currentFrameNum = 0;
        break;
    case AnimationMode::LoopBackwards:
    case AnimationMode::OnceBackwards:
        currentFrameNum = numFrames - 1;
        break;
    }
}

void Animation2d::DetermineNextFrameNum()
{
    if(!isPlaying) return;
    if(currentMode == AnimationMode::FirstFrameOnly) return;

    int elapsedFrames = msSinceLastFrame / msPerFrame;

    switch(currentMode)
    {
    case AnimationMode::LoopForwards:
    case AnimationMode::OnceForwards:
        currentFrameNum += elapsedFrames;
        break;
    case AnimationMode::LoopBackwards:
    case AnimationMode::OnceBackwards:
        currentFrameNum -= elapsedFrames;
        break;
    }

    if((currentFrameNum >= numFrames) || (currentFrameNum < 0))
    {
        switch(currentMode)
        {
        case AnimationMode::LoopForwards:
        case AnimationMode::LoopBackwards:
            currentFrameNum = currentFrameNum % numFrames;
            if(currentFrameNum < 0) currentFrameNum = numFrames + currentFrameNum;
            break;
        case AnimationMode::OnceForwards:
            currentFrameNum = numFrames - 1;
            isPlaying = false;
            break;
        case AnimationMode::OnceBackwards:
            currentFrameNum = 0;
            isPlaying = false;
            break;
        }
    }
}

void Animation2d::SetTextureRectForFrame()
{
    auto rect = animations[currentAnimation].Get(currentFrameNum);
    spritesheets[currentAnimation]->setTextureRect(rect->ToIntRect());

    float originX = 0.0f;
    float originY = 0.0f;

    switch(originMode)
    {
    case OriginMode::TopMiddle:
    case OriginMode::Center:
    case OriginMode::BottomMiddle:
        originX = (float) rect->width / 2.0f;
        break;
    case OriginMode::TopRight:
    case OriginMode::MiddleRight:
    case OriginMode::BottomRight:
        originX = (float) rect->width;
        break;
    }

    switch (originMode)
	{
	case OriginMode::MiddleLeft:
	case OriginMode::Center:
	case OriginMode::MiddleRight:
		originY = (float) rect->width / 2.0f;
		break;
	case OriginMode::BottomLeft:
	case OriginMode::BottomMiddle:
	case OriginMode::BottomRight:
		originY = (float) rect->width;
		break;
	};

    spritesheets[currentAnimation]->setOrigin(Vector2(originX, originY).ToVector2f());
}

bool Animation2d::IsDrawable()
{
	return (animations.Length() > 0 && animations.HasKey(currentAnimation));
}

#pragma endregion

void Animation2d::SetTimePerFrame(Time timePerFrame)
{
    this->msPerFrame = timePerFrame.ToMiliseconds();
}

void Animation2d::Pause(bool flag)
{
    this->paused = flag;
}

bool Animation2d::IsPlaying()
{
    return isPlaying;
}

Dictionary<String, Vector2Ptr> Animation2d::GetCardinals()
{
    return cardinals;
}

#pragma endregion

#pragma region generic

void Animation2d::Render()
{
    if(!enabled) return;
    if(!IsDrawable()) return;

    Alce.GetWindow().draw(*spritesheets[currentAnimation]);
}

void Animation2d::Update()
{
    if(!enabled) return;
    if(!IsDrawable()) return;

    msSinceLastFrame += Chrono.deltaTime.ToMiliseconds();

    if(!paused && msSinceLastFrame >= msPerFrame)
    {
        DetermineNextFrameNum();
        SetTextureRectForFrame();
        msSinceLastFrame = 0;
    }

    spritesheets[currentAnimation]->setPosition(transform->position.ToPixels().ToVector2f());
    spritesheets[currentAnimation]->setScale((transform->scale + scale).ToVector2f());
    spritesheets[currentAnimation]->setRotation(transform->rotation);

    if(!animations.HasKey(currentAnimation)) return;

    RectShape bounds = *animations[currentAnimation].Get(currentFrameNum);
    Vector2 pixelpos = transform->position.ToPixels();

    cardinals["top-left"]->x = pixelpos.x - (bounds.width / 2.0f);
    cardinals["top-left"]->y = pixelpos.y - (bounds.height / 2.0f);

    cardinals["top-right"]->x = pixelpos.x + (bounds.width / 2.0f);
    cardinals["top-right"]->y = pixelpos.y - (bounds.height / 2.0f);

    cardinals["bottom-left"]->x = pixelpos.x - (bounds.width / 2.0f);
    cardinals["bottom-left"]->y = pixelpos.y + (bounds.height / 2.0f);

    cardinals["bottom-right"]->x = pixelpos.x + (bounds.width / 2.0f);
    cardinals["bottom-right"]->y = pixelpos.y + (bounds.height / 2.0f);
}

#pragma endregion