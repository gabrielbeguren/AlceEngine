#include "Core.hpp"
#include "../Input/Input.hpp"
#include "../Storage/Storage.hpp"

using namespace alce;

void CORE::Window(String windowTitle, DisplayMode displayMode, Vector2 size, int antialiasing)
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
	Storage.Init();
}

sf::RenderWindow& CORE::GetWindow()
{
	return window;
}

Vector2 CORE::GetWindowSize()
{
	return Vector2(window.getSize());
}

Vector2 CORE::GetScreenResolution() 
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return Vector2(desktop.right, desktop.bottom);
}

void CORE::SetWindowIcon(String file)
{
	file = "./Assets/" + file.ToAnsiString();

	auto icon = sf::Image{};

	if(icon.loadFromFile(file.ToAnsiString()))
	{
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		iconFile = ~(file.Replace("./Assets/", ""));
	}
	else Debug.Warning("Error loading file \"{}\"", {file});
}

void CORE::AddScene(ScenePtr scene)
{
	if(scenes.GetKeyList().Contains(scene->GetName()))
	{
		Debug.Warning("A scene named \"{}\" already exists", {scene->GetName()});
		return;
	}

	Folder scenesFolder("./Scenes");

	if(!scenesFolder.Exists())
	{
		scenesFolder.Create();
	}

	scene->Init();

	if(scene->persist)
	{
		if(!scene->JsonFileExists())
		{
			scene->Save();
		}
	}

	scenes.Set(scene->GetName(), scene);
}

void CORE::RemoveScene(String name)
{
	if(!scenes.GetKeyList().Contains(name))
	{
		Debug.Warning("There is no scene named \"{}\"", {name});
		return;
	}

	scenes[name]->Clear();
	scenes.RemoveByKey(name);
}

ScenePtr CORE::GetScene(String name)
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

void CORE::SetCurrentScene(String name)
{
	if(!scenes.GetKeyList().Contains(name))
	{
		Debug.Warning("There is no scene named \"{}\"", {name});
		return;
	}

	try
	{
		currentScene = scenes.Get(name);

		if(currentScene->persist)
		{
			currentScene->loading = true;
			currentScene->LoadFromJson();
			currentScene->loading = false;
		}

		currentScene->Start();

		for(auto& sl: currentScene->sortingLayers)
		{
			for(auto& go: *sl.second.get())
			{
				go->Start();

				for(auto& c: go->GetComponents())
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

ScenePtr CORE::GetCurrentScene()
{
	return currentScene;
}

TexturePtr CORE::GetTexture(String file)
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

SoundBufferPtr CORE::GetSoundBuffer(String file)
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

FontPtr CORE::GetFont(String file)
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

void CORE::SetClearColor(Color color)
{
	clearColor = color;
}

float CORE::GetFPS()
{
	return fps;
}

String CORE::GetArchitecture()
{
	SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);

    std::ostringstream oss;
    oss << "Architecture: ";

    switch (sysInfo.wProcessorArchitecture) 
	{
        case PROCESSOR_ARCHITECTURE_AMD64: oss << "x86_64 (64-bit)"; break;
        case PROCESSOR_ARCHITECTURE_INTEL: oss << "x86 (32-bit)"; break;
        case PROCESSOR_ARCHITECTURE_ARM: oss << "ARM"; break;
        case PROCESSOR_ARCHITECTURE_ARM64: oss << "ARM64"; break;
        default: oss << "Unknown"; break;
    }

    return String(oss.str());
}

String CORE::GetWindowsVersion()
{
	RTL_OSVERSIONINFOW osvi = {0};
    osvi.dwOSVersionInfoSize = sizeof(osvi);

    HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
    if (hMod) 
	{
        RtlGetVersionPtr RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
        if (RtlGetVersion) 
		{
            if (RtlGetVersion(&osvi) == STATUS_SUCCESS) 
			{
                std::ostringstream oss;
                oss << osvi.dwMajorVersion << "." << osvi.dwMinorVersion;
                if (osvi.dwBuildNumber >= 22000) 
				{
                    oss << " (Windows 11)";
                } else if (osvi.dwBuildNumber >= 10240) 
				{
                    oss << " (Windows 10)";
                }
                return String(oss.str());
            }
        }
    }
    return "Not available";
}

String CORE::GetRAM()
{
	MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    std::ostringstream oss;
    oss << (memInfo.ullTotalPhys / (1024 * 1024)) << " MB";
    return String(oss.str());
}

String CORE::GetRAMinUse()
{
	MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    std::ostringstream oss;
    oss <<((memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024)) << " MB";
    return String(oss.str());
}

String CORE::GetCPU()
{
	HKEY hKey;
    TCHAR cpuName[256];
    DWORD size = sizeof(cpuName);
    std::ostringstream oss;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey) == ERROR_SUCCESS) 
	{
        if (RegQueryValueEx(hKey, _T("ProcessorNameString"), nullptr, nullptr, (LPBYTE)cpuName, &size) == ERROR_SUCCESS) 
		{
            oss << cpuName;
        } 
		else 
		{
            oss << "Not available";
        }
        RegCloseKey(hKey);
    } 
	else 
	{
        oss << "Error accessing processor registry";
    }
    
    return String(oss.str());
}

String CORE::GetGPU()
{
	DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    std::ostringstream oss;

    if (EnumDisplayDevices(nullptr, 0, &displayDevice, 0)) 
	{
        oss << displayDevice.DeviceString;
    } 
	else 
	{
        oss << "Not available";
    }
    
    return oss.str();
}

String CORE::GetVRAM()
{
	DWORD vram = 0;
    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    std::ostringstream oss;

    if (EnumDisplayDevices(nullptr, 0, &displayDevice, 0)) 
	{
        DEVMODE devMode;
        devMode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode)) 
		{
            vram = devMode.dmPelsWidth * devMode.dmPelsHeight * (devMode.dmBitsPerPel / 8) / (1024 * 1024);
        }
    }
    
    oss << vram << " MB";
    return String(oss.str());
}

String CORE::GetDirectXVersion()
{
	DWORD version = 0;
    std::ostringstream oss;

    if (RegGetValue(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\DirectX"), _T("Version"), RRF_RT_REG_SZ, nullptr, nullptr, &version) == ERROR_SUCCESS) 
	{
        oss << version;
    } 
	else 
	{
        oss << "Not available";
    }

    return oss.str();
}

String CORE::GetMonitorInfo()
{
	std::ostringstream oss;
    
    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    int deviceIndex = 0;
    
    while (EnumDisplayDevices(nullptr, deviceIndex, &displayDevice, 0)) 
	{
		if(deviceIndex > 0) oss << "\n";
        oss << "Monitor " << deviceIndex + 1 << ": " << displayDevice.DeviceString << "\n";
        
        DEVMODE devMode;
        devMode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode)) 
		{
            oss << "  Resolution: " << devMode.dmPelsWidth << "x" << devMode.dmPelsHeight << "\n";
            oss << "  Refresh Rate: " << devMode.dmDisplayFrequency << " Hz\n";
            oss << "  Bits Per Pixel: " << devMode.dmBitsPerPel;
        }
        
        deviceIndex++;
    }
    
    return String(oss.str());
}

String CORE::GetWindowInfo()
{
	std::ostringstream oss;

    oss << "Window Title: " << windowTitle.ToAnsiString() << "\n";

    sf::Vector2u windowSize = window.getSize();
    oss << "Window Size: " << windowSize.x << "x" << windowSize.y << "\n";

    sf::Vector2i windowPosition = window.getPosition();
    oss << "Window Position: (" << windowPosition.x << ", " << windowPosition.y << ")\n";

    sf::ContextSettings settings = window.getSettings();
    oss << "OpenGL Version: " << settings.majorVersion << "." << settings.minorVersion << "\n";
    oss << "Depth Bits: " << settings.depthBits << "\n";
    oss << "Stencil Bits: " << settings.stencilBits << "\n";
    oss << "Antialiasing Level: " << settings.antialiasingLevel << "\n";

    oss << "Window is Open: " << (window.isOpen() ? "Yes" : "No");

    return String(oss.str());
}

EventEmitterPtr CORE::GetEventEmitter()
{
	return eventEmitter;
}

void CORE::ConsoleInputHandler()
{
    std::string input;

    while (!exit)
    {
        std::cout << ">> ";

        if (!std::getline(std::cin, input)) 
            break;

        if (input == "exit")
        {
            exit = true;
            break;
        }

        if (!input.empty())
        {
            GetCurrentScene()->Shell(input);
        }
    }
}

void CORE::Run()
{
    sf::Clock clock;
    sf::Event event;

    int frameCount = 0;
    sf::Time second = sf::seconds(1.0f);
    sf::Time elapsed, accTime;

    std::thread inputThread([this]() { ConsoleInputHandler(); });

    while (window.isOpen() && !exit)
    {
        if (currentScene != nullptr)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                currentScene->EventsManager(event);
            }

            elapsed = clock.restart();
            accTime += elapsed;
            frameCount++;

            if (accTime >= second)
            {
                fps = static_cast<float>(frameCount) / accTime.asSeconds();
                accTime -= second;
                frameCount = 0;
            }
            
            // Update joysticks
            sf::Joystick::update();

            for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
            {
                if (sf::Joystick::isConnected(i) && Input.enabled)
                {
                    if (!Input.joysticks.HasKey(i))
                    {
                        Input.joysticks.Set(i, std::make_shared<Joystick::Joystick>());
                    }

                    auto joystick = Input.joysticks[i];
                    for (unsigned int j = 0; j < sf::Joystick::AxisCount; ++j)
                    {
                        float position = sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j));
                        switch(j) {
                            case 0: case 1:
                                joystick->xyAxis = Vector2(
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::X),
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::Y)
                                );
                                break;
                            case 2: case 3:
                                joystick->zrAxis = Vector2(
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::Z),
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::R)
                                );
                                break;
                            case 4: case 5:
                                joystick->uvAxis = Vector2(
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::U),
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::V)
                                );
                                break;
                            case 6: case 7:
                                joystick->povAxis = Vector2(
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::PovX),
                                    sf::Joystick::getAxisPosition(i, sf::Joystick::PovY)
                                );
                                break;
                        }
                    }

                    for (unsigned int j = 0; j < sf::Joystick::ButtonCount; ++j)
                    {
                        joystick->buttonsPressed.Set(static_cast<Joystick::Button>(j), sf::Joystick::isButtonPressed(i, j));
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
            //TODO: DEFAULT SCENE
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(~clearColor);
            window.display();
        }
    }

    exit = true;
    
    try
    {
        std::cin.rdbuf(nullptr); 
    }
    catch(const std::exception& e) { }
    
    if (inputThread.joinable()) 
    {
        inputThread.detach();
        std::terminate(); 
    }
}