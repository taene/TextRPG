#pragma once
#include <memory>

class Item;
enum class EItemType;

class ItemFactory
{
public:
	static std::unique_ptr<Item> createItem(EItemType type);
};
