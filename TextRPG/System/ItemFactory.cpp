#include "ItemFactory.h"

#include "../Item/Item.h"

std::unique_ptr<Item> ItemFactory::createItem(EItemType type)
{
	switch (type)
	{
	case EItemType::Default:
		return nullptr;
	case EItemType::HealthPotion:
		return std::make_unique<HealthPotion>();
	case EItemType::AttackBoost:
		return std::make_unique<AttackBoost>();
	default:
		return nullptr;
	}
}
