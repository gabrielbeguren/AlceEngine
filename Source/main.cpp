#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    // Kernel.Window("Alce Engine Test", DisplayMode::Default);
    // Kernel.stanby = true;

    // Kernel.AddScene<test::TestScene>();
    // Kernel.SetCurrentScene("test");

    // Kernel.Run();

    // return 0;

    //------------------------------------------------------------------------

    sf::RenderWindow window(sf::VideoMode(400, 400), "test-candle");

    candle::RadialLight light;
    light.setRange(-100);
    light.setFade(true);
    light.setPosition(sf::Vector2f(100, 100));

    candle::LightingArea fog(candle::LightingArea::FOG, sf::Vector2f(0, 0), sf::Vector2f(400, 400));
    fog.setAreaColor(sf::Color::Black);

    sf::Texture texture;
    if(!texture.loadFromFile("Assets/alce.png"))
    {
        exit(1);
    }

    sf::Sprite background(texture);

    while(window.isOpen())
    {
        sf::Event e;

        while(window.pollEvent(e)) 
        {
            if(e.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(e.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mp(sf::Mouse::getPosition(window));
                light.setPosition(mp);
            }
        }

        fog.clear();
        fog.draw(light);
        fog.display();
        
        window.clear();
        window.draw(background);
        window.draw(fog);
        window.draw(light);
        window.display();
    }

    return 0;
}
