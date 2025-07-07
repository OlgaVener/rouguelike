#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    sf::Texture& get(const std::string& name);
    void load(const std::string& name, const std::string& filename);

private:
    std::unordered_map<std::string, sf::Texture> textures_;
};