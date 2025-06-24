#include "Shop.h"
#include <iostream>

#include "../Character/Character.h"
#include "../System/ItemFactory.h"

Shop::Shop()
{
	availableItems.push_back(ItemFactory::createItem(EItemType::HealthPotion));
	availableItems.push_back(ItemFactory::createItem(EItemType::AttackBoost));
}

void Shop::displayItems() const
{
	std::cout << "-------------상점-------------\n";

	if (!availableItems.empty())
	{
		for (size_t i = 0; i < availableItems.size(); i++)
		{
			if (availableItems[i] != nullptr)
			{
				std::cout << i + 1 << ". " << availableItems[i]->getName() <<
					": Gold " << availableItems[i]->getPrice() << '\n';
			}
		}
	}
	else
	{
		std::cout << "상점에 아이템이 존재하지 않습니다.\n";
	}
}

void Shop::refreshShop()
{
	std::erase_if(availableItems, [] (std::unique_ptr<Item>& item) { return item == nullptr; });

	if (availableItems.empty())
		bHasItem = false;
}
