#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include <graphics/renderer.h>
#include <graphics/sprite_info.h>
#include <model/field.h>


namespace Graphics {

    class Drawer {
    public:
        Drawer(Model::Field &field_ref_, sf::Color outline_color_);

        void Update();
        void Close();
        void RenderField();
        void RenderCell(int x, int y);
        void RenderPlayer();
        bool PollEvent(sf::Event &event);
        bool IsOpen() const;

    private:
        Model::Field &field_ref;
        sf::RenderWindow window;
        Renderer renderer;
        sf::Color outline_color;

        SpriteDrawInfo hero_draw_info;
        SpriteDrawInfo enemy_draw_info;
        SpriteDrawInfo lives_draw_info;
        SpriteDrawInfo score_draw_info;
        SpriteDrawInfo portal_draw_info;
    };

}