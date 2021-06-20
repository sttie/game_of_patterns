#pragma once

#include "../commands/moves.hpp"
#include "../model/field.h"
#include "../lib/unit_testing.hpp"


void TestMoves() {
    auto field = Model::Field::GetField(10, 10, 80);

    Commands::MoveUp up(field);
    Commands::MoveRight right(field);
    Commands::MoveDown down(field);
    Commands::MoveLeft left(field);

    int player_x = field.PlayerX();
    int player_y = field.PlayerY();

    up.Execute();
    right.Execute();
    down.Execute();
    left.Execute();

    ASSERT(player_x == field.PlayerX() && player_y == field.PlayerY());

    Model::Field::ClearField();
}