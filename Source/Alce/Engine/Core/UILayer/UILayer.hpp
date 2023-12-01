#pragma once

#include <memory>

#include "../../../Libs/Libs.hpp"
#include "../Generic/Generic.hpp"
#include "../Debug/Debug.hpp"

namespace alce
{
    class UILayerComponent : public Object
    {
    public:

    virtual void Render()
        {

        }

        virtual void Init()
        {

        }

        virtual void Start()
        {

        }

        virtual void Update()
        {

        }

        virtual void EventManager(sf::Event& event)
        {

        }

        alce::String GetId()
        {
            return id;
        }

        bool enabled = true;

        Transform transform; 

        Vector2 margin = Vector2(0.0f, 0.0f);

        Vector2 size = Vector2(1.0f, 1.0f);

        float rotation = 0.0f;

    protected:

        friend class UILayer;
        friend class Scene;

        String id;
    };

    typedef std::shared_ptr<UILayerComponent> UILayerComponentPtr;

    class UILayer : public Generic
    {
    public:

        void Render();

        void AddComponent(UILayerComponentPtr component);

        List<UILayerComponentPtr> GetComponents();

        bool HasComponent(String componentId);

        template<typename T>
        T* GetComponent(String id)
        {
            return (T*) components[id].get();
        } 

        void Destroy();

    protected:

        friend class Scene;

        Dictionary<String, UILayerComponentPtr> components;

        bool destroyed = false;
    };

    typedef std::shared_ptr<UILayer> UILayerPtr;
}