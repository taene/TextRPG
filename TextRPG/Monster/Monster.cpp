#include "Monster.h"

#include "../System/Utils.h"
#include "../Item/Item.h"
#include "../System/ItemFactory.h"

Monster::Monster(std::string name, int level, float healthMultiply, float attackMultiply)
	: name(name),
health(Utils::getRandomInRange(static_cast<int>(level * 20*healthMultiply), static_cast<int>(level * 30*healthMultiply))),
attack(Utils::getRandomInRange(static_cast<int>(level * 20 * attackMultiply), static_cast<int>(level * 30 * attackMultiply)))
{
}

void Monster::takeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
	{
		bIsDead = true;
	}
}

std::unique_ptr<Item> Monster::dropItem()
{
	int r = Utils::getRandomInRange(1, 100);
	// 30% 확률로 아이템 드랍
	if (r <= 30)
	{
		int temp = Utils::getRandomInRange(static_cast<int>(EItemType::HealthPotion), static_cast<int>(EItemType::AttackBoost));
		EItemType type = static_cast<EItemType>(temp);
		return ItemFactory::createItem(type);
	}

	return nullptr;
}
