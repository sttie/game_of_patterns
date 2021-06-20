#pragma once

#include <random>

#include "../lib/my_container.hpp"
#include "player.h"
#include "buffs.h"
#include "../common.h"


namespace GameObject::Behavior {

        struct RandomMove {
            int x_right_border;
            int y_down_border;
            Lib::Container<Common::Position> obstacles_cords;
            static constexpr uint8_t behavior_id = 0;

            std::random_device rdevice;
            std::mt19937 rand{rdevice()};

            void Move(int &x, int &y) {
                const Lib::Container<int> directions({-1, 0, 1});

                int x_index = rand() % 3;
                while (x + directions[x_index] < 0 || x + directions[x_index] >= x_right_border
                       || IsObstacle({x + directions[x_index], y})) {
                    x_index = rand() % 3;
                }
                x += directions[x_index];

                int y_index = rand() % 3;
                while (y + directions[y_index] < 0 || y + directions[y_index] >= y_down_border
                       || IsObstacle({x, y + directions[y_index]})) {
                    y_index = rand() % 3;
                }
                y += directions[y_index];
            }

        private:
            bool IsObstacle(const Common::Position &pos) const {
                for (const auto &obstacle : obstacles_cords) {
                    if (obstacle == pos)
                        return true;
                }
                return false;
            }
        };


        struct InstantAttack {
            static constexpr uint8_t behavior_id = 0;
            static void Attack(int skill, Player &player) {
                if (skill < 0)
                    throw std::logic_error("skill cannot be negative");

                player.SetLives(player.Lives() - skill);
            }
        };

        struct PoisonBuffAttack {
            static constexpr uint8_t behavior_id = 1;
            static void Attack(int skill, Player &player) {
                player.SetBuff(std::make_shared<PoisonBuff>(skill * 2, skill));
            }
        };

    }