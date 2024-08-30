#pragma once

#include "../../Core/Core.hpp"

namespace alce
{
    class Camera : public Component
    {
    public:

        Camera();

        void Zoom(float zoom);

        RectShape GetViewport();

        void SetViewport(RectShape viewport);

        float GetZoom();

        RectShape GetBounds();

        Vector2 GetSize();

        void Init();

        void Update();

        float smoothFactor = 1.0f;

    private:

        friend class Scene;

        Vector2 size;
        sf::View view;
        RectShape viewport = RectShape(Vector2(0.0f, 0.0f), 1, 1);

        float zoom = 1.0f;
    };

    typedef std::shared_ptr<Camera> CameraPtr;
}