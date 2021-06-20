#pragma once

#include "../lib/serialize.hpp"
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
        IStrategy(StrategyType type_)
                : type(type_) { }

        virtual void ApplyStrategy(int& x, int& y,
                                   int& scores, int& lives) const = 0;

    private:
        StrategyType type;
    };


    class ScoresUp : public IStrategy {
    public:
        explicit ScoresUp(int scores_amount_ = 50);

        void ApplyStrategy(int& x, int& y,
                           int& scores, int& lives) const override;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        int scores_amount;
    };


    class LivesUp : public IStrategy {
    public:
        explicit LivesUp(int lives_amount_ = 1);

        void ApplyStrategy(int& x, int& y,
                           int& scores, int& lives) const override;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        int lives_amount;
    };


    class Teleport : public IStrategy {
    public:
        explicit Teleport(int to_x_ = 0, int to_y_ = 0);

        void ApplyStrategy(int& x, int& y,
                           int& scores, int& lives) const override;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        int to_x;
        int to_y;
    };


}
