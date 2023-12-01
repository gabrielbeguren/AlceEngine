#pragma once

#include "../TestScene.hpp"

using namespace alce;

namespace test
{
    class Wall : public GameObject
    {
    public:

        Wall(const Vector2& position);

        void Init();

        void Start();

    private:

        Rigidbody2DPtr rb2d;
    };

    typedef std::shared_ptr<Wall> WallPtr;
}