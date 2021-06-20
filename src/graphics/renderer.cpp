#include "../../include/graphics/renderer.h"

using namespace std;
using namespace Graphics;


Renderer::Renderer(sf::RenderWindow& window_)
    : window(window_)
{
}

void Renderer::ColorCell(int x, int y, int cell_size,
                         sf::Color cell_color) {
    sf::RectangleShape rect;
    rect.setPosition(cell_size * x, cell_size * y);
    rect.setSize(sf::Vector2f(cell_size, cell_size));
    rect.setOutlineColor(cell_color);
    rect.setFillColor(cell_color);
    rect.setOutlineThickness(1);
    window.draw(rect);
}


void Renderer::DrawGrid(int rows, int columns, int cell_size,
                        sf::Color outline_color) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(cell_size, cell_size));
            rect.setOutlineColor(outline_color);
            rect.setOutlineThickness(2);
            rect.setPosition(cell_size * i, cell_size * j);

            window.draw(rect);
        }
    }
}

void Renderer::DrawSprite(sf::Sprite& sprite, int x, int y) {
    sprite.setPosition(x, y);
    window.draw(sprite);
}