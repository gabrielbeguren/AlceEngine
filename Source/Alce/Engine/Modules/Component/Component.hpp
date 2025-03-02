#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Transform/Transform.hpp"
#include "../Generic/Generic.hpp"
#include "../../../Libs/Libs.hpp"

namespace alce
{
    class Component : public Object
    {
    public: 

        Component(String id)
        {
            this->id = id;
        }

        virtual void Render()
        {

        }

        virtual void DebugRender()
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

        String GetId()
        {
            return id;
        }

        bool enabled = true;

        unsigned int sortingLayer = 0;

        Transform* transform = nullptr;
    
    protected:

        friend class GameObject;
        friend class Scene;
        friend class Raycast2D;

        String id;
        Object* owner;
    };

    typedef std::shared_ptr<Component> ComponentPtr;
}