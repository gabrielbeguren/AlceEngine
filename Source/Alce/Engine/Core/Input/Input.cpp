#include "Input.hpp"

using namespace alce;

bool alce::Joystick::Joystick::IsButtonPressed(alce::Joystick::Button button)
{
	if(!Input.read) 
    {
        Debug.Warning("Input reading is disabled");
        return false;
    }

	return buttonsPressed[button];
}

bool alce::Joystick::Joystick::IsButtonDown(alce::Joystick::Button button)
{
	if(!Input.read) 
    {
        Debug.Warning("Input reading is disabled");
        return false;
    }

	if (IsButtonPressed(button))
	{
		if(!buttonsDown[button])
		{
			buttonsDown.Set(button, true);
			return true;
		}
		
		return false;
	}
	else 
	{
		buttonsDown.Set(button, false);
		return false;
	}
}

Vector2 alce::Joystick::Joystick::GetXYAxis()
{
	return xyAxis;
}

Vector2 alce::Joystick::Joystick::GetZRAxis()
{
	return zrAxis;
}

Vector2 alce::Joystick::Joystick::GetUVAxis()
{
	return uvAxis;
}

Vector2 alce::Joystick::Joystick::GetPovAxis()
{
	return povAxis;
}

bool alce::INPUT::IsKeyDown(Keyboard::Key key)
{
    if(!read) 
    {
        Debug.Warning("Input reading is disabled");
        return false;
    }

    if(IsKeyPressed(key))
	{
		if(!keysDown[key])
		{
			keysDown.Set(key, true);
			return true;
		}

		return false;
	}
	else
	{
		keysDown.Set(key, false);
		return false;
	}
}

bool alce::INPUT::IsKeyPressed(Keyboard::Key key)
{
    if(!read) 
    {
        Debug.Warning("Input reading is disabled");
        return false;
    }

    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

bool alce::INPUT::IsMouseButtonPressed(Mouse::Button button)
{
    if(!read) 
    {
        Debug.Warning("Input reading is disabled");
        return false;
    }

    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

bool alce::INPUT::IsMouseButtonDown(Mouse::Button button)
{
    if(!read) 
    {
        Debug.Warning("Input reading is disabled");
        return false;
    }

    if(IsMouseButtonPressed(button))
	{
		if(!mouseButtonsDown[button])
		{
			mouseButtonsDown.Set(button, true);
			return true;
		}

		return false;
	}
	else
	{
		mouseButtonsDown.Set(button, false);
		return false;
	}
}

Vector2 alce::INPUT::GetMousePosition()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Alce.GetWindow());

	return Vector2(Alce.GetWindow().mapPixelToCoords(pixelPos));
}

Vector2 alce::INPUT::GetMousePositionOnWindow()
{
	return Vector2(sf::Mouse::getPosition(Alce.GetWindow()));
}

Joystick::JoystickPtr alce::INPUT::GetJoystick(int joystick)
{
	if(joystick > 7 || joystick > 0)
	{
		Debug.Warning("Invalid joystick \"{}\"", {joystick});
		return nullptr;
	}

	if(!joysticks.HasKey(joystick))
	{
		Debug.Warning("Joystick {} not connected", {joystick});
		return nullptr;
	}

	return joysticks[joystick];
}

bool alce::INPUT::IsJoystickConnected(int joystick)
{
	return joysticks.HasKey(joystick);
}
