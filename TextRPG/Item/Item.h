#pragma once
#include <string>

enum class EItemType
{
	Default = 0,
	HealthPotion,
	AttackBoost
};

class Item
{
protected:
	std::string name;
	int price;
	EItemType type;

public:
	Item(std::string name, int price, EItemType type) :name(name), price(price), type(type) {}
	virtual ~Item() = default;

	std::string getName() const { return name; }
	int getPrice() const { return price; }

	virtual void use(class Character* player) = 0;
};

class HealthPotion :public Item
{
private:
	int healthRestore;

public:
	HealthPotion() :Item("힐포션", 5, EItemType::HealthPotion), healthRestore(50) {}

	virtual void use(class Character* player) override;
};

class AttackBoost :public Item
{
private:
	int attackIncrease;

public:
	AttackBoost() :Item("딜부스터", 1, EItemType::AttackBoost), attackIncrease(10) {}

	virtual void use(class Character* player) override;
};
