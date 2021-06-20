#include "../../include/game_objects/player.h"

#include <utility>


using namespace GameObject;

Player::Player(int x_, int y_,
               int scores_, int lives_)
    : x(x_), y(y_), scores(scores_), lives(lives_)
{
    if (x < 0 || y < 0 || scores < 0 || lives <= 0)
        throw std::logic_error("Some of parameters are negative");
}


Player& Player::operator+(Model::Cell& cell) {
    cell.ApplyStrategy(x, y, scores, lives);
    return *this;
}

bool Player::operator==(const Player& other) const {
    return std::tie(x, y, lives, scores)
            == std::tie(other.x, other.y, other.lives, other.scores);
}

bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}


void Player::Write(Lib::OutRFile& out) const {
    Lib::Write(out, x);
    Lib::Write(out, y);
    Lib::Write(out, scores);
    Lib::Write(out, lives);
}
const Lib::ISerializable& Player::Read(Lib::InRFile& in) {
    x = Lib::Read<int>(in);
    if (x < 0) {
        throw Lib::SerializeReadError("player's x coordinate cannot be negative");
    }

    y = Lib::Read<int>(in);
    if (y < 0) {
        throw Lib::SerializeReadError("player's u coordinate cannot be negative");
    }

    scores = Lib::Read<int>(in);
    if (scores < 0) {
        throw Lib::SerializeReadError("player's scores cannot be negative");
    }

    lives = Lib::Read<int>(in);
    if (lives <= 0) {
        throw Lib::SerializeReadError("player's lives cannot be negative");
    }

    return *this;
}


void Player::UpdateBuffs() {
    if (buff)
        buff->Apply(lives, scores);
}

void Player::SetLives(int lives_) {
    lives = lives_;
}
void Player::SetScores(int scores_) {
    scores = scores_;
}

void Player::SetX(int x_) {
    x = x_;
}

void Player::SetY(int y_) {
    y = y_;
}

void Player::SetBuff(std::shared_ptr<Buff> buff_) {
    buff = std::move(buff_);
}

int Player::X() const {
    return x;
}

int Player::Y() const {
    return y;
}

int Player::Scores() const {
    return scores;
}

int Player::Lives() const {
    return lives;
}