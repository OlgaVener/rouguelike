#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Component.h"
#include "TransformComponent.h"

namespace Engine
{
    class GameObject; 

    class CameraComponent : public Component
    {
    public:
        CameraComponent(GameObject* gameObject);
        ~CameraComponent();

        void Update(float deltaTime) override;
        void Render() override;

        void SetWindow(sf::RenderWindow* newWindow);
        void ZoomBy(float newZoom);
        void SetBaseResolution(int width, int height);

    private:
        TransformComponent* transform;
        sf::RenderWindow* window;
        sf::View* view;
    };
}