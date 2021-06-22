#include <game_objects/random_step_npc.h>
#include <common.h>

namespace GameObject {

    class WanderingEnemy : public RandomStepNPC {
    public:
        WanderingEnemy(const Common::Position& position, int strength);
        void InteractWithPlayer(Player& player) const override;

    private:
        int strength;
    };

}