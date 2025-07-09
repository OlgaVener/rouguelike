#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
public:
    static sf::Texture& GetTexture(const std::string& filename);
private:
    static std::map<std::string, sf::Texture> textures;
};