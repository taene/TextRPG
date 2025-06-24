#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "System/GameManager.h"

#define UP 0
#define DOWN 1
#define SUBMIT 2

using namespace std;

int keyControl();
void init();
void title();
int menuDraw();
void gotoxy(int, int);
void infoDraw();

int main()
{
	init();

	GameManager GameManager;
	while (true)
	{
		title();
		int menuCode = menuDraw();
		if (menuCode == 0)
		{
			// 게임 시작
			GameManager.gameStart();
		}
		else if (menuCode == 1)
		{
			infoDraw();
		}
		else if (menuCode == 2)
		{
			return 0;
		}
		system("cls");
	}
	return 0;
}

void title()
{
	printf("\n");
	printf("\n");
	printf("=======================================================================================================================\n");
	printf("=        ===============================        ===============================      ========  ====  =====  ==        =\n");
	printf("====  ==================================  ====================================   ==   ======   ====   ===   ==  =======\n");
	printf("====  ==================================  ====================================  ====  =====    ====  =   =  ==  =======\n");
	printf("====  ======   ====   ===  =  = ========  =========   ===  =  ==  =   ========  ==========  =  ====  == ==  ==  =======\n");
	printf("====  =====  =  ==  =  ==        =======      ====     ==  =  ==    =  =======  =========  ==  ====  =====  ==      ===\n");
	printf("====  =====     =====  ==  =  =  =======  ========  =  ==  =  ==  ============  ===   ==  ===  ====  =====  ==  =======\n");
	printf("====  =====  ======    ==  =  =  =======  ========  =  ==  =  ==  ============  ====  ==         ==  =====  ==  =======\n");
	printf("====  =====  =  ==  =  ==  =  =  =======  ========  =  ==  =  ==  ============   ==   =======  ====  =====  ==  =======\n");
	printf("====  ======   ====    ==  =  =  =======  =========   ====    ==  =============      ========  ====  =====  ==        =\n");
	printf("=======================================================================================================================\n");
	printf("\n");
	printf("\n");
}

void init()
{
	system("mode con cols=200 lines 50 | title Team Four G4ME");
}

void infoDraw()
{
	system("cls");
	printf("\n\n");
	printf("               Team : 4조       \n\n");
	printf("         김연지  김태연  남승윤 \n");
	printf("            박진권     이선형   \n");
	printf("\n\n");
	printf("       내일배움캠프 TextRPG 과제 \n");
	printf("스페이스 바를 누르면 메인화면으로 이동합니다.");

	while (1)
	{
		if (keyControl() == SUBMIT)
		{
			break;
		}
	}
}
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int keyControl()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 32)
	{
		return SUBMIT;
	}
}


int menuDraw()
{
	int x = 50;
	int y = 15;
	gotoxy(x - 2, y);
	printf("> GAME START");
	gotoxy(x, y + 1);
	printf("GAME INFO");
	gotoxy(x, y + 2);
	printf("  QUIT");

	while (1)
	{
		int n = keyControl();
		switch (n)
		{
		case UP:
		{
			if (y > 15)  // y는 15~17까지만 이동
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN:
		{
			if (y < 17)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT:
		{
			return y - 15;
		}
		}
	}

}
