#pragma once
#include "Engine/IPositionProvider.h"

class Enemy : public GameEngine::IPositionProvider {
public:
    sf::Vector2f position;

    sf::Vector2f getPosition() const override { return position; }
    void move(const sf::Vector2f& offset) { position += offset; }
};
