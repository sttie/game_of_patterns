#include <iostream>
#include <QApplication>
#include <SFML/Graphics.hpp>
#include <memory>

#include "include/graphics/draw.h"
#include "include/logging/file_logger.hpp"
#include "include/lib/my_container.hpp"


#include "include/lib/unit_testing.hpp"

#include "include/controller/field_controller.h"
#include "include/logging/field_logger.h"
#include "include/game_objects/behavior_types.hpp"
#include "include/game_objects/enemy.hpp"
#include "include/controller/states.h"

constexpr int ROWS = 10;
constexpr int COLUMNS = 10;
constexpr int SIZE = 80;


int main(int argc, char* argv[]) {
    using namespace std;
    using namespace Lib;
    using namespace Logging;
    using namespace Graphics;
    using namespace GameObject;
    using namespace Model;

    QApplication a(argc, argv);


    auto field_model = Field::GetField(ROWS, COLUMNS, SIZE);
    field_model.AddEnemy(make_shared
            <StandardEnemy<Behavior::RandomMove, Behavior::InstantAttack>
            >(1, 3, 3));
    field_model.AddEnemy(make_shared
            <StandardEnemy<Behavior::RandomMove, Behavior::InstantAttack>
            >(1, 9, 9));
    field_model.AddEnemy(make_shared
            <StandardEnemy<Behavior::RandomMove, Behavior::InstantAttack>
            >(1, 2, 0));


    auto field_view = make_shared<Drawer>(field_model, sf::Color::Black,
                                          "resources/heart.png",
                                          "resources/score_coin.png");

    // Listeners
    auto logger = make_shared<FieldLogger>(
        field_model, make_unique<FileLogger>("logfile.txt")
    );
    field_model.AddListener(move(logger));


    // GAME LOOP
    Container<shared_ptr<States::ControllerState>> states;
    states.PushBack(make_shared<States::PlayerTurn>(field_model, field_view));
    states.PushBack(make_shared<States::EnemyTurn>(field_model));

    Controller::FieldController field_controller(states[0]);
    int current_state = 1;

    while (field_controller.Run()) {
        field_controller.SetState(states[current_state]);
        current_state = (current_state + 1) % 2;
    }


    return 0;
}