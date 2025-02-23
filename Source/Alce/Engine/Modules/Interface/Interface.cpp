#include "Interface.hpp"
#include "../Core/Core.hpp"

using namespace alce;

Canvas::Canvas() : Component("Canvas")
{
    
}

void Canvas::Init()
{
    for(auto& p: elements)
    {
        p.first->Init();
    }
}

void Canvas::Start()
{
    for(auto& p: elements)
    {
        p.first->Start();
    }
}

void Canvas::Render()
{
    for(auto& p: elements)
    {
        if(!p.first->enabled) continue;

        p.first->Render();
    }
}

void Canvas::Update()
{
    bool needsSorting = false;

    for(auto& el: elements)
    {
        if(!el.first->enabled) continue;

        if(el.first->positionType == UIElement::Fixed)
        {
            el.first->transform.position = Vector2(Alce.GetWindow().mapPixelToCoords(el.first->position.ToVector2i(), *view));
        }
        else if(el.first->positionType == UIElement::Relative)
        {   
            Vector2 pos(Alce.GetWindowSize().x * el.first->position.x, Alce.GetWindowSize().y * el.first->position.y);
            el.first->transform.position = Vector2(Alce.GetWindow().mapPixelToCoords(pos.ToVector2i(), *view));
        }

        el.first->transform.rotation = *rotation;
        el.first->transform.scale.x = *scale;
        el.first->transform.scale.y = *scale;

        el.first->Update();  

        unsigned int currentValue = *el.second;
        if (previousValues[el.second] != currentValue)
        {
            needsSorting = true;
            previousValues[el.second] = currentValue; 
        }

        el.first->Update();
    }

    if (needsSorting)
    {
        elements.Sort([](const Pair<UIElementPtr, unsigned int*> a, const Pair<UIElementPtr, unsigned int*> b) {
            return *b.second > *a.second; 
        });
    }      
}


void Canvas::AddElement(UIElementPtr element)
{
    try
    {
        if(forbiddenElements.Contains(element->GetId()))
        {
            Debug.Warning("Element \"{}\" is forbidden for this Canvas", {element->GetId()});
            return;
        }

        element->owner = this;

        elements.Add(Pair<UIElementPtr, unsigned int*>(element, &element->zIndex));
    }
    catch(const std::exception& e)
    {
        Debug.Warning("Internal error: {}", {std::string(e.what())});
    }
    
}

void Canvas::EventManager(sf::Event& event)
{
    for(auto& p: elements)
    {
        if(p.first->enabled)
        {
            p.first->EventManager(event);
        }
    }
}