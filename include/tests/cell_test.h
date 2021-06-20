#pragma once

#include "../lib/unit_testing.hpp"
#include "../game_objects/player.h"
#include "../model/cell.h"


// Здесь тестится взаимодействие игрока с клетками
void TestCells() {
    using namespace Model;

    GameObject::Player player;
    int scores = player.Scores();
    int lives = player.Lives();
    int x = player.X();
    int y = player.Y();

    Model::Cell scores_cell({x, y}, Cell::CellType::SCORES_UP);
    scores_cell.SetStrategy(Cell::CellType::SCORES_UP);

    Model::Cell lives_cell({x, y}, Cell::CellType::LIVES_UP);
    lives_cell.SetStrategy(Cell::CellType::LIVES_UP);

    Model::Cell portal_cell({x, y}, Cell::CellType::PORTAL);
    portal_cell.SetStrategy(Cell::CellType::PORTAL, 6, 4);

    // Здесь добавляется 50 очков
    player + scores_cell;
    ASSERT(player.Scores() == scores + 50);

    // Здесь добавляется 1 здоровье
    player + lives_cell;
    ASSERT(player.Lives() == lives + 1);

    // Телепортируемся в точку (6, 4)
    player + portal_cell;
    ASSERT(player.X() == 6 && player.Y() == 4);
}