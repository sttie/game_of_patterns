#pragma once

#include <lib/serialize.hpp>
#include <game_objects/player.h>
#include <string>


namespace Strategies {

    enum class StrategyType {
        SCORES_UP,
        LIVES_UP,
        PORTAL,
        EMPTY
    };

    class IStrategy : public Lib::ISerializable {
    public:
        IStrategy(StrategyType type)
                : type(type) { }

        virtual void ApplyStrategy(GameObject::Player& player) const = 0;

    private:
        StrategyType type;
    };


    class ScoresUp : public IStrategy {
    public:
        explicit ScoresUp(int scores_amount = 50);

        void ApplyStrategy(GameObject::Player& player) const override;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        int scores_amount;
    };


    class LivesUp : public IStrategy {
    public:
        explicit LivesUp(int lives_amount = 1);

        void ApplyStrategy(GameObject::Player& player) const override;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        int lives_amount;
    };


    class Teleport : public IStrategy {
    public:
        explicit Teleport(int to_x = 0, int to_y = 0);

        void ApplyStrategy(GameObject::Player& player) const override;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        int to_x;
        int to_y;
    };


}
