#include <iostream>
#include <QApplication>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include <graphics/draw.h>
#include <logging/file_logger.hpp>

#include <controller/field_controller.h>
#include <logging/field_logger.h>
#include <game_objects/wandering_enemy.h>
#include <controller/states.h>

constexpr int ROWS = 10;
constexpr int COLUMNS = 10;
constexpr int SIZE = 80;

int main(int argc, char* argv[]) {
    using namespace Lib;
    using namespace Logging;
    using namespace Graphics;
    using namespace GameObject;
    using namespace Model;

    QApplication a(argc, argv);

    auto& field_model = Field::GetField(ROWS, COLUMNS, SIZE);
    field_model.AddNPC(std::make_shared<WanderingEnemy>(Common::Position{3, 3}, 1));
    field_model.AddNPC(std::make_shared<WanderingEnemy>(Common::Position{9, 9}, 1));
    field_model.AddNPC(std::make_shared<WanderingEnemy>(Common::Position{2, 0}, 1));

    auto field_view = std::make_shared<Drawer>(field_model, sf::Color::Black);

    // Listeners
    auto logger = std::make_shared<FieldLogger>(
        field_model, std::make_unique<FileLogger>("logfile.txt")
    );
    field_model.AddListener(std::move(logger));

    // GAME LOOP
    std::vector<std::shared_ptr<States::ControllerState>> states;
    states.push_back(std::make_shared<States::PlayerTurn>(field_model, field_view));
    states.push_back(std::make_shared<States::EnemyTurn>(field_model));

    Controller::FieldController field_controller(states[0]);
    int current_state = 1;

    while (field_controller.Run()) {
        field_controller.SetState(states[current_state]);
        current_state = (current_state + 1) % 2;
    }


    return 0;
}