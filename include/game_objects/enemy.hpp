#pragma once

#include <utility>

#include "player.h"
#include "../common.h"
#include "../lib/my_container.hpp"
#include "../lib/serialize.hpp"
#include "behavior_types.hpp"


namespace GameObject {

    class IEnemy : public Lib::ISerializable {
    public:
        explicit IEnemy(int strength_, int x_, int y_)
                : strength(strength_), x(x_), y(y_) {}

        virtual void operator+(Player &player) const = 0;

        virtual void Move() = 0;

        int X() const { return x; }

        int Y() const { return y; }

        int Strength() const { return strength; }

        void SetX(int x_) { x = x_; }

        void SetY(int y_) { y = y_; }

    protected:
        int x;
        int y;
        int strength;
    };


    template<typename Moving, typename Attacking>
    class StandardEnemy : public IEnemy {
    public:
        explicit StandardEnemy(int strength_, int x_, int y_)
                : IEnemy(strength_, x_, y_) {}

        void operator+(Player &player) const override {
            Attacking::Attack(strength, player);
        }

        template <typename T, typename U>
        bool operator==(const StandardEnemy<T, U>& other) const {
            return Moving::behavior_id == T::behavior_id
                    && Attacking::behavior_id == U::behavior_id;
        }

        void Move() override {
            moving_strategy.Move(x, y);
        }

        void SetMovingBorders(const std::pair<int, int>& borders,
                              const Lib::Container<Common::Position>& obstacles) {
            moving_strategy.x_right_border = borders.first;
            moving_strategy.y_down_border = borders.second;
            moving_strategy.obstacles_cords = obstacles;
        }

        void Write(Lib::OutRFile& out) const override {
            Lib::Write(out, x);
            Lib::Write(out, y);
            Lib::Write(out, strength);

            // Записываем айди класса-поведения для движения
            Lib::Write(out, Moving::behavior_id);
            // Записываем левые и правые границы
            Lib::Write(out, moving_strategy.x_right_border);
            Lib::Write(out, moving_strategy.y_down_border);
            Lib::Write(out, moving_strategy.obstacles_cords);

            // Записываем айди класса-поведения для атаки
            Lib::Write(out, Attacking::behavior_id);
        }

        const ISerializable& Read(Lib::InRFile& in) override {
            throw Lib::SerializeReadError("StandardEnemy is not readable with it's Read method. Use ReadEnemy.");
        }

    private:
        Moving moving_strategy;
    };

    inline std::shared_ptr<IEnemy> ReadEnemy(Lib::InRFile& in) {
        using namespace Behavior;

        int x = Lib::Read<int>(in);
        if (x < 0) {
            throw Lib::SerializeReadError("enemy's x coordinate cannot be negative");
        }

        int y = Lib::Read<int>(in);
        if (y < 0) {
            throw Lib::SerializeReadError("enemy's y coordinate cannot be negative");
        }

        int strength = Lib::Read<int>(in);
        if (strength < 0) {
            throw Lib::SerializeReadError("enemy's strength cannot be negative");
        }

        uint8_t moving_id = Lib::Read<uint8_t>(in);

        int x_right_border = Lib::Read<int>(in);
        int y_down_border = Lib::Read<int>(in);
        auto obstacles_cords = Lib::Read<Lib::Container<Common::Position>>(in);

        uint8_t attacking_id = Lib::Read<uint8_t>(in);

        // RandomMove
        if (moving_id == 0) {
            if (attacking_id == 0) {
                auto read_enemy = std::make_shared<StandardEnemy<RandomMove, InstantAttack>>(strength, x, y);
                read_enemy->SetMovingBorders({x_right_border, y_down_border}, obstacles_cords);
                return read_enemy;
            }
            else if (attacking_id == 1) {
                auto read_enemy = std::make_shared<StandardEnemy<RandomMove, PoisonBuffAttack>>(strength, x, y);
                read_enemy->SetMovingBorders({x_right_border, y_down_border}, obstacles_cords);
                return read_enemy;
            }
            else {
                throw Lib::SerializeReadError("unknown attacking id: " + std::to_string(attacking_id));
            }
        }

        throw Lib::SerializeReadError("unknown moving id: " + std::to_string(moving_id));
    }

}