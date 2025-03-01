#pragma once

#include <memory>
#include "../Transform/Transform.hpp"
#include "../../../Libs/Libs.hpp"
#include "../Collections/Collections.hpp"
#include "../String/String.hpp"
#include <typeindex>
#include <any>

namespace alce
{
    class Generic : public Object
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

        virtual void SetterManager(String name, String value)
        {

        }

        Transform transform;
    
    protected:
        
        friend class ARL_PROCESSOR;
        friend class Scene;
        friend class ParticleSystem;
        friend class RaycastCallback;
        friend class Raycast2D;

        String id;

        Object* scene = nullptr;
    };

    typedef std::shared_ptr<Generic> GenericPtr;
}