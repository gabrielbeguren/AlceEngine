#pragma once

#include "../TestScene.hpp"

using namespace alce;

namespace test
{
    class Floor : public GameObject
    {
    public:

        Floor();

        void Init();

        void Start();

        void Update();

    private:

        Rigidbody2DPtr rb2d;

        CameraPtr camera;
    };

    typedef std::shared_ptr<Floor> FloorPtr;
}