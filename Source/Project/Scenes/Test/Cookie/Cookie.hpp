#pragma once

#include "../TestScene.hpp"

using namespace alce;

namespace test
{
    class Cookie : public GameObject
    {
    public:

        Cookie(String tag, bool flag = false);

        void Init();

        void Start();

        void Update();

    private:

        ParticleSystemPtr ps;
        SpriteRendererPtr sr;
        bool flag = false;

        String tag;
    };

    typedef std::shared_ptr<Cookie> CookiePtr;
}