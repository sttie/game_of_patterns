#include <game_objects/npc.h>
#include <common.h>

namespace GameObject {

    class RandomStepNPC : public NPC {
    public:
        RandomStepNPC(const Common::Position& position);

        Common::Position Move() const override final;
    };

}