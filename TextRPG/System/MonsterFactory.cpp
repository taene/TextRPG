#include "MonsterFactory.h"

#include "../Monster/Monster.h"

std::unique_ptr<Monster> MonsterFactory::createMonster(EMonsterType type, int level)
{
	switch (type)
	{
	case EMonsterType::Default:
		return nullptr;
	case EMonsterType::Goblin:
		return std::make_unique<Goblin>(level);
	case EMonsterType::Orc:
		return std::make_unique<Orc>(level);
	case EMonsterType::Troll:
		return std::make_unique<Troll>(level);
	case EMonsterType::Slime:
		return std::make_unique<Slime>(level);
	case EMonsterType::Boss:
		return std::make_unique<Dragon>(level);
	default:
		return nullptr;
	}
}
