#pragma once

#include "../String/String.hpp"
#include "../Scene/Scene.hpp"
#include <memory>

#define ARL alce::ARL_PROCESSOR::Instance()

namespace alce
{
    class ARL_PROCESSOR
    {
    public:

        static ARL_PROCESSOR& Instance()
	    {
		    static ARL_PROCESSOR arlp;
		    return arlp;
	    }

    private:

        friend class Scene;

        Scene* currentScene = nullptr;

        void Shell(String prompt, Scene* scene);

        void Process(String command);

    };
};