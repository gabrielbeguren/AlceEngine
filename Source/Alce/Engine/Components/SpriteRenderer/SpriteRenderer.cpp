#include "SpriteRenderer.hpp"

using namespace alce;

SpriteRenderer::SpriteRenderer() : Component("SpriteRenderer")
{
    sprite = std::make_unique<sf::Sprite>();

    cardinals.Set("top-left", std::make_shared<Vector2>());
    cardinals.Set("top-right", std::make_shared<Vector2>());
    cardinals.Set("bottom-left", std::make_shared<Vector2>());
    cardinals.Set("bottom-right", std::make_shared<Vector2>());
}

#pragma region implementation

void SpriteRenderer::AddTexture(String file, String name)
{
    if(textures.HasKey(name))
    {
        Debug.Warning("SpriteRenderer already contains a texture named \"{}\"", {file});
        return;
    }
    
    auto texture = Alce.GetTexture(file);

    if(texture != nullptr)
    {
        textures.Set(name, texture);
    }
}

void SpriteRenderer::SetTexture(String name)
{
    if(!textures.HasKey(name))
    {
        Debug.Warning("SpriteRenderer does not contain a texture named \"{}\"", {name});
        return;
    }

    sprite->setTexture(*textures.Get(name).get());
}

void SpriteRenderer::RemoveTexture(String name)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("SpriteRenderer does not contain a texture named \"{}\"", {name});
        return;
    }

    textures.RemoveByKey(name);
}

void SpriteRenderer::SetTextureSmooth(String name, bool flag)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("SpriteRenderer does not contain a texture named \"{name}\"", {name});
        return;
    }

    textures[name]->setSmooth(flag);
}

Vector2 SpriteRenderer::GetLocalCenter()
{
    return localCenter;
}

Vector2 SpriteRenderer::GetGlobalCenter()
{
    return globarCenter;
}

Dictionary<String, Vector2Ptr> SpriteRenderer::GetCardinals()
{
    return cardinals;
}

#pragma endregion

#pragma region generic

void SpriteRenderer::Init()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component SpriteRenderer has no association with any GameObject");
    }
}

void SpriteRenderer::Start()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component SpriteRenderer has no association with any GameObject");
    }
}

void SpriteRenderer::Render()
{
    if(transform == nullptr) return;

    Alce.GetWindow().draw(*sprite);
}

void SpriteRenderer::Update()
{
    if(transform == nullptr) return;

    sprite->setPosition(transform->position.ToPixels().ToVector2f());
    sprite->setOrigin(sprite->getLocalBounds().width / 2.0f, sprite->getLocalBounds().height / 2.0f);
    sprite->setScale(transform->scale.ToVector2f());
    sprite->setRotation(transform->rotation);

    RectShape bounds(sprite->getLocalBounds());
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
