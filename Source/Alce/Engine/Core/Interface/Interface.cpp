#include "Interface.hpp"
#include "../Kernel/Kernel.hpp"

using namespace alce;

Canvas::Canvas() : Component("Canvas")
{
    
}

void Canvas::Init()
{
    for(auto& el: elements)
    {
        el->Init();
    }
}

void Canvas::Start()
{
    for(auto& el: elements)
    {
        el->Start();
    }
}

void Canvas::Render()
{
    for(auto& layer: layers)
    {
        auto layerElements = elements.Filter([&](UIElementPtr e) {
            return e->zIndex == layer;
        });

        for(auto& el: layerElements)
        {
            if(!el->enabled) continue;
            
            el->Render();
        }
    }
}

void Canvas::Update()
{
    for(auto& el: elements)
    {
        if(!el->enabled) continue;
        
        Vector2 position;

        position.x = el->margin.x;
        position.y = el->margin.y;

        el->transform.position = Vector2(Alce.GetWindow().mapPixelToCoords(position.ToVector2i(), *view));
        el->transform.rotation = *rotation;
        el->transform.scale.x = *scale;
        el->transform.scale.y = *scale;

        el->Update();        
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

        elements.Add(element);
        element->owner = this;

        if(layers.Empty() || !layers.Contains(element->zIndex))
        {
            layers.Add(element->zIndex);
        }

        layers.Sort([](const unsigned int a, const unsigned int b) {
            return b > a;
        });
    }
    catch(const std::exception& e)
    {
        Debug.Warning("Internal error: {}", {std::string(e.what())});
    }
    
}

void Canvas::EventManager(sf::Event& event)
{
    for(auto& element: elements)
    {
        if(element->enabled)
        {
            element->EventManager(event);
        }
    }
}