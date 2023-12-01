#pragma once

#include <memory>
#include "../Transform/Transform.hpp"
#include "../../../Libs/Libs.hpp"

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

        Transform transform;
    
    protected:

        friend class Scene;
        friend class ParticleSystem;
        friend class RaycastCallback;
        friend class Raycast2D;

        String id;

        Object* scene = nullptr;

    };

    typedef std::shared_ptr<Generic> GenericPtr;
}