#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Joystick.hpp>
#include <fstream>
#include <thread>
#include <atomic>
#include <iostream>

#include "../../../Libs/Libs.hpp"
#include "../Chrono/Chrono.hpp"
#include "../Math/Math.hpp"
#include "../Scene/Scene.hpp"
#include "../Color/Color.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventEmitter.hpp"

#include <sstream>
#include <tchar.h>
#include <ntstatus.h>
#include <winternl.h>
#include <windows.h>
#include "wtypes.h"

#define Alce alce::CORE::Instance()

namespace alce
{
    typedef std::shared_ptr<sf::Texture> TexturePtr;
    typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;
    typedef std::shared_ptr<sf::Font> FontPtr;

    typedef std::function<void()> Lambda;

    typedef LONG (NTAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

    enum DisplayMode
    {
        Close,
        Default,
        Fullscreen,
        None,
        Resize,
        Titlebar
    };

    class CORE
    {
    public:

        static CORE& Instance()
        {
            static CORE kernel;
            return kernel;
        }

        void Window(String title, DisplayMode displayMode = DisplayMode::Default, Vector2 size = Vector2(1280, 720), int antialiasing = 0);

        sf::RenderWindow& GetWindow();

        Vector2 GetScreenResolution();

        Vector2 GetWindowSize();

        void SetWindowIcon(String file);

        void AddScene(ScenePtr scene);

        template<typename T>
        void AddScene()
        {
            ScenePtr scene = std::make_shared<T>();
            AddScene(scene);
        }

        void RemoveScene(String name);

        ScenePtr GetScene(String name);

        void SetCurrentScene(String name);

        ScenePtr GetCurrentScene();

        TexturePtr GetTexture(String file);

        SoundBufferPtr GetSoundBuffer(String file);

        FontPtr GetFont(String file);

        void SetClearColor(Color color);

        float GetFPS();

        String GetArchitecture();

        String GetWindowsVersion();

        String GetRAM();

        String GetRAMinUse();

        String GetCPU();

        String GetGPU();

        String GetVRAM();

        String GetDirectXVersion();

        String GetMonitorInfo();

        String GetWindowInfo();

        EventEmitterPtr GetEventEmitter();

        bool stanby = false;

        void Run();

    private:

        friend class ARL_PROCESSOR;

        ScenePtr currentScene = nullptr;
        bool restart = false;

        Dictionary<String, ScenePtr> scenes;
        Dictionary<String, TexturePtr> textures;
        Dictionary<String, SoundBufferPtr> sounds;
        Dictionary<String, FontPtr> fonts;

        sf::RenderWindow window;
        String windowTitle;
        Color clearColor = Color("#41424C");
        String iconFile = "logo.png";

        EventEmitterPtr eventEmitter = nullptr;

        std::atomic<bool> exit = {false};
        float fps = 0;

        void ConsoleInputHandler();
        
        CORE() { };
        CORE(CORE const&);
    };
}