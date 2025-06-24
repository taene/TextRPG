#pragma once
#include <memory>

class Monster;
enum class EMonsterType;

class MonsterFactory
{
public:
	static std::unique_ptr<Monster> createMonster(EMonsterType type, int level);
};