#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "renderer.h"
#include "../model/field.h"


namespace Graphics {

    class Drawer {
    public:
        Drawer(Model::Field &field_ref_,
               sf::Color outline_color_,
               const std::string &LIVES_IMG_PATH,
               const std::string &SCORES_IMG_PATH);

        void Update();
        void Close();
        void RenderField();
        void RenderCell(int x, int y);
        void RenderPlayer();
        bool PollEvent(sf::Event &event);
        bool IsOpen() const;

    private:
        static void InitSprite(const std::string &texture_path,
                                sf::Texture &texture, sf::Sprite &sprite,
                                float xscale, float yscale);

        Model::Field &field_ref;
        sf::RenderWindow window;
        Renderer renderer;
        sf::Color outline_color;

        sf::Texture heart_texture;
        sf::Texture score_texture;
        sf::Sprite heart_sprite;
        sf::Sprite score_sprite;
    };

}