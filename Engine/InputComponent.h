#pragma once

#include "Component.h"
#include <SFML/Window.hpp>

namespace GameEngine
{
	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void Update(float deltatime) override;
		void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;
	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;
	};
}
