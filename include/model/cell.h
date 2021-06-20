#pragma once

#include <memory>
#include <string>

#include "elements_strategies.h"
#include "../lib/serialize.hpp"
#include "../common.h"


namespace Model {

    class Cell : public Lib::ISerializable {
    public:
        enum class CellType {
            OBSTACLE,
            EXIT,
            ENTER,
            EMPTY,
            LIVES_UP,
            SCORES_UP,
            PORTAL,
            COUNT
        };

        explicit Cell(Common::Position pos_ = {-1, -1},
                      CellType type_ = CellType::EMPTY,
                      Strategies::StrategyType strategy_type_ = Strategies::StrategyType::EMPTY);

        bool operator==(const Cell& other) const;
        bool operator!=(const Cell& other) const {
            return !(*this == other);
        }

        void SetStrategy(std::shared_ptr<Strategies::IStrategy> strategy_);
        void SetType(CellType type_);
        void SetPos(Common::Position pos_);
        void ApplyStrategy(int &x, int &y, int &scores, int &lives);

        bool WithStrategy() const;
        CellType Type() const;
        std::string StringType() const;

        void Write(Lib::OutRFile& out) const override;
        const ISerializable& Read(Lib::InRFile& in) override;

    private:
        Common::Position pos;
        CellType type;
        std::shared_ptr<Strategies::IStrategy> strategy;
        Strategies::StrategyType strategy_type;
    };

}