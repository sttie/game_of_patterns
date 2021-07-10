#include <graphics/draw.h>
#include <graphics/sprites_paths.h>

#include <iostream>


using namespace std;
using namespace Graphics;

Drawer::Drawer(Model::Field& field_ref_, sf::Color outline_color_)
    : field_ref(field_ref_)
    , window(sf::VideoMode(field_ref.CellSize() * field_ref.Rows(),
                           field_ref.CellSize() * field_ref.Columns()),
                           "Game field")
    , renderer(window)
    , outline_color(outline_color_)
    , hero_draw_info(PLAYER_SPRITE_PATH, 0.11, 0.135)
    , enemy_draw_info(WANDERING_ENEMY_PATH, 0.11, 0.105)
    , lives_draw_info(HEART_SPRITE_PATH, 0.155, 0.155)
    , score_draw_info(SCORE_SPRITE_PATH, 0.025, 0.025)
    , portal_draw_info(PORTAL_SPRITE_PATH, 0.12, 0.123)
{
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
    renderer.DrawGrid(field_ref.Rows(), field_ref.Columns(),
                      field_ref.CellSize(), outline_color);

    for (size_t i = 0; i < field_ref.Rows(); i++)
        for (size_t j = 0; j < field_ref.Columns(); j++ )
            RenderCell(i, j);
    RenderPlayer();
}

void Drawer::RenderCell(int x, int y) {
    size_t cell_size = field_ref.CellSize();
    
    if (field_ref.IsObstacle(x, y)) {
        renderer.ColorCell(x, y, field_ref.CellSize(), sf::Color::Black);
    }
    else if (field_ref.IsExit(x, y)) {
        renderer.ColorCell(x, y, field_ref.CellSize(), sf::Color::Blue);
    }
    else if (field_ref.IsLivesUp(x, y)) {
        renderer.DrawSprite(lives_draw_info.sprite, 
                            x * cell_size + cell_size / 3.9,
                            y * cell_size + cell_size / 3.9);
    }
    else if (field_ref.IsScoresUp(x, y)) {
        renderer.DrawSprite(score_draw_info.sprite,
                            x * cell_size + cell_size / 3.7,
                            y * cell_size + cell_size / 5.2);
    }
    else if (field_ref.IsPortal(x, y)) {
        renderer.DrawSprite(portal_draw_info.sprite, x * cell_size, y * cell_size);
    }

    if (field_ref.IsNPC(x, y)) {
        renderer.DrawSprite(enemy_draw_info.sprite,
                            x * cell_size + cell_size / 5,
                            y * cell_size + cell_size / 12);
    }
}

void Drawer::RenderPlayer() {
    size_t cell_size = field_ref.CellSize();
    renderer.DrawSprite(hero_draw_info.sprite, cell_size * field_ref.PlayerX(), cell_size * field_ref.PlayerY());
}

bool Drawer::IsOpen() const {
    return window.isOpen();
}

bool Drawer::PollEvent(sf::Event& event) {
    return window.pollEvent(event);
}