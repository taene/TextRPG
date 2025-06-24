#pragma once
#include <memory>
#include <string>

#include "../System/Utils.h"

enum class EMonsterType
{
	Default = 0,
	Goblin,
	Orc,
	Troll,
	Slime,
	Boss
};

class Monster
{
protected:
	std::string name;
	int health;
	int attack;
	EMonsterType type;

	bool bIsDead = false;

public:
	Monster(std::string name, int health, int attack, EMonsterType type)
		:name(name), health(health), attack(attack), type(type)
	{
	}
	virtual ~Monster() = default;

	std::string getName() const { return name; }
	int getHealth() const { return health; }
	int getAttack() const { return attack; }
	EMonsterType getType() const { return type; }

	bool isDead() const { return bIsDead; }
	void takeDamage(int damage);
	
	std::unique_ptr<class Item> dropItem();
};

class Goblin : public Monster
{
public:
	Goblin(int level)
		:Monster("고블린",
			Utils::getRandomInRange(level * 20, level * 30),
			Utils::getRandomInRange(level * 5, level * 10),
			EMonsterType::Goblin)
	{
	}
};

class Orc : public Monster
{
public:
	Orc(int level)
		:Monster("오크",
			Utils::getRandomInRange(level * 20, level * 30),
			Utils::getRandomInRange(level * 5, level * 10),
			EMonsterType::Orc)
	{
	}
};

class Troll : public Monster
{
public:
	Troll(int level)
		:Monster("트롤",
			Utils::getRandomInRange(level * 20, level * 30),
			Utils::getRandomInRange(level * 5, level * 10),
			EMonsterType::Troll)
	{
	}
};

class Slime : public Monster
{
public:
	Slime(int level)
		:Monster("슬라임",
			Utils::getRandomInRange(level * 20, level * 30),
			Utils::getRandomInRange(level * 5, level * 10),
			EMonsterType::Slime)
	{
	}
};

class Dragon : public Monster
{
public:
	Dragon(int level)
		:Monster("드래곤",
			Utils::getRandomInRange(static_cast<int>(level * 20 * 1.5f), static_cast<int>(level * 30 * 1.5f)),
			Utils::getRandomInRange(static_cast<int>(level * 5 * 1.5f), static_cast<int>(level * 10 * 1.5f)),
			EMonsterType::Boss)
	{
	}
};