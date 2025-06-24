#include "Item.h"

#include "../Character/Character.h"

void HealthPotion::use(Character* player)
{
	player->addHealth(this->healthRestore);
}

void AttackBoost::use(Character* player)
{
	player->addAttack(this->attackIncrease);
}
