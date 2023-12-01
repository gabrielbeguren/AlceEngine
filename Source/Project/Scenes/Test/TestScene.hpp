#pragma once

#include "../../../Alce/Alce.hpp"

using namespace alce;

namespace test
{
    class TestScene : public Scene
    {
    public:
        
        TestScene();

        void Init() override;

        void Start() override;        
        
    };

    typedef std::shared_ptr<TestScene> TestScenePtr;
}