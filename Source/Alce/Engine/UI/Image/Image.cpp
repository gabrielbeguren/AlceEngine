#include "Image.hpp"

using namespace alce;

void Image::AddTexture(String file, String name)
{
    if(textures.HasKey(name))
    {
        Debug.Warning("UI Image already contains a texture named \"{}\"", {file});
        return;
    }
    
    auto texture = Alce.GetTexture(file);

    if(texture != nullptr)
    {
        textures.Set(name, texture);
    }
}

void Image::SetTexture(String name)
{
    if(!textures.HasKey(name))
    {
        Debug.Warning("UI Image does not contain a texture named \"{}\"", {name});
        return;
    }

    sprite->setTexture(*textures.Get(name).get());
}

void Image::RemoveTexture(String name)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("UI Image does not contain a texture named \"{}\"", {name});
        return;
    }

    textures.RemoveByKey(name);
}

void Image::SetTextureSmooth(String name, bool flag)
{
    if(!textures.GetKeyList().Contains(name))
    {
        Debug.Warning("UI Image does not contain a texture named \"{name}\"", {name});
        return;
    }

    textures[name]->setSmooth(flag);
}

void Image::Init()
{

}

void Image::Start()
{

}

void Image::Update()
{
    sprite->setPosition(transform.position.ToVector2f());
    sprite->setScale(transform.scale.ToVector2f());
    sprite->setRotation(transform.rotation);
}

void Image::Render()
{
    Alce.GetWindow().draw(*sprite);
}

void Image::EventManager(sf::Event& event)
{

}