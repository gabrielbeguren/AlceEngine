#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class TextInput : public UIElement
    {
    public:

        enum FontSize
        {
            Tiny, 
            Small, 
            Medium, 
            Large, 
            Big 
        };

        TextInput() : UIElement("TextInput")
        {

        }

        String GetText();

        void SetFocus(bool focus = true);

        bool HasFocus();

        void Init();

        void Start();

        void Update();

        void Render();

        void EventManager(sf::Event& event);

        Color backgroundColor = Colors::White;

        Color cursorColor = Colors::Black;

        FontSize fontSize = FontSize::Medium;
        Color textColor = Color(120, 120, 120);

        float borderWidth = 2;
        Color borderColor = Colors::White;

        String placeholder = "Enter text here...";
        Color placeholderColor = Color(150, 150, 150);

        float borderRadius = 2;

        float width = 400;
        float height = 40;

        String fontPath = "fonts/Consolas/CONSOLA.ttf";

        Lambda onSubmit;

    private:

        sf::RectangleShape box;
        sfe::RichText richText;
        sf::RectangleShape cursor;
        alce::String inputText;
        unsigned int cursorPosition;
        sf::Font font;
  
        bool showCursor;
        sf::Clock clock;
        bool focused;
        float textOffset;
        unsigned int maxCharacters;
        sf::ConvexShape roundedBox;

        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;
        void updateRoundedBox();
        void calculateMaxCharacters();
        void setPosition(float x, float y);
        void adjustTextPosition();
        void toggleCursorVisibility();
        void updateCursor();

        void insertText(const sf::String& text);
        void deleteCharacter();
        void moveCursorLeft();
        void moveCursorRight();
        void moveCursorStart();
        void moveCursorEnd();
    };

    typedef std::shared_ptr<TextInput> TextInputPtr;
} 