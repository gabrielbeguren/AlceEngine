#pragma once

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "../../Engine/Modules/String/String.hpp"

typedef sf::Text::Style TextStyle;

//RichText source project: https://github.com/Skyrpex/RichText

namespace sf
{
    class Font;
    class String;
    template <class T> class Rect;
    typedef Rect<float> FloatRect;
}

namespace sfe
{
    struct TextStroke
    {
        sf::Color fill = sf::Color::White;
        sf::Color outline = sf::Color::Transparent;
        float thickness = 0.f;
    };

    struct Outline
    {
        sf::Color outline = sf::Color::Transparent;
        float thickness = 0.f;
    };

    class RichText : public sf::Drawable, public sf::Transformable
    {
    public:
        // Nested class that represents a single line
        class Line : public sf::Transformable, public sf::Drawable
        {
        public:
            // Set a character's color.
            // NOTE: Attempting to access a character outside of the line bounds
            // causes a crash.
            void setCharacterColor(std::size_t pos, sf::Color color);

            // Set a character's style
            // NOTE: Attempting to access a character outside of the line bounds
            // causes a crash.
            void setCharacterStyle(std::size_t pos, sf::Text::Style style);

            // Set a character
            // NOTE: Attempting to access a character outside of the line bounds
            // causes a crash.
            void setCharacter(std::size_t pos, sf::Uint32 character);

            // Set character size
            void setCharacterSize(unsigned int size);

            void insertString(std::size_t pos, sf::String string) const;

            // Set font
            void setFont(const sf::Font& font);

            // Get the length of the line
            std::size_t getLength() const;

            // Get a character's color
            // NOTE: Attempting to access a character outside of the line bounds
            // causes a crash.
            sf::Color getCharacterColor(std::size_t pos) const;

            // Get a character's style
            // NOTE: Attempting to access a character outside of the line bounds
            // causes a crash.
            sf::Uint32 getCharacterStyle(std::size_t pos) const;

            // Get a character
            // NOTE: Attempting to access a character outside of the line bounds
            // causes a crash
            sf::Uint32 getCharacter(std::size_t pos) const;

            // Get texts
            std::vector<sf::Text>& getTexts() const;

            // Append text
            void appendText(sf::Text text);

            // Get local bounds
            sf::FloatRect getLocalBounds() const;

            // Get global bounds
            sf::FloatRect getGlobalBounds() const;

        protected:
            // Draw
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            // Get the index of the sf::Text containing the pos'th character.
            // Also changes pos to the position of the character in the sf::Text.
            std::size_t convertLinePosToLocal(std::size_t& pos) const;

            // Split a string to isolate the given character
            // into a string of its own for individual formatting
            void isolateCharacter(std::size_t pos);

            // Update geometry
            void updateGeometry() const;

            // Update geometry for a given text
            void updateTextAndGeometry(sf::Text& text) const;

            // Member data
            mutable std::vector<sf::Text> m_texts; ///< List of texts
            mutable sf::FloatRect m_bounds;        ///< Local bounds
        };

        // Constructor
        RichText();

        // Constructor
        RichText(const sf::Font& font);

        // Operators
        RichText& operator << (const TextStroke& stroke);
        RichText& operator << (const Outline& outline);
        RichText& operator << (const sf::Color& color);
        RichText& operator << (sf::Text::Style style);
        RichText& operator << (const sf::String& string);

        // Set the color of a character.
        // Attempting to access a character outside of the bounds causes a crash.
        void setCharacterColor(std::size_t line, std::size_t pos, sf::Color color);

        // Set the style of a character.
        // Attempting to access a character outside of the bounds causes a crash.
        void setCharacterStyle(std::size_t line, std::size_t pos, sf::Text::Style style);

        // Set a character
        // Attempting to access a character outside of the bounds causes a crash.
        void setCharacter(std::size_t line, std::size_t pos, sf::Uint32 character);

        // Set character size
        void setCharacterSize(unsigned int size);

        // Set font
        void setFont(const sf::Font& font);

        // Clear
        void clear();

        void erase(std::size_t line, std::size_t begin, std::size_t end);

        // Get the color of a character.
        // Attempting to access a character outside of the bounds causes a crash.
        sf::Color getCharacterColor(std::size_t line, std::size_t pos) const;

        // Get the style of a character.
        // Attempting to access a character outside of the bounds causes a crash.
        sf::Uint32 getCharacterStyle(std::size_t line, std::size_t pos) const;

        // Get a character
        // Attempting to access a character outside of the bounds causes a crash.
        sf::Uint32 getCharacter(std::size_t line, std::size_t pos) const;

        // Get text list
        const std::vector<Line>& getLines() const;

        // Get character size
        unsigned int getCharacterSize() const;

        // Get font
        const sf::Font* getFont() const;

        // Get local bounds
        sf::FloatRect getLocalBounds() const;

        // Get global bounds
        sf::FloatRect getGlobalBounds() const;

        std::string getString() const;

        std::string getStringOfLine(std::size_t line) const;

 

    protected:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        RichText(const sf::Font* font);

        sf::Text createText(const sf::String& string) const;

        void updateGeometry() const;

        mutable std::vector<Line> m_lines; ///< List of lines
        const sf::Font* m_font;            ///< Font
        unsigned int m_characterSize;      ///< Character size
        mutable sf::FloatRect m_bounds;    ///< Local bounds
        TextStroke m_currentStroke;        ///< Last used stroke
        sf::Text::Style m_currentStyle;    ///< Last style used
    };

}