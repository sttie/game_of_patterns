#include "../../include/model/elements_strategies.h"
#include <stdexcept>

using namespace std;
using namespace Strategies;


ScoresUp::ScoresUp(int scores_amount_)
    : IStrategy(StrategyType::SCORES_UP)
    , scores_amount(scores_amount_) { }

void ScoresUp::ApplyStrategy(int& x, int& y,
                             int& scores, int& lives) const {
    scores += scores_amount;
}

void ScoresUp::Write(Lib::OutRFile& out) const {
    Lib::Write(out, scores_amount);
}
const Lib::ISerializable& ScoresUp::Read(Lib::InRFile& in) {
    scores_amount = Lib::Read<int>(in);
    return *this;
}


LivesUp::LivesUp(int lives_amount_)
    : IStrategy(StrategyType::LIVES_UP)
    , lives_amount(lives_amount_) { }

void LivesUp::ApplyStrategy(int& x, int& y,
                            int& scores, int& lives) const {
    lives += lives_amount;
}

void LivesUp::Write(Lib::OutRFile& out) const {
    Lib::Write(out, lives_amount);
}
const Lib::ISerializable& LivesUp::Read(Lib::InRFile& in) {
    lives_amount = Lib::Read<int>(in);
    return *this;
}


Teleport::Teleport(int to_x_, int to_y_)
    : IStrategy(StrategyType::PORTAL)
    , to_x(to_x_), to_y(to_y_)
{
}

void Teleport::ApplyStrategy(int& x, int& y,
                             int& scores, int& lives) const {
    x = to_x;
    y = to_y;
}

void Teleport::Write(Lib::OutRFile& out) const {
    Lib::Write(out, to_x);
    Lib::Write(out, to_y);
}
const Lib::ISerializable& Teleport::Read(Lib::InRFile& in) {
    to_x = Lib::Read<int>(in);
    to_y = Lib::Read<int>(in);
    return *this;
}