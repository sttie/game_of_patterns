#pragma once

#include <vector>
#include <memory>

#include "../model/field.h"
#include "../lib/unit_testing.hpp"
#include "../logging/listener.h"


class TestingListener : public Logging::Listener {
public:
    void Update() override {
        ++updates_amount;
    }

    int updates_amount = 0;
};

inline void TestField() {
    using namespace Model;

    auto field = Model::Field::GetField(10, 10, 80);

    // Проверяем, вернется ли игрок в исходное положение
    std::vector<Field::Move> moves = {
            Field::Move::UP,
            Field::Move::UP,
            Field::Move::RIGHT
    };
    for (const auto& move : moves)
        field.MovePlayer(move);
    // Если здесь его сдвинуть направо, то он не должен оказаться в препятствии
    field.MovePlayer(Field::Move::RIGHT);
    ASSERT(!field.IsObstacle(field.PlayerX(), field.PlayerY()));


    // Проверяем нотифаер
    auto test_listener = std::make_shared<TestingListener>();
    field.AddListener(test_listener);

    moves = {
            Field::Move::UP,
            Field::Move::UP,
            Field::Move::RIGHT,
            Field::Move::UP,
            Field::Move::UP,
            Field::Move::RIGHT,
            Field::Move::UP,
            Field::Move::UP,
            Field::Move::RIGHT
    };
    // Заставляем поле обновляться и оповещать об этом слушателей
    for (const auto& move : moves)
        field.MovePlayer(move);
    ASSERT(test_listener->updates_amount == moves.size());

    Field::ClearField();
}