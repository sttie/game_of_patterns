#include "../../include/graphics/draw.h"

#include <iostream>

using namespace std;
using namespace Graphics;

Drawer::Drawer(Model::Field& field_ref_,
               sf::Color outline_color_,
               const std::string& LIVES_IMG_PATH,
               const std::string& SCORES_IMG_PATH)
    : field_ref(field_ref_)
    , window(sf::VideoMode(field_ref.CellSize() * field_ref.Rows(),
                           field_ref.CellSize() * field_ref.Columns()),
                           "Game field")
    , renderer(window)
    , outline_color(outline_color_)
{
    InitSprite(LIVES_IMG_PATH, heart_texture, heart_sprite, 0.085, 0.12);
    InitSprite(SCORES_IMG_PATH, score_texture, score_sprite, 0.094, 0.12);
}


void Drawer::InitSprite(const std::string& texture_path,
                        sf::Texture& texture, sf::Sprite& sprite,
                        float xscale, float yscale) {
    texture.loadFromFile(texture_path);
    sprite.setTexture(texture);
    sprite.setScale(xscale, yscale);
}

void Drawer::Update() {
    window.clear();
    RenderField();
    window.display();
}

void Drawer::Close() {
    window.close();
}

void Drawer::RenderField() {
    renderer.DrawGrid(field_ref.Rows(),
                      field_ref.Columns(),
                      field_ref.CellSize(),
                      outline_color);

    for (size_t i = 0; i < field_ref.Rows(); i++) {
        for (size_t j = 0; j < field_ref.Columns(); j++ ) {
            RenderCell(i, j);
        }
    }

    RenderPlayer();
}

void Drawer::RenderCell(int x, int y) {
    if (field_ref.IsObstacle(x, y)) {
        renderer.ColorCell(x, y, field_ref.CellSize(), sf::Color::Black);
    }
    else if (field_ref.IsExit(x, y)) {
        renderer.ColorCell(x, y, field_ref.CellSize(), sf::Color::Blue);
    }
    else if (field_ref.IsEnter(x, y)) {
        renderer.ColorCell(x, y, field_ref.CellSize(), sf::Color::Green);
    }
    else if (field_ref.IsLivesUp(x, y)) {
        renderer.DrawSprite(heart_sprite, x * field_ref.CellSize(), y * field_ref.CellSize());
    }
    else if (field_ref.IsScoresUp(x, y)) {
        renderer.DrawSprite(score_sprite, x * field_ref.CellSize(), y * field_ref.CellSize());
    }
    else if (field_ref.IsPortal(x, y)) {
        renderer.ColorCell(x, y, field_ref.CellSize(), sf::Color::Magenta);
    }

    if (field_ref.IsEnemy(x, y)) {
        size_t cell_size = field_ref.CellSize();
        sf::CircleShape circle(cell_size / 2 - 10);
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineColor(sf::Color(225, 225, 0, 255));
        circle.setOutlineThickness(5);
        circle.setPosition(cell_size * x + 10, cell_size * y + 10);

        window.draw(circle);
    }
}

void Drawer::RenderPlayer() {
    size_t cell_size = field_ref.CellSize();
    sf::CircleShape circle(cell_size / 2 - 10);
    circle.setFillColor(sf::Color::Black);
    circle.setOutlineColor(sf::Color(224, 160, 37, 255));
    circle.setOutlineThickness(5);
    circle.setPosition(cell_size * field_ref.PlayerX() + 10, cell_size * field_ref.PlayerY() + 10);

    window.draw(circle);
}

bool Drawer::IsOpen() const {
    return window.isOpen();
}

bool Drawer::PollEvent(sf::Event& event) {
    return window.pollEvent(event);
}