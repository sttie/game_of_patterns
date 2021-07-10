#pragma once

#include <utility>

#include <game_objects/player.h>
#include <common.h>
#include <lib/serialize.hpp>


namespace GameObject {

    class NPC : public Lib::ISerializable {
    public:
        NPC(const Common::Position& position);
        NPC(int x, int y);

        // TODO: убрать заглушку
        void Write(Lib::OutRFile& out) const {}
        const ISerializable& Read(Lib::InRFile& in) { return *this; }

        virtual void InteractWithPlayer(Player& player) const = 0;
        virtual Common::Position Move() const = 0;

        // const std::string& SpritePath() const;
        int X() const;
        int Y() const;

        void SetPosition(const Common::Position& pos);

    protected:
        Common::Position position;
    };


    // template<typename Moving, typename Attacking>
    // class StandardEnemy : public IEnemy {
    // public:
    //     explicit StandardEnemy(int strength, int x, int y)
    //             : IEnemy(strength, x, y) {}

    //     void operator+(Player& player) const override {
    //         Attacking::Attack(strength, player);
    //     }

    //     template <typename T, typename U>
    //     bool operator==(const StandardEnemy<T, U>& other) const {
    //         return Moving::behavior_id == T::behavior_id
    //                 && Attacking::behavior_id == U::behavior_id;
    //     }

    //     void Move() override {
    //         moving_strategy.Move(x, y);
    //     }

    //     void SetMovingBorders(const std::pair<int, int>& borders,
    //                           const Lib::Container<Common::Position>& obstacles) {
    //         moving_strategy.x_right_border = borders.first;
    //         moving_strategy.y_down_border = borders.second;
    //         moving_strategy.obstacles_cords = obstacles;
    //     }

    //     void Write(Lib::OutRFile& out) const override {
    //         Lib::Write(out, x);
    //         Lib::Write(out, y);
    //         Lib::Write(out, strength);

    //         // Записываем айди класса-поведения для движения
    //         Lib::Write(out, Moving::behavior_id);
    //         // Записываем левые и правые границы
    //         Lib::Write(out, moving_strategy.x_right_border);
    //         Lib::Write(out, moving_strategy.y_down_border);
    //         Lib::Write(out, moving_strategy.obstacles_cords);

    //         // Записываем айди класса-поведения для атаки
    //         Lib::Write(out, Attacking::behavior_id);
    //     }

    //     const ISerializable& Read(Lib::InRFile& in) override {
    //         throw Lib::SerializeReadError("StandardEnemy is not readable with it's Read method. Use ReadEnemy.");
    //     }

    // private:
    //     Moving moving_strategy;
    // };

    // inline std::shared_ptr<IEnemy> ReadEnemy(Lib::InRFile& in) {
    //     using namespace Behavior;

    //     int x = Lib::Read<int>(in);
    //     if (x < 0) {
    //         throw Lib::SerializeReadError("enemy's x coordinate cannot be negative");
    //     }

    //     int y = Lib::Read<int>(in);
    //     if (y < 0) {
    //         throw Lib::SerializeReadError("enemy's y coordinate cannot be negative");
    //     }

    //     int strength = Lib::Read<int>(in);
    //     if (strength < 0) {
    //         throw Lib::SerializeReadError("enemy's strength cannot be negative");
    //     }

    //     uint8_t moving_id = Lib::Read<uint8_t>(in);

    //     int x_right_border = Lib::Read<int>(in);
    //     int y_down_border = Lib::Read<int>(in);
    //     auto obstacles_cords = Lib::Read<Lib::Container<Common::Position>>(in);

    //     uint8_t attacking_id = Lib::Read<uint8_t>(in);

    //     // RandomMove
    //     if (moving_id == 0) {
    //         if (attacking_id == 0) {
    //             auto read_enemy = std::make_shared<StandardEnemy<RandomMove, InstantAttack>>(strength, x, y);
    //             read_enemy->SetMovingBorders({x_right_border, y_down_border}, obstacles_cords);
    //             return read_enemy;
    //         }
    //         else if (attacking_id == 1) {
    //             auto read_enemy = std::make_shared<StandardEnemy<RandomMove, PoisonBuffAttack>>(strength, x, y);
    //             read_enemy->SetMovingBorders({x_right_border, y_down_border}, obstacles_cords);
    //             return read_enemy;
    //         }
    //         else {
    //             throw Lib::SerializeReadError("unknown attacking id: " + std::to_string(attacking_id));
    //         }
    //     }

    //     throw Lib::SerializeReadError("unknown moving id: " + std::to_string(moving_id));
    // }

}