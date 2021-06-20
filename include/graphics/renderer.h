#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>


namespace Graphics {

    class Renderer {
    public:
        Renderer(sf::RenderWindow &window_);

        void ColorCell(int x, int y, int cell_size,
                       sf::Color cell_color);

        void DrawGrid(int rows, int columns, int cell_size,
                      sf::Color outline_color);

        void DrawSprite(sf::Sprite &sprite, int x, int y);

    private:
        sf::RenderWindow &window;
    };

}