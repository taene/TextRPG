#include "Shop.h"
#include <iostream>

#include "../Character/Character.h"
#include "../System/ItemFactory.h"

Shop::Shop()
{
	availableItems.push_back(ItemFactory::createItem(EItemType::HealthPotion));
	availableItems.push_back(ItemFactory::createItem(EItemType::AttackBoost));
}

void Shop::displayItems()
{
	std::cout << "-------------상점-------------\n";

	for (size_t i = 0; i < availableItems.size(); i++)
	{
		if (availableItems[i] == nullptr)
		{
			availableItems.erase(availableItems.begin() + i);
		}
	}

	for (size_t i = 0; i < availableItems.size(); i++)
	{
		if (availableItems[i] != nullptr)
		{
			std::cout << i + 1 << ". " << availableItems[i]->getName() <<
				": Gold " << availableItems[i]->getPrice() << '\n';
		}
	}
}
