#include "Character.h"
#include <iostream>

#include "../Shop/Shop.h"

Character::Character(std::string name)
{
	this->name = name;
	level = 1;
	maxHealth = 200;
	health = maxHealth;
	attack = 30;
	experience = 0;
	gold = 0;
}

void Character::displayInventory() const
{
	std::cout << "------인벤토리-----\n";
	if (inventory.empty())
	{
		std::cout << "비어있습니다.\n";
	}
	else
	{
		for (size_t i = 0; i < inventory.size(); i++)
		{
			std::cout << i + 1 << ". " << inventory[i]->getName() << '\n';
		}
	}
	std::cout << "------------------\n";
}

void Character::displayStatus()
{
	std::cout << "-------스탯------\n"
		<< "이름: " << name << '\n'
		<< "레벨: " << level << '\n'
		<< "체력: " << health << " / " << maxHealth << '\n'
		<< "공격력: " << attack << '\n'
		<< "경험치: " << experience << '\n'
		<< "골드: " << gold << '\n'
		<< "------------------\n";
}

void Character::takeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
	{
		bIsDead = true;
	}
}

void Character::visitShop()
{
	// 도전기능: interaction with Shop
	std::cout << "=============상점============\n";

	Shop shop;
	while (true)
	{
		std::cout << "=============================\n";
		std::cout << "보유 Gold: " << getGold() << '\n';
		std::cout << "1. 아이템 구매\n"
			<< "2. 아이템 판매\n"
			<< "3. 나가기\n"
			<< "(1/2/3): ";
		int choice;
		std::cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			shop.displayItems();

			if (shop.hasItem())
			{
				std::cout << "선택: ";
				int itemIndex;
				std::cin >> itemIndex;

				buyItem(itemIndex - 1, shop);
			}
		}
			break;
		case 2:
		{
			this->displayInventory();

			if (hasItem())
			{
				std::cout << "0. 취소\n";
				std::cout << "선택: ";
				int itemIndex;
				std::cin >> itemIndex;

				if (itemIndex > 0)
					sellItem(itemIndex - 1, shop);
				else
					std::cout << "아이템 판매를 취소했습니다.\n";
			}
			else
			{
				std::cout << "판매할 아이템이 없습니다.\n";
			}
		}
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void Character::buyItem(int index, Shop& shop)
{
	std::unique_ptr<Item>& item = shop.getItem(index);

	if (item->getPrice() <= getGold())
	{
		int buyPrice = getGold() - item->getPrice();
		setGold(buyPrice);
		std::cout << item->getName() << "을(를) 구매했습니다! 잔액 Gold: " << getGold() << '\n';
		this->setItem(std::move(item));	// move(item) 이후로 item에 접근 불가
	}
	else
	{
		std::cout << "잔액이 부족합니다. 구매하지 못했습니다. 잔액 Gold: " << getGold() << '\n';
	}
}

void Character::sellItem(int index, Shop& shop)
{
	if (index >= 0 && index < inventory.size())
	{
		// 판매가만큼 골드를 얻고 인벤토리에서 해당 아이템 지우기
		int sellPrice = static_cast<int>(inventory[index]->getPrice() * 0.6);
		setGold(getGold() + sellPrice);
		
		std::cout << inventory[index]->getName() << "을(를) 팔았습니다! "
			<< "판매가: " << sellPrice << " 잔액 Gold: " << getGold() << '\n';

		inventory.erase(inventory.begin() + index);
	}
}

void Character::setItem(std::unique_ptr<Item> item)
{
	inventory.push_back(std::move(item));
}

void Character::useItem(int index)
{
	if (index >= 0 && index < inventory.size())
	{
		if (inventory[index] != nullptr)
		{
			// 인벤토리 사용 후 삭제
			// TODO: 인벤토리의 아이템 사용(Item::use())
			inventory[index]->use(this);
			std::cout << "사용 아이템: " << inventory[index]->getName() << '\n';
			
			inventory.erase(inventory.begin() + index);
		}
		else
		{
			std::cout << "Error: There are no items in Inventory.\n";
		}
	}
	else
	{
		std::cout << "Error: Invalid item index.\n";
	}
}

void Character::setLevelUp()
{
	if (level >= 10)
	{
		std::cout << "최대 레벨입니다. 레벨업 할 수 없습니다.\n";
		return;
	}

	while (level <= 10 && experience >= 100)
	{
		experience -= 100;
		++level;
	}

	std::cout << "레벨업! 레벨: " << level
		<< " / 경험치: " << experience << '\n';

	maxHealth += level * 20;
	attack += level * 5;
	addHealth(maxHealth);
}

void Character::addHealth(int health)
{
	this->health += health;

	if (this->health >= maxHealth)
	{
		this->health = maxHealth;
	}
}

void Character::addAttack(int atk)
{
	attack += atk;
}

void Character::addExperience(int exp)
{
	experience += exp;

	if (experience >= 100)
	{
		setLevelUp();
	}
}

void Character::setGold(int gold)
{
	this->gold = gold;
}

