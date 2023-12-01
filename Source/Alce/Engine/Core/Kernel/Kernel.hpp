#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Joystick.hpp>
#include <fstream>

#ifdef _WIN32 
    #include <windows.h>
    #include "wtypes.h"
#elif __linux__ 
    #include <X11/Xlib.h>
    #undef None
#elif __APPLE__
    #include <CoreGraphics/CoreGraphics.h>
#endif

#include "../../../Libs/Libs.hpp"
#include "../Chrono/Chrono.hpp"
#include "../Math/Math.hpp"
#include "../Scene/Scene.hpp"
#include "../Color/Color.hpp"

#define Kernel alce::KERNEL::Instance()

namespace alce
{
    typedef std::shared_ptr<sf::Texture> TexturePtr;
    typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;
    typedef std::shared_ptr<sf::Font> FontPtr;

    enum DisplayMode
    {
        Close,
        Default,
        Fullscreen,
        None,
        Resize,
        Titlebar
    };

    enum MemoryUnit 
    {
        byte,
        kilobyte,
        megabyte,
        gigabyte
    };

    class KERNEL
    {
    public:

        static KERNEL& Instance()
        {
            static KERNEL kernel;
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

        bool stanby = false;

        void Run();

    private:

        ScenePtr currentScene = nullptr;
        bool restart = false;

        Dictionary<String, ScenePtr> scenes;
        Dictionary<String, TexturePtr> textures;
        Dictionary<String, SoundBufferPtr> sounds;
        Dictionary<String, FontPtr> fonts;

        sf::RenderWindow window;
        String windowTitle;
        Color clearColor = Colors::Black;
        String iconFile = "alce.png";

        bool exit = false;
        float fps = 0;

        KERNEL() { };
        KERNEL(KERNEL const&);
    };
}