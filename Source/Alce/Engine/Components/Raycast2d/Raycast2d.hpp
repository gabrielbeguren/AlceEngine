#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class Raycast2D : public Component
    {
    public:
        Raycast2D();

        void Init();

        void Update();

        void DebugRender();

        float length = 5.0f;
        Vector2 direction = Vector2(0.0f, -1.0f);

    private:
        friend class GameObject;

        B2WorldPtr world = nullptr;
        ContactListenerPtr contactListener;

        class RaycastCallback : public b2RayCastCallback
        {
        public:
            bool hit = false;
            b2Fixture* fixture = nullptr;
            b2Vec2 point;
            b2Vec2 normal;
            GameObject* owner;
            GameObject* currentImpact = nullptr;

            float ReportFixture(b2Fixture* f, const b2Vec2& p, const b2Vec2& n, float fraction) override 
            {
                GameObject* other = static_cast<GameObject*>(f->GetBody()->attachedObject);

                owner->OnImpact(other);
                other->OnImpact(owner);

                hit = true;
                fixture = f;
                point = p;
                normal = n;
                currentImpact = other;

                return fraction;
            }
        };

        RaycastCallback callback;
        GameObject* previousImpact = nullptr;
    };

    typedef std::shared_ptr<Raycast2D> Raycast2DPtr;
}
