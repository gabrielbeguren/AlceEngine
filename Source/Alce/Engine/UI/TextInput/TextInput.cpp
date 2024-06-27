#include "TextInput.hpp"

using namespace alce;

void TextInput::Init()
{

}

void TextInput::Start()
{

}

String TextInput::GetText()
{
    return inputText;
}

void TextInput::SetFocus(bool focus)
{
    focused = focus;

    if(focused)
    {
        Input.enabled = false;
    }
    else
    {
        Input.enabled = true;
    }

}

bool TextInput::HasFocus()
{
    return focused;
}

void TextInput::Update()
{
    box.setPosition(transform.position.x, transform.position.y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);

    font = *Alce.GetFont(fontPath).get();

    richText.setFont(font);
    richText.setPosition(transform.position.x + 5, transform.position.y);

    switch(fontSize)
    {
    case FontSize::Tiny:
        richText.setCharacterSize(15);
        break;
    case FontSize::Small:
        richText.setCharacterSize(17);
        break;
    case FontSize::Medium:
        richText.setCharacterSize(19);
        break;
    case FontSize::Large:
        richText.setCharacterSize(21);
        break;
    case FontSize::Big:
        richText.setCharacterSize(23);
        break;
    }

    richText << textColor.ToSFMLColor();

    cursor.setSize(sf::Vector2f(2, richText.getCharacterSize()));
    cursor.setFillColor(cursorColor.ToSFMLColor());

    calculateMaxCharacters();
    updateRoundedBox();
    updateCursor();
}

void TextInput::EventManager(sf::Event& event)
{
    Vector2 mousePos = Alce.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(Alce.GetWindow()));

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            SetFocus(true);
        }
        else
        {
            SetFocus(false);
        }
    }

    if (getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        sf::Cursor cursor;
        if (cursor.loadFromSystem(sf::Cursor::Text)) Alce.GetWindow().setMouseCursor(cursor);
    }
    else
    {
        sf::Cursor cursor;
        if (cursor.loadFromSystem(sf::Cursor::Arrow)) Alce.GetWindow().setMouseCursor(cursor);
    }

    if (!focused) return;

    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == 8)
        {
            deleteCharacter();
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128)
        {
            insertText(event.text.unicode);
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Left: moveCursorLeft(); break;
            case sf::Keyboard::Right: moveCursorRight(); break;
            case sf::Keyboard::Home: moveCursorStart(); break;
            case sf::Keyboard::End: moveCursorEnd(); break;
            case sf::Keyboard::Enter: /*TODO: submit */ break;
            case sf::Keyboard::Delete: deleteCharacter(); break;
        }
    }

    updateCursor();
}

void TextInput::Render()
{
    if (borderRadius > 0)
    {
        Alce.GetWindow().draw(roundedBox);
    }
    else
    {
        Alce.GetWindow().draw(box);
    }

    richText.clear();

    if (inputText.Length() == 0 && !focused)
    {
        richText << placeholderColor.ToSFMLColor() << placeholder.ToSFMLString();
    }
    else
    {
        richText << textColor.ToSFMLColor() << inputText.ToSFMLString();
    }

    sf::FloatRect textBounds = richText.getLocalBounds();
    float textY = box.getPosition().y + (height - textBounds.height) / 2 - textBounds.top;
    richText.setPosition(richText.getPosition().x, textY);

    adjustTextPosition();

    Alce.GetWindow().draw(richText);

    toggleCursorVisibility();
    if (showCursor && focused)
    {
        Alce.GetWindow().draw(cursor);
    }
}

sf::FloatRect TextInput::getLocalBounds() const
{
    return box.getLocalBounds();
}

sf::FloatRect TextInput::getGlobalBounds() const
{
    return box.getGlobalBounds();
}

void TextInput::updateRoundedBox()
{
    if (borderRadius > 0)
    {
        roundedBox.setPointCount(8);
        roundedBox.setPoint(0, sf::Vector2f(borderRadius, 0));
        roundedBox.setPoint(1, sf::Vector2f(width - borderRadius, 0));
        roundedBox.setPoint(2, sf::Vector2f(width, borderRadius));
        roundedBox.setPoint(3, sf::Vector2f(width, height - borderRadius));
        roundedBox.setPoint(4, sf::Vector2f(width - borderRadius, height));
        roundedBox.setPoint(5, sf::Vector2f(borderRadius, height));
        roundedBox.setPoint(6, sf::Vector2f(0, height - borderRadius));
        roundedBox.setPoint(7, sf::Vector2f(0, borderRadius));
        roundedBox.setPosition(box.getPosition());
        roundedBox.setFillColor(backgroundColor.ToSFMLColor());
        roundedBox.setOutlineThickness(borderWidth);
        roundedBox.setOutlineColor(outlineColor.ToSFMLColor());
    }
}

void TextInput::calculateMaxCharacters()
{
    unsigned int fs = fontSize == FontSize::Tiny ? 15 :
                      fontSize == FontSize::Small ? 17 :
                      fontSize == FontSize::Medium ? 19 :
                      fontSize == FontSize::Large ? 21 :
                      fontSize == FontSize::Big ? 23 : 19;

    sfe::RichText tempRichText;
    tempRichText.setFont(font);
    tempRichText.setCharacterSize(fs);
    tempRichText << sf::String("A");

    float charWidth = tempRichText.getLocalBounds().width;

    if(fs < 20)
    {
        charWidth -= 1;
    }

    float availableWidth = width - 10;

    maxCharacters = static_cast<unsigned int>(availableWidth / charWidth);
}

void TextInput::setPosition(float x, float y)
{
    box.setPosition(sf::Vector2f(x, y));
    richText.setPosition(x + 5, y);
    updateRoundedBox();
}

void TextInput::adjustTextPosition()
{
    textOffset = 0;
    richText.setPosition(box.getPosition().x + 5, richText.getPosition().y);
    updateCursor();
}

void TextInput::toggleCursorVisibility()
{
    if (clock.getElapsedTime().asSeconds() >= 0.5f)
    {
        showCursor = !showCursor;
        clock.restart();
    }
}

void TextInput::updateCursor()
{
    sf::Vector2f textPos = richText.getPosition();
    if (cursorPosition == 0)
    {
        unsigned int fs = fontSize == FontSize::Tiny ? 15 :
                    fontSize == FontSize::Small ? 17 :
                    fontSize == FontSize::Medium ? 19 :
                    fontSize == FontSize::Large ? 21 :
                    fontSize == FontSize::Big ? 23 : 19;

        sfe::RichText tempRichText;
        tempRichText.setFont(font);
        tempRichText.setCharacterSize(fs);
        tempRichText << sf::String("A");

        float charHeight = tempRichText.getLocalBounds().height;
        cursor.setPosition(textPos.x - textOffset, textPos.y - (charHeight / 2));
    }
    else if (cursorPosition <= inputText.Length())
    {
        sf::String displayText = inputText.ToSFMLString().substring(0, cursorPosition);
        sf::Text tempText(displayText, font, richText.getCharacterSize());
        float cursorX = tempText.findCharacterPos(displayText.getSize()).x;
        cursor.setPosition(textPos.x + cursorX, textPos.y);
    }
    else
    {
        sf::FloatRect bounds = richText.getGlobalBounds();
        cursor.setPosition(textPos.x + bounds.width, textPos.y);
    }
    cursor.setSize(sf::Vector2f(2, richText.getCharacterSize()));
}

void TextInput::insertText(const sf::String& text)
{
    if (inputText.Length() + text.getSize() <= maxCharacters)
    {
        inputText.Insert(cursorPosition, alce::String(text));
        cursorPosition += text.getSize();
        richText << inputText.ToSFMLString();
        adjustTextPosition();
        updateCursor();
    }
}

void TextInput::deleteCharacter()
{
    if (cursorPosition > 0)
    {
        inputText.Cut(cursorPosition - 1, cursorPosition - 1);
        cursorPosition--;
        richText << inputText.ToSFMLString();
        updateCursor();
    }
}

void TextInput::moveCursorLeft()
{
    if (cursorPosition > 0)
    {
        cursorPosition--;
        updateCursor();
    }
}

void TextInput::moveCursorRight()
{
    if (cursorPosition < inputText.Length())
    {
        cursorPosition++;
        updateCursor();
    }
}

void TextInput::moveCursorStart()
{
    cursorPosition = 0;
    updateCursor();
}

void TextInput::moveCursorEnd()
{
    cursorPosition = inputText.Length();
    updateCursor();
}

