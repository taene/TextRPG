#pragma once
#include <memory>

#include "../Character/Character.h"

class GameManager
{
private:
	std::unique_ptr<Character> player;
	bool bIsGameOver = false;

public:
	void gameStart();
	
private:
	void selectPlayer();	// 이전 캐릭터 플레이 or 새 캐릭터 생성
	void createPlayer();	// 캐릭터 생성

	void battle(Character* player);

	std::unique_ptr<class Monster> createMonster(int level);

	void displayInventory(Character* player);
};

