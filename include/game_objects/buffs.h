#pragma once


namespace GameObject {

    class Buff {
    public:
        explicit Buff(int timer_) : timer(timer_) {}

        virtual void Apply(int &lives, int &scores) = 0;

    protected:
        int timer = 0;
    };


    class PoisonBuff : public Buff {
    public:
        explicit PoisonBuff(int timer_, int degree_)
                : Buff(timer_), degree(degree_) {}

        void Apply(int &lives, int &scores) override {
            if (timer > 0) {
                --timer;
                lives -= degree;
            }
        }

    private:
        int degree;
    };

}