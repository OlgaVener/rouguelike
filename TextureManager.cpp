#include "TextureManager.h"

sf::Texture& TextureManager::get(const std::string& name) {
    auto it = textures_.find(name);
    if (it == textures_.end()) {
        // ������ ��������-�������� ��� ������ ���������
        sf::Texture texture;
        texture.create(32, 32); // ׸���� ������� 32x32
        textures_[name] = texture;
    }
    return textures_[name];
}

void TextureManager::load(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    textures_[name] = texture;
}