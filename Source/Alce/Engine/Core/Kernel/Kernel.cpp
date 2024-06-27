#include "Kernel.hpp"
#include "../Input/Input.hpp"

using namespace alce;

void KERNEL::Window(String windowTitle, DisplayMode displayMode, Vector2 size, int antialiasing)
{
	sf::Uint32 style = sf::Style::Default;

	switch(displayMode)
	{
	case DisplayMode::Close:
		style = sf::Style::Close;
		break;
	case DisplayMode::Default:
		style = sf::Style::Default;
		break;
	case DisplayMode::Fullscreen:
		size = GetScreenResolution();
		style = sf::Style::None;
		break;
	case DisplayMode::None:
		style = sf::Style::None;
		break;
	case DisplayMode::Resize:
		style = sf::Style::Resize;
		break;
	case DisplayMode::Titlebar:
		style = sf::Style::Titlebar;
		break;
	}

	if (style == sf::Style::Fullscreen)
	{
		size = GetScreenResolution();
	}

	sf::ContextSettings cs = sf::ContextSettings(0, 0, 1);
	cs.antialiasingLevel = antialiasing;
	window.create(sf::VideoMode(size.x, size.y), sf::String(~windowTitle), style, cs);
	this->windowTitle = windowTitle;
	window.setVerticalSyncEnabled(true);

	SetWindowIcon(iconFile);
	Debug.clock.restart();
}

sf::RenderWindow& KERNEL::GetWindow()
{
	return window;
}

Vector2 KERNEL::GetWindowSize()
{
	return Vector2(window.getSize());
}

#ifdef _WIN32 

Vector2 KERNEL::GetScreenResolution() 
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return Vector2(desktop.right, desktop.bottom);
}

#elif __linux__  // Linux

Vector2 Kernel::GetScreenResolution() 
{
    Display* display = XOpenDisplay(NULL);
    Screen* screen = DefaultScreenOfDisplay(display);
    int width = WidthOfScreen(screen);
    int height = HeightOfScreen(screen);
    XCloseDisplay(display);
    return Vector2(width, height);
}

#elif __APPLE__  // macOS
#include <CoreGraphics/CoreGraphics.h>

Vector2 Kernel::GetScreenResolution() 
{
    CGSize screenSize = CGDisplayScreenSize(CGMainDisplayID());
    return Vector2(screenSize.width, screenSize.height);
}

#else
#error Unsupported platform
#endif


void KERNEL::SetWindowIcon(String file)
{
	file = "./Assets/" + file.ToAnsiString();

	auto icon = sf::Image{};

	if(icon.loadFromFile(file.ToAnsiString()))
	{
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		iconFile = ~file;
	}
	else Debug.Warning("Error loading file \"{}\"", {file});
}

void KERNEL::AddScene(ScenePtr scene)
{
	if(scenes.GetKeyList().Contains(scene->GetName()))
	{
		Debug.Warning("A scene named \"{}\" already exists", {scene->GetName()});
		return;
	}

	scene->Init();

	for(auto& sl: scene->sortingLayers)
	{
		for(auto& go: *sl.second.get())
		{
			go->Init();

			for(auto& c: go->GetComponents())
			{
				c->Init();
			}
		}
	}

	scenes.Set(scene->GetName(), scene);
}

void KERNEL::RemoveScene(String name)
{
	if(!scenes.GetKeyList().Contains(name))
	{
		Debug.Warning("There is no scene named \"{}\"", {name});
		return;
	}

	scenes[name]->Clear();
	scenes.RemoveByKey(name);
}

ScenePtr KERNEL::GetScene(String name)
{
	try
	{
		return scenes.Get(name);
	}
	catch (const std::exception& e)
	{
		Debug.Warning("Internal error: {}", {std::string(e.what())});
		return nullptr;
	}
}

void KERNEL::SetCurrentScene(String name)
{
	if(!scenes.GetKeyList().Contains(name))
	{
		Debug.Warning("There is no scene named \"{}\"", {name});
		return;
	}

	try
	{
		currentScene = scenes.Get(name);
		currentScene->Start();

		for(auto& sl: currentScene->sortingLayers)
		{
			for(auto& go: *sl.second.get())
			{
				go->Start();

				for(auto& c: go->GetComponents())
				{
					c->Start();
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		Debug.Warning("Internal error: {}", {std::string(e.what())});
	}
}

ScenePtr KERNEL::GetCurrentScene()
{
	return currentScene;
}

TexturePtr KERNEL::GetTexture(String file)
{ 
	file = "./Assets/" + file.ToAnsiString();

	if(textures.HasKey(file)) return textures[file];

	TexturePtr texture = std::make_shared<sf::Texture>();
	if(!texture->loadFromFile(file.ToAnsiString()))
	{
		Debug.Warning("Unable to load texture from file \"{}\"", {file});
		return nullptr;
	}
	textures.Set(file, texture);

	return texture;
}

SoundBufferPtr KERNEL::GetSoundBuffer(String file)
{
	file = "./Assets/" + file.ToAnsiString();

	if(sounds.HasKey(file)) return sounds[file];

	SoundBufferPtr sound = std::make_shared<sf::SoundBuffer>();

	if(!sound->loadFromFile(file.ToAnsiString()))
	{
		Debug.Warning("Unable to load sound buffer from file \"{}\"", {file});
		return nullptr;
	}
	sounds.Set(file, sound);
	
	return sound;
}

FontPtr KERNEL::GetFont(String file)
{
	file = "./Assets/" + file.ToAnsiString();

	if(fonts.HasKey(file)) return fonts[file];

	FontPtr font = std::make_shared<sf::Font>();

	if(!font->loadFromFile(file.ToAnsiString()))
	{
		Debug.Warning("Unable to load font from file \"{}\"", {file});
		return nullptr;
	}

	fonts.Set(file, font);

	return font;
}

void KERNEL::SetClearColor(Color color)
{
	clearColor = color;
}

float KERNEL::GetFPS()
{
	return fps;
}

EventEmitterPtr KERNEL::GetEventEmitter()
{
	return eventEmitter;
}

void KERNEL::Run()
{
	sf::Clock clock;
	sf::Event event;

	int frameCount = 0;
	sf::Time second = sf::seconds(1.0f);
	sf::Time elapsed, accTime;

	while(window.isOpen() && !exit)
	{
		if(currentScene != nullptr)
		{
			while(window.pollEvent(event))
			{
				currentScene->EventsManager(event);
			}

			elapsed = clock.restart();
			accTime += elapsed;
			frameCount++;	

			if(accTime >= second)
			{
				fps = static_cast<float>(frameCount) / accTime.asSeconds();
				accTime -= second;
				frameCount = 0;
			}

			sf::Joystick::update();

			for(int i = 0; i <= sf::Joystick::Count; i++)
			{
				if(sf::Joystick::isConnected(i) && Input.enabled)
				{
					if(!Input.joysticks.HasKey(i)) 
					{
						Input.joysticks.Set(i, std::make_shared<Joystick::Joystick>());
					}

					float x = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(0));
					float y = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(1));
					float z = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(2));
					float r = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(3));
					float u = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(4));
					float v = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(5));
					float povx = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(6));
					float povy  = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(7));

					Input.joysticks[i]->xyAxis = Vector2(x, y);
					Input.joysticks[i]->zrAxis = Vector2(z, r);
					Input.joysticks[i]->uvAxis = Vector2(u, v);
					Input.joysticks[i]->povAxis = Vector2(povx, povy);

					for(int j = 0; j <= 14; j++)
					{
						Input.joysticks[i]->buttonsPressed.Set(static_cast<Joystick::Button>(j), sf::Joystick::isButtonPressed(i, j));
					}
				}
			}

			Chrono.deltaTime.Reset().AddMiliseconds(elapsed.asMilliseconds());
			currentScene->Update();			

			window.clear(clearColor.ToSFMLColor());
			currentScene->Render();

			window.display();
		}
		else
		{
			//TODO: Escena por defecto

			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed) window.close();
			}

			window.clear(~clearColor);
			window.display();
		}
	}
}