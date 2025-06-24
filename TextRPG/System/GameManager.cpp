#include "GameManager.h"
#include <iostream>

#include "MonsterFactory.h"
#include "ItemFactory.h"

#include "../Monster/Monster.h"
#include "../Item/Item.h"

void GameManager::gameStart()
{
	selectPlayer();

	while (!bIsGameOver)
	{
		int choice;
		std::cout << "=============================\n";
		std::cout << "1. 던전 입장\n"
			<< "2. 캐릭터 스탯 확인\n"
			<< "3. 인벤토리 확인\n"
			<< "4. 상점 방문\n"
			<< "5. 게임 종료\n";
		std::cout << "선택: ";
		std::cin >> choice;
		
		switch (choice)
		{
		case 1:
			battle(player.get());
			break;

		case 2:
			player->displayStatus();
			break;

		case 3:
			player->displayInventory();
			break;
			
		case 4:
			player->visitShop();
			break;

		case 5:
			std::cout << "시작 화면으로 돌아갑니다...\n";
			bIsGameOver = true;
			break;

		default:
			std::cout << "잘못된 입력입니다. 다시 시도해주세요. \n";
		}
	}

	bIsGameOver = false;
}

void GameManager::selectPlayer()
{
	if (player == nullptr)
	{
		createPlayer();
	}
	else
	{
		system("cls");

		std::cout << "기존에 생성했던 캐릭터가 남아있습니다.\n";
		player->displayStatus();
		std::cout << "이어서 플레이 하시겠습니까 ? Y / N : ";

		bool bIsFinish = false;
		while (!bIsFinish)
		{
			char choice;
			std::cin >> choice;

			switch (choice)
			{
			case 'Y': case 'y':
				std::cout << player->getName() << "님, 환영합니다!\n";
				bIsFinish = true;
				break;

			case 'N': case 'n':
				createPlayer();
				bIsFinish = true;
				break;

			default:
				std::cout << "잘못된 입력입니다. 다시 시도해주세요. \n";
			}
		}
	}
}

void GameManager::createPlayer()
{
	system("cls");

	std::string name;
	std::cout << "캐릭터 이름을 입력하세요: ";
	std::cin >> name;
	player = std::make_unique<Character>(name);
	std::cout << "캐릭터 " << name << " 생성 완료!\n";
	player->displayStatus();
}
void GameManager::battle(Character* player)
{
	std::unique_ptr<Monster> monster = createMonster(player->getLevel());
	std::cout << "==========전투 시작==========\n";
	
	if (monster->getType() != EMonsterType::Boss)
	{
		std::cout << "몬스터 " << monster->getName() << " 등장! ";
	}
	else
	{
		std::cout<< "보스 몬스터 "<< monster->getName() << "이(가) 등장했습니다! 파이팅!\n";
	}
	std::cout << "체력: " << monster->getHealth() 
		<< ", 공격력: " << monster->getAttack() << '\n';

	// 전투로직
	while (!player->isDead() && !monster->isDead())
	{
		if (player->hasItem())
		{
			std::cout << "> 이럴때 아이템!\n";
			int index = Utils::getRandomInRange(0, player->getInventory().size() - 1);
			player->useItem(index);
		}

		std::cout << "-----------------------------\n";
		monster->takeDamage(player->getAttack());
		std::cout << player->getName() << "---공격--->" << monster->getName() << '\n';
		std::cout << monster->getName() << " 체력: " << monster->getHealth() << '\n';

		if (monster->isDead()) break;

		std::cout << "-----------------------------\n";
		player->takeDamage(monster->getAttack());
		std::cout << monster->getName() << "---공격--->" << player->getName() << '\n';
		std::cout << player->getName() << " 체력: " << player->getHealth() << '\n';

		if (player->isDead()) break;
	}

	// 몬스터가 죽으면 => 경험치50 골드10~20 아이템드랍
	if (monster->isDead())
	{
		std::cout << "=============승리============\n";
		std::cout << monster->getName() << " 처치!\n";
		
		if (monster->getType() == EMonsterType::Boss)
		{
			std::cout << "> 축하합니다! 보스 " << monster->getName() << "을(를) 처치하고 게임을 클리어했습니다!\n";
			bIsGameOver = true;
			return;
		}

		int exp = 50;
		int gold = Utils::getRandomInRange(10, 20);
		player->addExperience(exp);
		player->setGold(player->getGold() + gold);

		std::cout << player->getName() << "이(가) " << exp << "와 " << gold << " 골드를 획득했습니다. "
			<< "현재 EXP : " << player->getExperience() << "/100, 골드: " << player->getGold() << '\n';
		
		std::unique_ptr<Item> item = monster->dropItem();
		if (item != nullptr)
		{
			std::cout << "> 획득한 아이템: " << item->getName() << '\n';
			player->setItem(std::move(item));
		}

		std::cout << "상점을 방문하시겠습니까? Y/N: ";
		bool bIsFinish = false;
		while (!bIsFinish)
		{
			char choice;
			std::cin >> choice;

			switch (choice)
			{
			case 'Y': case 'y':
				player->visitShop();
				bIsFinish = true;
				break;

			case 'N': case 'n':
				std::cout << "전투를 준비합니다...\n";
				bIsFinish = true;
				break;

			default:
				std::cout << "잘못된 입력입니다. 다시 시도해주세요: ";
			}
		}
	}
	else if (player->isDead())
	{
		std::cout << "\n=============패배============\n";
		std::cout << player->getName() << "이(가) 사망했습니다. 타이틀로 돌아갑니다...\n";
		delete player;
		player = nullptr;
		bIsGameOver = true;

		return;
	}
}


std::unique_ptr<Monster> GameManager::createMonster(int level)
{
	if (level >= 10)
	{
		return MonsterFactory::createMonster(EMonsterType::Boss, level);
	}

	int r = Utils::getRandomInRange(static_cast<int>(EMonsterType::Goblin), static_cast<int>(EMonsterType::Slime));
	EMonsterType type = static_cast<EMonsterType>(r);
	return MonsterFactory::createMonster(type, level);
}

void GameManager::displayInventory(Character* player)
{
	player->displayInventory();
}
