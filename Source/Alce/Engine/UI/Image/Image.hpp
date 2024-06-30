#pragma once

#include "../../Core/Core.hpp"

namespace alce
{
    class Image : public UIElement
    {
    public:

        Image() : UIElement("Image")
        {
            sprite = std::make_unique<sf::Sprite>();
        }

        void AddTexture(String file, String name);

        void SetTexture(String name);

        void RemoveTexture(String name);

        void SetTextureSmooth(String name, bool flag);

        void Init();

        void Start();

        void Update();

        void Render();

        void EventManager(sf::Event& event);

        Vector2 originOffset = Vector2(0.0f, 0.0f);

    private:

        Dictionary<String, TexturePtr> textures;
        std::unique_ptr<sf::Sprite> sprite;
        String currentTexture = "";

    };

    typedef std::shared_ptr<Image> ImagePtr;
}