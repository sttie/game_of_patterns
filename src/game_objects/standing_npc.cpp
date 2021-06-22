#include <game_objects/standing_npc.h>

using namespace GameObject;

StandingNPC::StandingNPC(const Common::Position& position)
    : NPC(position)
{
}

Common::Position StandingNPC::Move() const {
    return position;
}