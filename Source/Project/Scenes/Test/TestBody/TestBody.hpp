#pragma once

#include "../TestScene.hpp"

using namespace alce;

namespace test
{
    class TestBody : public GameObject
    {
    public:

        TestBody();

        void Init();

        void Start();

        void Update();

        void OnCollisionEnter(GameObject* other);

        void OnCollisionExit(GameObject* other);

        void OnImpact(GameObject* other);

    private:

        Rigidbody2DPtr rb2d;
        SpriteRendererPtr sr;
        CameraPtr camera;
        ParticleSystemPtr ps;
        Raycast2DPtr raycast;
        Animation2dPtr animation;
    };

    typedef std::shared_ptr<TestBody> TestBodyPtr;
}