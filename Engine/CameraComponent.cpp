#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h" 

namespace GameEngine
{
    CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
    {
        // ПРАВИЛЬНОЕ создание view - центр и размер
        view = new sf::View(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));
        //transform = gameObject->GetComponent<TransformComponent>();
        window = nullptr;
    }

    CameraComponent::~CameraComponent()
    {
        delete view;
    }

    // Метод обновления камеры
    void CameraComponent::Update(float deltaTime)
    {
        if (!window) return;

        view->setCenter(640, 352); // Центр экрана 1280x720
        view->setSize(1280, 704);

        window->setView(*view);
    }

    void CameraComponent::Render()
    {
        if (window == nullptr)
        {
            std::cout << "NULL window render." << std::endl;
        }
    }

    // Установка базового разрешения камеры
    void CameraComponent::SetBaseResolution(int width, int height)
    {
        // УБИРАЕМ минус! Ось Y должна быть положительной
        view->reset(sf::FloatRect(0, 0, width, height));

        // Или лучше использовать setSize:
        view->setSize(width, height);
        view->setCenter(width / 2, height / 2);
    }

    void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
    {
        window = newWindow;
        if (window) {
            window->setView(*view); // Немедленно применяем view к окну
        }
    }

    void CameraComponent::ZoomBy(float newZoom)
    {
        if (newZoom <= 0)
        {
            std::cout << "Not allowed zoom lesser or equal than zero." << std::endl;
            return;
        }
        view->zoom(newZoom);
        if (window) {
            window->setView(*view); // Обновляем view после zoom
        }
    }
}