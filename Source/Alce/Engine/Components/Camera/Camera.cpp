#include "Camera.hpp"

using namespace alce;

Camera::Camera() : Component("camera")
{

}

#pragma region implementation

void Camera::Zoom(float zoom)
{
    if(zoom < 0)
    {
        Debug.Warning("Zoom value cannot be less than 0");
        return;
    }

    this->zoom = zoom;
}

RectShape Camera::GetViewport()
{
    return viewport;
}

void Camera::SetViewport(RectShape viewport)
{
    this->viewport = viewport;
}

float Camera::GetZoom()
{
    return zoom;
}

RectShape Camera::GetBounds()
{
    Vector2 pixelSize = this->GetSize();

    Vector2 pos = transform->position.ToPixels();
    pos.x -= GetSize().x / 2.0f;
    pos.y -= GetSize().y / 2.0f;

    return RectShape(pos.x, pos.y, pixelSize.x, pixelSize.y);
}

Vector2 Camera::GetSize()
{
    return Vector2(Alce.GetWindowSize().x * viewport.width, Alce.GetWindowSize().y * viewport.height);
}

#pragma endregion

#pragma region inherited

void Camera::Init()
{
    if (transform == nullptr)
    {
        Debug.Warning("Component Camera has no association with any GameObject");
        return;
    }

    sf::Vector2f initialCenter = transform->position.ToPixels().ToVector2f();
    view = sf::View(initialCenter, size.ToVector2f());
}


void Camera::Update()
{
    size.x = Alce.GetWindowSize().x * viewport.width;
    size.y = Alce.GetWindowSize().y * viewport.height;

    size *= zoom;

    sf::Vector2f targetCenter = transform->position.ToPixels().ToVector2f();
    sf::Vector2f currentCenter = view.getCenter();

    sf::Vector2f smoothedCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor;

    view.setCenter(smoothedCenter);
    view.setSize(size.ToVector2f());
    view.setRotation(transform->rotation);
    view.setViewport(viewport.ToFloatRect());
}


#pragma endregion