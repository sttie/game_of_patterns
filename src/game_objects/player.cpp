#include <game_objects/player.h>

#include <utility>

using namespace GameObject;


Player::Player(int x, int y, int scores, int lives)
    : x(x), y(y), scores(scores), lives(lives)
{
    if (x < 0 || y < 0 || scores < 0 || lives <= 0)
        throw std::logic_error("Some of parameters are negative");
}


// Returns true if (lives - lives_damage <= 0)
bool Player::TakeDamage(int lives_damage) {
    lives = std::max(lives - lives_damage, 0);
    return lives == 0;
}

void Player::TakeHeal(int lives_heal) {
    lives += lives_heal;
}

void Player::TakeScores(int scores_amount) {
    scores += scores_amount;
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

void Player::SetPosition(int x_, int y_) {
    x = x_;
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