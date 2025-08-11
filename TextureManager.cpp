#include "TextureManager.h"
#include <stdexcept>

std::map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::GetTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it == textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
           throw std::runtime_error("Failed to load texture: " + filename);
        }
        textures[filename] = texture;
        return textures[filename];
    }
    return it->second;
}