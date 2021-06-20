#pragma once

#include <memory>

#include "../model/cell.h"
#include "buffs.h"
#include "../lib/serialize.hpp"


namespace GameObject {

    class Player : public Lib::ISerializable {
    public:
        explicit Player(int x_ = 0, int y_ = 0,
                        int scores_ = 0, int lives_ = 3);

        Player &operator+(Model::Cell &cell);
        bool operator==(const Player& other) const;
        bool operator!=(const Player& other) const;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

        void UpdateBuffs();
        void SetLives(int lives_);
        void SetScores(int scores_);
        void SetX(int x_);
        void SetY(int y_);
        void SetBuff(std::shared_ptr<Buff> buff_);

        int X() const;
        int Y() const;
        int Scores() const;
        int Lives() const;

    private:
        int x;
        int y;
        int scores;
        int lives;

        std::shared_ptr<Buff> buff;
    };

}