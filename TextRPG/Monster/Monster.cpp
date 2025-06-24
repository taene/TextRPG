#include "Monster.h"

#include "../Item/Item.h"
#include "../System/ItemFactory.h"

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
