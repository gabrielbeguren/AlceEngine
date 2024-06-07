#pragma once

#include "../../Core/Core.hpp"

namespace alce
{
    class UIText : public UIElement, public String
    {
    public:
        
        UIText(): UIElement("UIText")
		{
			this->str = sf::String("");
		}

        UIText(const char* cstr) : UIElement("UIText")
		{
			this->str = sf::String(cstr);
		}

		UIText(const wchar_t* cstr) : UIElement("UIText")
		{
			this->str = sf::String(cstr);
		}

		UIText(std::wstring str) : UIElement("UIText")
		{
			this->str = sf::String(str);
		}

		UIText(std::string str) : UIElement("UIText")
		{
			this->str = sf::String(str);
		}

		UIText(sf::String str) : UIElement("UIText")
		{
			this->str = str;
		}

		UIText(size_t size) : UIElement("UIText")
		{
			this->str = sf::String(std::to_string(size));
		}

		UIText(bool boolean) : UIElement("UIText")
		{
			boolean ? this->str = sf::String("true") : this->str = sf::String("false");
		}

		UIText(int integer) : UIElement("UIText")
		{
			this->str = sf::String(std::to_string(integer));
		}

		UIText(long long_int) : UIElement("UIText")
		{
			this->str = sf::String(std::to_string(long_int));
		}

		UIText(double dec) : UIElement("UIText")
		{
			this->str = sf::String(std::to_string(dec));
		}

		UIText(float dec) : UIElement("UIText")
		{
			this->str = sf::String(std::to_string(dec));
		}

        void Init();

        void Start();

        void Render();

        void Update();

        Color color = Colors::White;

        sf::Text::Style style = sf::Text::Regular;

        unsigned int fontSize = 17;

        String font = "fonts/Basic-Regular/Basic-Regular.ttf";
        
    private:

        sfe::RichText richText;
    };

    typedef std::shared_ptr<UIText> UITextPtr; 
};

