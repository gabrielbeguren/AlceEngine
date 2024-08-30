#include "Button.hpp"

using namespace alce;

void Button::Init()
{

}

void Button::Start()
{

}

void Button::Update()
{
    Vector2 size = Vector2(richText.getLocalBounds().width, richText.getLocalBounds().height) + (padding * 2);

    box.setPosition(transform.position.x, transform.position.y);
    box.setSize(size.ToVector2f());

    if(isMouseOver)
    {
        if (isMousePressed)
        {
            box.setFillColor(onClickBackgroundColor.ToSFMLColor());
        }
        else
        {
            box.setFillColor(mouseOverBackgroundColor.ToSFMLColor());
        }
    }
    else
    {
        box.setFillColor(backgroundColor.ToSFMLColor());
    }

    font = *Alce.GetFont(fontPath).get();

    richText.setFont(font);
    richText.setCharacterSize(fontSize);

    sf::FloatRect textBounds = richText.getLocalBounds();
    Vector2 textPos = Vector2(
        transform.position.x + (size.x - textBounds.width) / 2 - textBounds.left,
        transform.position.y + (size.y - textBounds.height) / 2 - textBounds.top
    );

    richText.setPosition(textPos.ToVector2f());
    richText.setCharacterSize(fontSize);

    if (borderRadius > 0)
    {
        roundedBox.setPointCount(8);
        roundedBox.setPoint(0, sf::Vector2f(borderRadius, 0));
        roundedBox.setPoint(1, sf::Vector2f(size.x - borderRadius, 0));
        roundedBox.setPoint(2, sf::Vector2f(size.x, borderRadius));
        roundedBox.setPoint(3, sf::Vector2f(size.x, size.y - borderRadius));
        roundedBox.setPoint(4, sf::Vector2f(size.x - borderRadius, size.y));
        roundedBox.setPoint(5, sf::Vector2f(borderRadius, size.y));
        roundedBox.setPoint(6, sf::Vector2f(0, size.y - borderRadius));
        roundedBox.setPoint(7, sf::Vector2f(0, borderRadius));
        roundedBox.setPosition(box.getPosition());

        if(isMouseOver)
        {
            if (isMousePressed)
            {
                roundedBox.setFillColor(onClickBackgroundColor.ToSFMLColor());
            }
            else
            {
                roundedBox.setFillColor(mouseOverBackgroundColor.ToSFMLColor());
            }
        }
        else
        {
            roundedBox.setFillColor(backgroundColor.ToSFMLColor());
        }

        roundedBox.setOutlineThickness(borderWidth);
        roundedBox.setOutlineColor(borderColor.ToSFMLColor());
    }
    else
    {
        box.setOutlineThickness(borderWidth);
        box.setOutlineColor(borderColor.ToSFMLColor());
    }
}

void Button::Render()
{
    if(borderRadius > 0)
    {
        Alce.GetWindow().draw(roundedBox);
    }
    else
    {   
        Alce.GetWindow().draw(box);
    }

    richText.clear();
    richText << (isMouseOver ? mouseOverTextColor.ToSFMLColor() : textColor.ToSFMLColor()) << text.ToSFMLString();
    Alce.GetWindow().draw(richText);
}

void Button::EventManager(sf::Event& event)
{
    Vector2 mousePos = Alce.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(Alce.GetWindow()));
    isMouseOver = box.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if(isMouseOver)
    {
        sf::Cursor cursor;

        //TODO: La carga del tipo de cursor no funciona bien
        if (cursor.loadFromSystem(sf::Cursor::Hand)) Alce.GetWindow().setMouseCursor(cursor);
        else Debug.Warning("Failed to load system cursor.");

        if (!prevMouseOver && onMouseEnter)
        {
            onMouseEnter();  
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            isOnClick = true;
            isMousePressed = true;
            if(onClick)
            {
                onClick();
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            isMousePressed = false;
        }
    }
    else
    {
        sf::Cursor cursor;
        if (cursor.loadFromSystem(sf::Cursor::Arrow)) Alce.GetWindow().setMouseCursor(cursor);

        if (prevMouseOver && onMouseOut)
        {
            onMouseOut();  
        }

        isOnClick = false;
        isMousePressed = false;
    }

    prevMouseOver = isMouseOver; 
}