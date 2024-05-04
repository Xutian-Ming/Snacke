#include<iostream>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include<easyx.h>
#include"class.h"
using namespace std;

int main()
{
	Snake snake;
	srand((unsigned)time(0));
	while (1)
	{
		snake.menu();
		if (snake.getchoice() == -1)
			return 0;
		if (snake.getchoice() == 7)
		{
			snake.historyrecordshow();
			continue;
		}
		if (snake.getchoice() == 8)
		{
			snake.historyrecorddelete();
			continue;
		}
		if (snake.getchoice() == 9)
		{
			snake.historyrecordsearch();
			continue;
		}
		if (snake.getchoice() == 10)
		{
			snake.historyrecordchangename();
			continue;
		}
		if (snake.getchoice() == 11)
		{
			snake.readhistory();
		}
		if (snake.getchoice() == 0)
			continue;
		initgraph(12 * length, 22 * width, EW_SHOWCONSOLE);
		if (snake.getchoice() == 1)
			snake.game1();
		if (snake.getchoice() == 2)
			snake.game2();
		if (snake.getchoice() == 3)
			snake.game3();
		if (snake.getchoice() == 4)
			snake.game4();
		if (snake.getchoice() == 5)
			snake.game5();
		if (snake.getchoice() == 6)
			snake.game6();
	}
}