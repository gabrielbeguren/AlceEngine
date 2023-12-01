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

void Camera::SetSmoothFactor(float sf)
{
    if(sf < 0.f)
    {
        Debug.Warning("Smooth factor cannot be less than 0");
        return;
    }

    smoothFactor = sf;
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
    return Vector2(Kernel.GetWindowSize().x * viewport.width, Kernel.GetWindowSize().y * viewport.height);
}

#pragma endregion

#pragma region generic

void Camera::Init()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component Camera has no association with any GameObject");
        return;
    }

    view = sf::View(transform->position.ToPixels().ToVector2f(), size.ToVector2f());
}

void Camera::Update()
{
    size.x = Kernel.GetWindowSize().x * viewport.width;
    size.y = Kernel.GetWindowSize().y * viewport.height;

    size *= zoom;

    sf::Vector2f targetCenter = transform->position.ToPixels().ToVector2f();

    sf::Vector2f displacement = (targetCenter - view.getCenter()) * smoothFactor;
    sf::Vector2f newPosition = view.getCenter() + displacement;

    view.setCenter(newPosition);

    view.setSize(size.ToVector2f());
    view.setRotation(transform->rotation);
    view.setViewport(viewport.ToFloatRect());
}

#pragma endregion