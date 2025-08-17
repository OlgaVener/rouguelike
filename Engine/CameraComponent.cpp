#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h" 

namespace GameEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
	{
		view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
		transform = gameObject->GetComponent<TransformComponent>();
	}	

	CameraComponent::~CameraComponent()
	{
		delete view;
	}

	// Метод обновления камеры (вызывается каждый кадр)
	void CameraComponent::Update(float deltaTime)
	{
		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation();

		view->setCenter(sf::Vector2f(position.x, position.y));
		view->setRotation(rotation);

		window->setView(*view);
	}
	
	// Метод рендеринга (в текущей реализации только проверяет наличие окна)
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
		view->reset(sf::FloatRect(0, 0, width, -height));
	}

	// Привязка окна рендеринга к камере
	void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
	{
		window = newWindow;
	}

	// Метод масштабирования (зумирования) камеры
	void CameraComponent::ZoomBy(float newZoom)
	{
		if (newZoom <= 0)
		{
			std::cout << "Not allowed zoom lesser or equal than zero." << std::endl;
			return;
		}
		view->zoom(newZoom);
	}
}
