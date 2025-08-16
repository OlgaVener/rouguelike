#pragma once
#include "Component.h"
#include "GameObject.h"
#include <CameraComponent.h>
#include <Logger.h>

namespace GameEngine
{
	class StatsComponent : public Component
	{
	public:
		StatsComponent(GameObject* gameObject, float health, float armor)
			: Component(gameObject), maxHealth(health), currentHealth(health), armor(armor)
		{}

		float GetCurrentHealth() const { return currentHealth; }
		float GetMaxHealth() const { return maxHealth; }
		float GetArmor() const { return armor; }

		void TakeDamage(float damage)
		{
			damage -= armor;
			if (damage < 0)
			{
				damage = 0;
			}
			armor -= 1;

			if (armor < 0)
			{
				armor = 0;
				LOG_INFO("The armor was broken");
			}

			currentHealth -= damage;

			if (currentHealth < 0)
			{
				currentHealth = 0;
			}

			LOG_INFO("Took " + std::to_string((float)damage) + " damage, current health: " + std::to_string((float)GetCurrentHealth()));
		}

		void Heal(float amount)
		{
			currentHealth += amount;

			if (currentHealth > maxHealth)
			{
				currentHealth = maxHealth;
			}

			LOG_INFO("Healed " + std::to_string((float)amount) + " health, current health: " + std::to_string((float)GetCurrentHealth()));
		}

	private:
		float maxHealth;
		float currentHealth;
		float armor;
	};
}
