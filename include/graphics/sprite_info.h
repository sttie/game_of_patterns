#pragma once

#include <SFML/Graphics.hpp>
#include <string>

struct SpriteDrawInfo {
    SpriteDrawInfo(const std::string& path, float xscale, float yscale) {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
        sprite.setScale(xscale, yscale);
    }

    sf::Texture texture;
    sf::Sprite sprite;
};