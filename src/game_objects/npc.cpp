#include <game_objects/npc.h>

using namespace GameObject;

NPC::NPC(const Common::Position& position) : position(position)
{
}

NPC::NPC(int x, int y) : position(x, y)
{
}

int NPC::X() const {
    return position.x;
}

int NPC::Y() const {
    return position.y;
}

void NPC::SetPosition(const Common::Position& pos) {
    position = pos;
}