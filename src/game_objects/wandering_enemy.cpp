#include <game_objects/wandering_enemy.h>

using namespace GameObject;

WanderingEnemy::WanderingEnemy(const Common::Position& position, int strength)
    : RandomStepNPC(position), strength(strength)
{
}

void WanderingEnemy::InteractWithPlayer(Player& player) const {
    player.TakeDamage(strength);
}