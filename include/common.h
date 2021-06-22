#pragma once

#include "lib/serialize.hpp"


namespace Common {

    class Position : public Lib::ISerializable {
    public:
        Position(int x = 0, int y = 0) : x(x), y(y) { }

        bool operator==(const Position& b) const {
            return x == b.x && y == b.y;
        }

        bool IsOutOfBounds(int xbound, int ybound) const {
            return x < 0 || x >= xbound || y < 0 || y >= ybound;
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