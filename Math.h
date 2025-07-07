#pragma once
#include <memory>

class Platform;
class Ball;
class Brick;

namespace Math
{
	template <typename T>
	const T& clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	// === Коллизии ===
	// void checkCollisions();																						  // Общая проверка всех коллизий


																												// void checkBonusWithPlatformCollision();					// Коллизия бонусов с платформой
}  // namespace Math
