#include "UILayer.hpp"

using namespace alce;

void UILayer::Render()
{
    for(auto& component: components)
    {
        component.second->Render();
    }
}

void UILayer::AddComponent(UILayerComponentPtr component)
{
    if(components.GetKeyList().Contains(component->GetId()))
    {
        Debug.Warning("UILayer already contains component \"{}\"", {component->GetId()});
        return;
    }

    components.Set(component->GetId(), component);
}

List<UILayerComponentPtr> UILayer::GetComponents()
{
    return components.GetValueList();
}

bool UILayer::HasComponent(String componentId)
{
    return components.GetKeyList().Contains(componentId);
}

void UILayer::Destroy()
{
    if(destroyed)
    {
        Debug.Warning("UILayer is already destroyed");
        return;
    }

    destroyed = true;
}