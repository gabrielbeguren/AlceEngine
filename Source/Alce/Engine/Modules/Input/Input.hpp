#pragma once

#include "../Core/Core.hpp"
#include "../Debug/Debug.hpp"

#define Input alce::INPUT::Instance()

namespace alce
{
    namespace Joystick
    {
        enum Button
        {
            A, B, X, Y,
            LB, RB, BACK, START,
            GUIDE, LEFT_STICK, RIGHT_STICK,
            D_PAD_UP, D_PAD_DOWN, 
            D_PAD_LEFT, D_PAD_RIGHT
        };

        class Joystick
        {
        public:

            bool IsButtonPressed(Button button);

            bool IsButtonDown(Button button);

            Vector2 GetXYAxis();

            Vector2 GetZRAxis();

            Vector2 GetUVAxis();

            Vector2 GetPovAxis();

        private:

            friend class alce::CORE;
            friend class INPUT;

            Button lastButtonPressed;
            bool buttonDown = true;

            Vector2 xyAxis, zrAxis, uvAxis, povAxis;

            Dictionary<Button, bool> buttonsPressed = {
                {Button::A, false},
                {Button::B, false},
                {Button::X, false},
                {Button::Y, false},
                {Button::LB, false},
                {Button::RB, false},
                {Button::BACK, false},
                {Button::START, false},
                {Button::GUIDE, false},
                {Button::LEFT_STICK, false},
                {Button::RIGHT_STICK, false},
                {Button::D_PAD_UP, false},
                {Button::D_PAD_DOWN, false},
                {Button::D_PAD_LEFT, false},
                {Button::D_PAD_RIGHT, false}
            };

            Dictionary<Button, bool> buttonsDown = {
                {Button::A, false},
                {Button::B, false},
                {Button::X, false},
                {Button::Y, false},
                {Button::LB, false},
                {Button::RB, false},
                {Button::BACK, false},
                {Button::START, false},
                {Button::GUIDE, false},
                {Button::LEFT_STICK, false},
                {Button::RIGHT_STICK, false},
                {Button::D_PAD_UP, false},
                {Button::D_PAD_DOWN, false},
                {Button::D_PAD_LEFT, false},
                {Button::D_PAD_RIGHT, false}
            };

        };

        typedef std::shared_ptr<Joystick> JoystickPtr;
    }

    namespace Keyboard
    {
        enum Key
        {
            Unknown = -1,
            A = 0, B, C, D, E, F, G,
            H, I, J, K, L, M, N, O,
            P, Q, R, S, T, U, V, W,
            X, Y, Z, Num0, Num1, Num2,
            Num3, Num4, Num5, Num6, Num7,
            Num8, Num9, Escape, LControl,
            LShift, LAlt, LSystem, RControl,
            RShift, RAlt, RSystem, Menu,
            LBracket, RBracket, SemiColon,
            Comma, Period, Quote, Slash,
            BackSlash, Tilde, Equal, Dash,
            Space, Return, BackSpace, Tab,
            PageUp, PageDown, End, Home,
            Insert, Delete, Add, Subtract,
            Multiply, Divide, Left, Right,
            Up, Down, Numpad0, Numpad1,
            Numpad2, Numpad3, Numpad4,
            Numpad5, Numpad6, Numpad7,
            Numpad8, Numpad9, F1, F2,
            F3, F4, F5, F6, F7, F8, F9,
            F10, F11, F12, F13, F14,
            F15, Pause, KeyCount
        };
    }

    namespace Mouse
    {
        enum Button
        {
            Left,
            Right,
            Middle,     
            XButton1,   
            XButton2,
            ButtonCount
        };
    };

    class INPUT
    {
    public:

        static INPUT& Instance()
        {
            static INPUT input;
            return input;
        }

        bool IsKeyDown(Keyboard::Key key);

        bool IsKeyPressed(Keyboard::Key key);

        bool IsMouseButtonPressed(Mouse::Button button);

        bool IsMouseButtonDown(Mouse::Button button);

        Vector2 GetMousePosition();

        Vector2 GetMousePositionOnWindow();

        Joystick::JoystickPtr GetJoystick(int joystick);

        bool IsJoystickConnected(int joystick);
    
    private:

        friend class Scene;
        friend class CORE;
        friend class Joystick::Joystick;
        friend class TextInput;

        bool enabled = true;  
        bool mouseDown = false;

        Dictionary<int, Joystick::JoystickPtr> joysticks;

        sf::Mouse::Button lastButtonPressed;

        Dictionary<Mouse::Button, bool> mouseButtonsDown = {
            {Mouse::Button::Left, false},
            {Mouse::Button::Right, false},
            {Mouse::Button::Middle, false},
            {Mouse::Button::XButton1, false},
            {Mouse::Button::XButton2, false},
            {Mouse::Button::ButtonCount, false}
        };

        Dictionary<Keyboard::Key, bool> keysDown = {
            {Keyboard::Key::Unknown, false},
            {Keyboard::Key::A, false},
            {Keyboard::Key::B, false},
            {Keyboard::Key::C, false},
            {Keyboard::Key::D, false},
            {Keyboard::Key::E, false},
            {Keyboard::Key::F, false},
            {Keyboard::Key::G, false},
            {Keyboard::Key::H, false},
            {Keyboard::Key::I, false},
            {Keyboard::Key::J, false},
            {Keyboard::Key::K, false},
            {Keyboard::Key::L, false},
            {Keyboard::Key::M, false},
            {Keyboard::Key::N, false},
            {Keyboard::Key::O, false},
            {Keyboard::Key::P, false},
            {Keyboard::Key::Q, false},
            {Keyboard::Key::R, false},
            {Keyboard::Key::S, false},
            {Keyboard::Key::T, false},
            {Keyboard::Key::U, false},
            {Keyboard::Key::V, false},
            {Keyboard::Key::W, false},
            {Keyboard::Key::X, false},
            {Keyboard::Key::Y, false},
            {Keyboard::Key::Z, false},
            {Keyboard::Key::Num0, false},
            {Keyboard::Key::Num1, false},
            {Keyboard::Key::Num2, false},
            {Keyboard::Key::Num3, false},
            {Keyboard::Key::Num4, false},
            {Keyboard::Key::Num5, false},
            {Keyboard::Key::Num6, false},
            {Keyboard::Key::Num7, false},
            {Keyboard::Key::Num8, false},
            {Keyboard::Key::Num9, false},
            {Keyboard::Key::Escape, false},
            {Keyboard::Key::LControl, false},
            {Keyboard::Key::LShift, false},
            {Keyboard::Key::LAlt, false},
            {Keyboard::Key::LSystem, false},
            {Keyboard::Key::RControl, false},
            {Keyboard::Key::RShift, false},
            {Keyboard::Key::RAlt, false},
            {Keyboard::Key::RSystem, false},
            {Keyboard::Key::Menu, false},
            {Keyboard::Key::LBracket, false},
            {Keyboard::Key::RBracket, false},
            {Keyboard::Key::SemiColon, false},
            {Keyboard::Key::Comma, false},
            {Keyboard::Key::Period, false},
            {Keyboard::Key::Quote, false},
            {Keyboard::Key::Slash, false},
            {Keyboard::Key::BackSlash, false},
            {Keyboard::Key::Tilde, false},
            {Keyboard::Key::Equal, false},
            {Keyboard::Key::Dash, false},
            {Keyboard::Key::Space, false},
            {Keyboard::Key::Return, false},
            {Keyboard::Key::BackSpace, false},
            {Keyboard::Key::Tab, false},
            {Keyboard::Key::PageUp, false},
            {Keyboard::Key::PageDown, false},
            {Keyboard::Key::End, false},
            {Keyboard::Key::Home, false},
            {Keyboard::Key::Insert, false},
            {Keyboard::Key::Delete, false},
            {Keyboard::Key::Add, false},
            {Keyboard::Key::Subtract, false},
            {Keyboard::Key::Multiply, false},
            {Keyboard::Key::Divide, false},
            {Keyboard::Key::Left, false},
            {Keyboard::Key::Right, false},
            {Keyboard::Key::Up, false},
            {Keyboard::Key::Down, false},
            {Keyboard::Key::Numpad0, false},
            {Keyboard::Key::Numpad1, false},
            {Keyboard::Key::Numpad2, false},
            {Keyboard::Key::Numpad3, false},
            {Keyboard::Key::Numpad4, false},
            {Keyboard::Key::Numpad5, false},
            {Keyboard::Key::Numpad6, false},
            {Keyboard::Key::Numpad7, false},
            {Keyboard::Key::Numpad8, false},
            {Keyboard::Key::Numpad9, false},
            {Keyboard::Key::F1, false},
            {Keyboard::Key::F2, false},
            {Keyboard::Key::F3, false},
            {Keyboard::Key::F4, false},
            {Keyboard::Key::F5, false},
            {Keyboard::Key::F6, false},
            {Keyboard::Key::F7, false},
            {Keyboard::Key::F8, false},
            {Keyboard::Key::F9, false},
            {Keyboard::Key::F10, false},
            {Keyboard::Key::F11, false},
            {Keyboard::Key::F12, false},
            {Keyboard::Key::F13, false},
            {Keyboard::Key::F14, false},
            {Keyboard::Key::F15, false},
            {Keyboard::Key::Pause, false},
            {Keyboard::Key::KeyCount, false}
        };

        INPUT(){ };
        INPUT(INPUT const&);
        void operator=(INPUT const&);
    };
}