#pragma once

#include "lib/serialize.hpp"


namespace Common {

    class Position : public Lib::ISerializable {
    public:
        Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) { }

        bool operator==(const Position& b) const {
            return x == b.x && y == b.y;
        }

        void Write(Lib::OutRFile& out) const override {
            Lib::Write(out, x);
            Lib::Write(out, y);
        }

        const ISerializable& Read(Lib::InRFile& in) override {
            x = Lib::Read<int>(in);
            y = Lib::Read<int>(in);
            return *this;
        }

        int x, y;
    };

    struct Date {
        int year = 0;
        int month = 0;
        int day = 0;
        int hour = 0;
        int minute = 0;
        int second = 0;
    };

}