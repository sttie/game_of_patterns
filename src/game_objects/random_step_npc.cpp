#include <game_objects/random_step_npc.h>
#include <array>
#include <cstdlib>

using namespace GameObject;

RandomStepNPC::RandomStepNPC(const Common::Position& position)
    : NPC(position)
{
}

Common::Position RandomStepNPC::Move() const {
    std::array<int, 3> directions = {-1, 0, 1};
    return Common::Position{
        position.x + directions[rand() % 3],
        position.y + directions[rand() % 3]
    };
}