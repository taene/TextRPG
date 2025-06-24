#pragma once
#include <memory>
#include <vector>

#include "../Item/Item.h"

class Shop
{
private:
	
	bool bHasItem = true;
	std::vector<std::unique_ptr<Item>> availableItems;

public:

	Shop();
	virtual ~Shop() = default;

	void displayItems();
	bool hasItem() const { return bHasItem; }
	
	std::unique_ptr<Item>& getItem(int index) { return availableItems[index]; }
};

