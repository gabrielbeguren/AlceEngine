#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class SpriteRenderer : public Component
    {
    public:

        SpriteRenderer();

        void Init();

        void Start();

        void Render();

        void Update();

        void AddTexture(String file, String name);

        void SetTexture(String name);

        void RemoveTexture(String name);

        void SetTextureSmooth(String name, bool flag = true);

        Vector2 originOffset = Vector2(0.0f, 0.0f);

        Vector2 GetLocalCenter();

        Vector2 GetGlobalCenter();

        Dictionary<String, Vector2Ptr> GetCardinals();

    private:

        Vector2 localCenter;
        Vector2 globarCenter;

        String currentTexture = "";
        std::unique_ptr<sf::Sprite> sprite;
        Dictionary<String, TexturePtr> textures;
        Dictionary<String, Vector2Ptr> cardinals;
    };

    typedef std::shared_ptr<SpriteRenderer> SpriteRendererPtr;
}