#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../Item/Item.h"

class Character
{
private:

	std::string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int gold;
	bool bIsDead = false;
	std::vector<std::unique_ptr<Item>> inventory;

public:

	Character(std::string name);

	void displayInventory() const;
	void displayStatus();
	void takeDamage(int damage);
	void visitShop();

	void buyItem(int index, class Shop& shop);
	void sellItem(int index, class Shop& shop);
	void setItem(std::unique_ptr<Item> item);
	void useItem(int index);

	bool hasItem() const { return !inventory.empty(); }
	bool isDead() const { return bIsDead; }
	const std::string& getName() const { return name; }


	// 단순 get set 함수들
	const std::vector<std::unique_ptr<Item>>& getInventory() const { return inventory; }

	int getLevel() const { return level; }
	void setLevelUp();

	int getHealth() const { return health; }
	void addHealth(int health);

	int getAttack() const { return attack; }
	void addAttack(int atk);

	int getExperience() const { return experience; }
	void addExperience(int exp);

	int getGold() const { return gold; }
	void setGold(int gold);

};