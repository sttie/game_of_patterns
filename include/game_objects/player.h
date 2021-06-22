#pragma once

#include <memory>
#include <game_objects/buffs.h>
#include <lib/serialize.hpp>


namespace GameObject {

    class Player : public Lib::ISerializable {
    public:
        explicit Player(int x = 0, int y = 0,
                        int scores = 0, int lives = 3);

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

        // Returns true if (lives - lives_damage <= 0)
        bool TakeDamage(int lives_damage);
        void TakeHeal(int lives_heal);
        void TakeScores(int scores_amount);

        void UpdateBuffs();
        void SetLives(int lives_);
        void SetScores(int scores_);

        void SetX(int x_);
        void SetY(int y_);
        void SetPosition(int x_, int y_);

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