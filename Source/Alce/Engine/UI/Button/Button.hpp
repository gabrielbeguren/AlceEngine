#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class Button : public UIElement
    {
    public:

        Button() : UIElement("Button")
        {
            padding = Vector2(7, 7);
        }

        void Init();

        void Start();

        void Update();

        void Render();

        void EventManager(sf::Event& event);

        Color backgroundColor = Color("#808080");
        Color mouseOverBackgroundColor = Color("#999999");
        Color onClickBackgroundColor = Color("#7A7A7A");
        Color textColor = Colors::White;
        Color mouseOverTextColor = Colors::White;

        float borderWidth = 2;
        Color borderColor = Colors::Black;
        float borderRadius = 2;

        unsigned int fontSize = 18;
        String fontPath = "fonts/Consolas/CONSOLA.ttf";
        String text = "Button";

        Lambda onClick;
        Lambda onMouseEnter;
        Lambda onMouseOut;

    private:

        sf::RectangleShape box;
        sf::ConvexShape roundedBox;

        sfe::RichText richText;
        sf::Font font;

        bool isMouseOver = false;
        bool isOnClick = false;
        bool prevMouseOver = false;
        bool isMousePressed = false;
    };

    typedef std::shared_ptr<Button> ButtonPtr;
}