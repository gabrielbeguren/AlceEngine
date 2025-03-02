#include "GameObject.hpp"
#include "../../Components/Camera/Camera.hpp"
#include "../../Components/Rigidbody2d/Rigidbody2d.hpp"
#include "../../Components/Raycast2d/Raycast2d.hpp"
#include "../Scene/Scene.hpp"

using namespace alce;

GameObject::GameObject()
{
    id = GenerateUUID();
}

GameObject::~GameObject()
{

}

void GameObject::AddTag(String tag)
{
    if(!tags.Contains(tag)) tags.Add(tag);
    else
    {
        Debug.Warning("GameObject already contains tag \"{}\"", {tag});
    }
}

void GameObject::RemoveTag(String tag)
{
    if(!tags.Contains(tag))
    {
        Debug.Warning("GameObject does not contains tag \"{}\"", {tag});
        return;
    }

    tags.RemoveIf([tag](String t){
        return t == tag;
    });
}

bool GameObject::HasTag(String tag)
{
    return tags.Contains(tag);
}

void GameObject::Destroy()
{
    if(destroyed)
    {
        Debug.Warning("GameObject is already destroyed");
        return;
    }

    destroyed = true;
    components.Clear();
}

void GameObject::AddComponent(ComponentPtr component)
{
    try
    {
        if(forbiddenComponents.Contains(component->GetId()))
        {
            Debug.Warning("Component \"{}\" is forbidden for this gameObject", {component->GetId()});
            return;
        }

        component->transform = &transform;
        components.Add(component);
        component->owner = this;

        if(layers.Empty() || !layers.Contains(component->sortingLayer))
        {
            layers.Add(component->sortingLayer);
        }

        layers.Sort([](const unsigned int a, const unsigned int b) {
            return a > b;
        });

        if(scene == nullptr) return;

        Camera* camPtr = dynamic_cast<Camera*>(component.get());
        if(camPtr) ((Scene*) scene)->cameras.Add(camPtr);
        else
        {
            Rigidbody2D* rb2D = dynamic_cast<Rigidbody2D*>(component.get());
            if(rb2D) 
            {
                rb2D->world = ((Scene*) scene)->world;
                components.SetFirst(components.Length() - 1);
            }
            else
            {
                Raycast2D* rc2d = dynamic_cast<Raycast2D*>(component.get());
                if(rc2d) rc2d->world = ((Scene*) scene)->world;
                else
                {
                    Canvas* canvas = dynamic_cast<Canvas*>(component.get());
                    if(canvas) 
                    {
                        Camera* cam = GetComponent<Camera>();
                        if(cam)
                        {
                            CanvasPtr canvasSPTR(component, canvas);
                            CameraPtr camSPTR(component, cam);
                            ((Scene*) scene)->AddCanvas(canvasSPTR, camSPTR);
                        }
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        Debug.Warning("Internal error: {}", {std::string(e.what())});
    }
}

List<ComponentPtr> GameObject::GetComponents()
{
    return components;
}

void GameObject::SetParent(GameObjectPtr gameObject)
{
    parent = gameObject;
}

void GameObject::SetParent(GameObject* gameObject)
{
    std::shared_ptr<GameObject> sharedptr(gameObject);
    parent = sharedptr;
}

void GameObject::DetachParent()
{
    if(parent == nullptr)
    {
        Debug.Warning("GameObject doesn't have any parent attached");
        return;
    }

    parent = nullptr;
}

GameObjectPtr GameObject::GetParent()
{
    return parent;
}

void GameObject::Render()
{
    for(auto layer: layers)
    {
        auto layerComponents = components.Filter([&](ComponentPtr c) {
            return c->sortingLayer == layer;
        });

        for(auto& comp: layerComponents)
        {
            if(!comp->enabled) continue;
            if(comp->GetId() == "Canvas") continue;
            comp->Render();
        }
    }
}

void GameObject::DebugRender()
{
    if(cardinals.HasKey("top-left"))
    {
        sf::RectangleShape top_left(sf::Vector2f(1, 1));
        top_left.setOutlineThickness(1.0f);
        top_left.setOutlineColor(sf::Color::Yellow);
        top_left.setPosition(cardinals["top-left"]->ToVector2f());
        Alce.GetWindow().draw(top_left);
    }

    if(cardinals.HasKey("top-right"))
    {
        sf::RectangleShape top_right(sf::Vector2f(1, 1));
        top_right.setOutlineThickness(1.0f);
        top_right.setOutlineColor(sf::Color::Yellow);
        top_right.setPosition(cardinals["top-right"]->ToVector2f());
        Alce.GetWindow().draw(top_right);
    }

    if(cardinals.HasKey("bottom-left"))
    {
        sf::RectangleShape bottom_left(sf::Vector2f(1, 1));
        bottom_left.setOutlineThickness(1.0f);
        bottom_left.setOutlineColor(sf::Color::Yellow);
        bottom_left.setPosition(cardinals["bottom-left"]->ToVector2f());
        Alce.GetWindow().draw(bottom_left);
    }

    if(cardinals.HasKey("bottom-right"))
    {
        sf::RectangleShape bottom_right(sf::Vector2f(1, 1));
        bottom_right.setOutlineThickness(1.0f);
        bottom_right.setOutlineColor(sf::Color::Yellow);
        bottom_right.setPosition(cardinals["bottom-right"]->ToVector2f());
        Alce.GetWindow().draw(bottom_right);
    }
}