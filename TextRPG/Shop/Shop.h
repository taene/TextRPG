#pragma once
#include <memory>
#include <vector>

#include "../Item/Item.h"

class Shop
{
private:
	
	std::vector<std::unique_ptr<Item>> availableItems;

public:

	Shop();
	virtual ~Shop() = default;

	void displayItems();
	
	std::unique_ptr<Item>& getItem(int index) { return availableItems[index]; }
};

