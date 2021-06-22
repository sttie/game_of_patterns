#include <game_objects/npc.h>
#include <common.h>

namespace GameObject {

    class StandingNPC : public NPC {
    public:
        StandingNPC(const Common::Position& position);

        Common::Position Move() const override final;
    };

}