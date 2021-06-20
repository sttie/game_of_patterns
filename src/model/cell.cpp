#include "../../include/model/cell.h"

#include <utility>


using namespace std;
using namespace Model;


Cell::Cell(Common::Position pos_, CellType type_, Strategies::StrategyType strategy_type_)
    : pos(std::move(pos_)), type(type_)
    , strategy_type(strategy_type_), strategy(nullptr)
{
}

bool Cell::operator==(const Cell& other) const {
    return std::tie(pos, type) == std::tie(other.pos, other.type);
}

void Cell::SetStrategy(std::shared_ptr<Strategies::IStrategy> strategy_) {
    strategy = std::move(strategy_);
}

void Cell::SetType(CellType type_) {
    type = type_;
}

void Cell::SetPos(Common::Position pos_) {
    pos = std::move(pos_);
}

bool Cell::WithStrategy() const {
    return strategy != nullptr;
}

Cell::CellType Cell::Type() const {
    return type;
}

void Cell::ApplyStrategy(int& x, int& y,
                         int& scores, int& lives) {
    if (strategy) {
        strategy->ApplyStrategy(x, y, scores, lives);
        strategy = nullptr;
        type = CellType::EMPTY;
    }
}

std::string Cell::StringType() const {
    switch (type) {
        case CellType::ENTER:
            return "Enter";
        case CellType::EXIT:
            return "Exit";
        case CellType::OBSTACLE:
            return "Obstacle cell";
    }

    switch (strategy_type) {
        case Strategies::StrategyType::LIVES_UP:
            return "Lives up cell";
        case  Strategies::StrategyType::SCORES_UP:
            return "Scores up cell";
        case  Strategies::StrategyType::PORTAL:
            return "Portal cell";
    }

    return "";
}


void Cell::Write(Lib::OutRFile& out) const {
    Lib::Write(out, pos);
    Lib::Write(out, static_cast<int>(type));

    // Также вписываем маркеры, говорящие о том, была ли у клетки стратегия
    if (strategy) {
        Lib::Write<uint8_t>(out, 1);
        strategy->Write(out);
    } else {
        Lib::Write<uint8_t>(out, 0);
    }
}

const Lib::ISerializable& Cell::Read(Lib::InRFile& in) {
    pos = Lib::Read<Common::Position>(in);

    int int_type = Lib::Read<int>(in);
    if (int_type < 0 || int_type >= static_cast<int>(CellType::COUNT)) {
        throw Lib::SerializeReadError("cell type int representation is negative or overflowed");
    }

    SetStrategy(static_cast<CellType>(int_type));
    uint8_t has_strategy = Lib::Read<uint8_t>(in);
    if (has_strategy > 1) {
        throw Lib::SerializeReadError("cell's has_strategy flag cannot be more than 1");
    }


    if (has_strategy) {
        strategy->Read(in);
    }

    return *this;
}