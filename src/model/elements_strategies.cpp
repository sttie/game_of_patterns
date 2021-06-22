#include <model/elements_strategies.h>
#include <game_objects/player.h>
#include <stdexcept>

using namespace std;
using namespace Strategies;


ScoresUp::ScoresUp(int scores_amount)
    : IStrategy(StrategyType::SCORES_UP)
    , scores_amount(scores_amount)
{
}

void ScoresUp::ApplyStrategy(GameObject::Player& player) const {
    player.TakeScores(scores_amount);
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
    , lives_amount(lives_amount) { }

void LivesUp::ApplyStrategy(GameObject::Player& player) const {
    player.TakeHeal(lives_amount);
}

void LivesUp::Write(Lib::OutRFile& out) const {
    Lib::Write(out, lives_amount);
}
const Lib::ISerializable& LivesUp::Read(Lib::InRFile& in) {
    lives_amount = Lib::Read<int>(in);
    return *this;
}


Teleport::Teleport(int to_x, int to_y)
    : IStrategy(StrategyType::PORTAL)
    , to_x(to_x), to_y(to_y)
{
}

void Teleport::ApplyStrategy(GameObject::Player& player) const {
    player.SetPosition(to_x, to_y);
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