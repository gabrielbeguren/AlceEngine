#pragma once

#include <memory>

#include "../../../Libs/Libs.hpp"
#include "../Math/Math.hpp"

namespace alce
{
    class B2Mask
    {
    public:

        B2Mask()
        {
            this->category = 0x0001;
            this->mask = 0x0001 | 0x0002;
        }

        B2Mask(uint16_t category, uint16_t mask)
        {
            this->category = category;
            this->mask = mask;
        }

        uint16_t GetCategory()
        {
            return category;
        }

        uint16_t GetMask()
        {
            return mask;
        }

    protected:
        
        uint16_t category;
        uint16_t mask;
    };

    enum MaskType
    {
        mask_0,
        mask_1,
        mask_2
    };

    class B2World
    {
    public:

        B2World();

        B2World(Vector2 gravity);

        void SetGravity(Vector2 gravity);

        void SetVelocityIterations(int velocityIterations);

        void SetPositionIterations(int positionIterations);

    private:

        friend class Scene;
        friend class Rigidbody2D;
        friend class Raycast2D;
        friend class Particle;

        void Step();

        b2World* __world = nullptr;

        float timeStep = 1.0f / 80.0f;
        int velocityIterations = 12;
        int positionIterations = 14;
    };

    typedef std::shared_ptr<B2World> B2WorldPtr;
}