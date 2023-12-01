#pragma once

#include "../../Core/Core.hpp"

namespace alce
{
    class Particle : public GameObject
    {
    public:

        Particle();

        ~Particle();

        void SetDensity(float density);

        void SetFriction(float friction);

        void SetRestitution(float restitution);

        void SetRestitutionThreshold(float restitutionThreshold);

        void ApplyForce(Vector2 force, bool wake = true);

        void ApplyLinearForce(Vector2 force, bool wake = true);

        void SetLinearVelocity(Vector2 linearVelocity);

        void SetHorizontalVelocity(float vy);

        void SetVerticalVelocity(float vx);

        void SetAngularVelocity(float va);

        void SetAngularDamping(float ad);

        void SetLinearDamping(float ld);

        void ApplyAngularImpulse(float impulse);

        void ApplyTorque(float torque, bool wake = true);

        void SetAngle(float angle);

        void SetFixedRotation(bool flag = true);

        void SetLifetime(Time lifetime);

        void Update();

    private:

        friend class ParticleSystem;

        void Create(Vector2 position, bool enableCollision);

        void Config(std::function<void(Particle&)> configLambda)
        {
            if(configLambda) configLambda(*this);
        }

        Time lifetime = Time({
            {"seconds", 1.0f}
        });

        float density = 10.0f;
        float friction = 1.0f;
        float restitution = 0.0f;
        float restitutionThreshold = 0.0f;
        float radius = 0;

        b2Body* body = nullptr;
        b2Fixture* fixture;
        B2WorldPtr world = nullptr;
        ContactListenerPtr contactListener;

        RectShapePtr shape;
        Vector2 shapePos;
    };

    typedef std::shared_ptr<Particle> ParticlePtr;

    class ParticleSystem : public Component
    {
    public:

        ParticleSystem();

        void Init();

        void Start();

        void Update();

        void Render();

        void DebugRender();

        void SetDelay(Time delay);

        void SetEmitArea(ShapePtr emitArea);

        void Emit();

        void Stop();

        void Behavior(std::function<void(Particle&)> behaviorLambda)
        {
            this->behaviorLambda = behaviorLambda;
        }

        Vector2 offset = Vector2(0.0f, 0.0f);

        bool enableCollision = false;

    private:

        Dictionary<float, TexturePtr> textures;
        List<ParticlePtr> particles;

        std::function<void(Particle&)> behaviorLambda = [](Particle& particle) {
            particle.ApplyForce(Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)) * 0.1f);
            particle.SetLifetime(Time({
                {"seconds", 2.0f}
            }));
            particle.sortingLayer = 1;
            particle.SetDensity(1.0f);
            particle.SetFixedRotation();
        };

        ShapePtr emitArea = std::make_shared<alce::RectShape>(30.0f, 30.0f);

        Time delay;
        Time elapsed;

        bool emit = false;
    };

    typedef std::shared_ptr<ParticleSystem> ParticleSystemPtr;
}