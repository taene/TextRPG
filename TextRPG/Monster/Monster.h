#pragma once
#include <memory>
#include <string>

enum class EMonsterType
{
	Default = 0,
	Goblin,
	Orc,
	Troll,
	Slime,
	Boss,
	End
};

class Monster
{
protected:
	std::string name;
	int health;
	int attack;
	EMonsterType type = EMonsterType::Default;

	bool bIsDead = false;

public:
	Monster(std::string name, int level, float healthMultiply = 1.f, float attackMultiply = 1.f);
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
		: Monster("고블린", level)
	{
	}
};

class Orc : public Monster
{
public:
	Orc(int level)
		: Monster("오크", level)
	{
	}
};

class Troll : public Monster
{
public:
	Troll(int level)
		: Monster("트롤", level)
	{
	}
};

class Slime : public Monster
{
public:
	Slime(int level)
		: Monster("슬라임", level)
	{
	}
};

class Dragon : public Monster
{
public:
	Dragon(int level)
		: Monster("드래곤", level, 1.5f, 1.5f)
	{
	}
};
