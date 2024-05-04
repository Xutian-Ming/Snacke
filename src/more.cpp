#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include<ctime>
#include<easyx.h>
#include<fstream>
#include<stdlib.h>
#include<strstream>
#include"class.h"
using namespace std;

//其他模式
extern void gotoxy(const int X, const int Y);
extern void getxy(int& x, int& y);

//choice4	体能槽，多种果实
void Snake::game4()
{
	if (startflag&&!readhistoryflag)
	{
		for (int i = 0; i < (length + 1); i++)			//初始化二维数组用来记录食物的位置
			for (int j = 0; j < (width + 1); j++)
				foodpos[i][j] = 0;
	}
	historyrecordread();
	drawwall();
	init_snake();
	if (!readhistoryflag)
		sec = 0;
	while (1)
	{
		UIstate_show();
		if (foodcount == 0)
		{
			if (badfoodcount <= badfoodmax)
				createbadfood();
			if (goodfoodsymbol)
				creategoodfood();
			create_foodmore();
		}
		if (foodcount > 0&&foodcount<foods)
		{
			drawfoodmore();
			drawbadfood();
		}
		inputcheck();
		if (returnflag)
		{
			historyrecordwrite();
			gameover();
			break;
		}
		move();
		snakestateset();
		keepwallline();
		drawsnake();
		if (snakedead())
		{
			historyrecordwrite();
			gameover();
			break;
		}
		Sleep(speed);
		energydecrease();
	}
}
void Snake::create_foodmore()
{
	int count = 0;
	bool flag = 0;
	int random = 0;
	if (foodcount == 0)
		foodcount = rand() % 10 + 1;					//生成1-5个食物
	while (count < foodcount)
	{
		random = rand() % 10 + 1;
		food[count].pos_fx = (rand() % (length - 3) + 1);		//限定坐标范围
		food[count].pos_fy = (rand() % (width - 3) + 1);
		if (foodpos[food[count].pos_fx][food[count].pos_fy] != 0 || wall[food[count].pos_fx][food[count].pos_fy] == 1)	 //判断食物生成的位置是否重复或在墙上
			continue;
		for (int j = 0; j < bodysize; j++)							 //判断食物生成的位置是否在蛇身上
			if (food[count].pos_fx == snake[j].pos_x && food[count].pos_fy == snake[j].pos_y)
			{
				flag = 1;
				break;
			}
		if (!flag)										//适当位置标记食物生成成功
		{
			if (random >= 7)
				foodpos[food[count].pos_fx][food[count].pos_fy] = 2;
			else
				foodpos[food[count].pos_fx][food[count].pos_fy] = 1;
			flag = 0;
			count++;
		}
	}
}
void Snake::drawbadfood()
{
	for (int i = 0; i < badfoodmax; i++)								//画恶果
	{
		if (foodpos[badfood[i].pos_fx][badfood[i].pos_fy] == -1)
		{
			setfillcolor(GREEN);
			fillrectangle(badfood[i].pos_fx * unitsize, badfood[i].pos_fy * unitsize, badfood[i].pos_fx * unitsize + unitsize, badfood[i].pos_fy * unitsize + unitsize);
		}
	}
}
void Snake::createbadfood()
{
	int random = 0, count = 0,badfoodcounts=0;
	bool flag = 0;
	random = rand() % 3 + 1;
	count = badfoodcount;
	while (count-badfoodcount < random)
	{
		badfood[count].pos_fx = (rand() % (length - 3) + 1);		//限定坐标范围
		badfood[count].pos_fy = (rand() % (width - 3) + 1);
		if (foodpos[badfood[count].pos_fx][badfood[count].pos_fy] != 0 || wall[badfood[count].pos_fx][badfood[count].pos_fy] == 1)	 //判断食物生成的位置是否重复或在墙上
			continue;
		for (int j = 0; j < bodysize; j++)							 //判断食物生成的位置是否在蛇身上
			if (badfood[count].pos_fx == snake[j].pos_x && badfood[count].pos_fy == snake[j].pos_y)
			{
				flag = 1;
				break;
			}
		if ((badfood[count].pos_fy - snake[0].pos_y) * (badfood[count].pos_fy - snake[0].pos_y) + (badfood[count].pos_fx - snake[0].pos_x) * (badfood[count].pos_fx - snake[0].pos_x) < 36)	//恶果要距离蛇头远一些
		{
			flag = 0;
			continue;
		}
		if (!flag)										//适当位置标记食物生成成功
		{
			foodpos[badfood[count].pos_fx][badfood[count].pos_fy] = -1;
			count++;
			badfoodcounts++;
			flag = 0;
		}
	}
	badfoodcount += badfoodcounts;
}
void Snake::energydecrease()
{

	if (bodysize < 5)
		energy -= energyunit;
	if (bodysize >= 5 && bodysize < 10)
		energy = energy - energyunit*2;
	if (bodysize >= 10 && bodysize < 20)
		energy = energy - energyunit*3;
	if (bodysize >= 20 && bodysize < 30)
		energy = energy - energyunit*4;
	if (bodysize >= 30 && bodysize < 40)
		energy = energy - energyunit*5;
	if (bodysize >= 40 && bodysize < 50)
		energy = energy - energyunit*6;
	if (bodysize >= 50)
		energy = energy - energyunit*7;
}
void Snake::drawfoodmore()
{
	for (int i = 0; i < foodcount; i++)								//画食物
	{
		if (foodpos[food[i].pos_fx][food[i].pos_fy] == 1)
		{
			setfillcolor(RED);
			fillrectangle(food[i].pos_fx * unitsize, food[i].pos_fy * unitsize, food[i].pos_fx * unitsize + unitsize, food[i].pos_fy * unitsize + unitsize);
		}
		if (foodpos[food[i].pos_fx][food[i].pos_fy] == 2)
		{
			setfillcolor(BLUE);
			fillrectangle(food[i].pos_fx * unitsize, food[i].pos_fy * unitsize, food[i].pos_fx * unitsize + unitsize, food[i].pos_fy * unitsize + unitsize);
		}
		if (!goodfoodsymbol&& foodpos[goodfood.pos_fx][goodfood.pos_fy] == 3)
		{
			setfillcolor(RGB(241, 212, 232));
			fillrectangle(goodfood.pos_fx * unitsize, goodfood.pos_fy * unitsize, goodfood.pos_fx * unitsize + unitsize, goodfood.pos_fy * unitsize + unitsize);
		}
	}
}
void Snake::creategoodfood()
{
	bool flag = 0;
	while (1)
	{
		goodfood.pos_fx = (rand() % (length - 3) + 1);
		goodfood.pos_fy = (rand() % (width - 3) + 1);
		if (foodpos[goodfood.pos_fx][goodfood.pos_fy] != 0 || wall[goodfood.pos_fx][goodfood.pos_fy] == 1)	 //判断食物生成的位置是否重复或在墙上
			continue;
		for (int j = 0; j < bodysize; j++)							 //判断食物生成的位置是否在蛇身上
			if (goodfood.pos_fx == snake[j].pos_x && goodfood.pos_fy == snake[j].pos_y)
			{
				flag = 1;
				break;
			}
		if (!flag)										//适当位置标记食物生成成功
		{
			foodpos[goodfood.pos_fx][goodfood.pos_fy] = 3;
			goodfoodsymbol = 0;
			foodcount++;
			flag = 0;
			break;
		}
	}
	
}

//choice5	easyx插入图片版
void Snake::game5()
{
	loadimage(&img1, _T("../image/doge.png"), 20, 20);
	loadimage(&img2, _T("../image/bone.png"), 20, 20);
	loadimage(&img3, _T("../image/clear.png"), 20, 20);
	loadimage(&img4, _T("../image/wall.png"), 10, 10);
	drawpicturewall();
	init_snake();
	if (!readhistoryflag)
		create_food();
	while (1)
	{
		UIstate_show();
		if (foodcount == 0)
			create_food();
		if (foodcount > 0)
			drawbone();
		inputcheck();
		if (returnflag)
		{
			gameover();
			break;
		}
		move();
		snakestateset();
		drawdoge();
		if (snakedead())
		{
			gameover();
			break;
		}
		Sleep(speed);
	}
}
void Snake::drawdoge()
{
	putimage(tail.pos_x * unitsize, tail.pos_y * unitsize, &img3);
	for (int i = 0; i < bodysize; i++)														//画蛇
	{
		putimage(snake[i].pos_x * unitsize, snake[i].pos_y * unitsize, &img1); //snake[i].pos_x * unitsize + unitsize, snake[i].pos_y * unitsize + unitsize);
	}

}
void Snake::drawpicturewall()
{
	for (int i = 0; i < length + 2; i++)		//生成二维数组进行初始化	
		for (int j = 0; j < width + 2; j++)
		{
			wall[i][j] = 0;
		}
	for (int i = 0; i < length; i++)		//利用二维数组标记记录墙的位置并绘制
	{

		wall[i][0] = 1;
		wall[i][(width - 1)] = 1;
		setfillcolor(GREEN);
		putimage(i * unitsize, 0, &img4);
		putimage(i * unitsize, unitsize * (width - 1), &img4);
	}
	for (int i = 0; i < width; i++)
	{

		wall[0][i] = 1;
		wall[(length - 1)][i] = 1;
		putimage(0, i * unitsize, &img4);
		putimage((length - 1) * unitsize, unitsize * i, &img4);
	}

}
void Snake::drawbone()
{
	for (int i = 0; i < foodcount; i++)								//画食物
	{
		if (foodpos[food[i].pos_fx][food[i].pos_fy] == 1)
		{
			putimage(food[i].pos_fx * unitsize, food[i].pos_fy * unitsize, &img2);
		}
	}

}

//choice6	双人游戏
void Snake::game6()
{
	drawwall();
	init_2snake();
	create_food();
	while (1)
	{
		//UIstate_show();
		if (foodcount == 0)
			create_food();
		if (foodcount > 0)
			drawfood();
		tpcheck();
		if (returnflag)
		{
			gameover();
			break;
		}
		tpmove();
		tpdrawsnake();
		keepwallline();
		if (tpsnakedead())
		{
			gameover();
			break;
		}
		Sleep(beginspeed);
	}
}
void Snake::init_2snake()
{
	if (init_snakeflag)		//生成蛇头位置
	{
		while (1)
		{
			snake1[0].pos_x = (rand() % (length - 3) + 1);		//限定坐标范围
			snake1[0].pos_y = (rand() % (width - 3) + 1);
			snake2[0].pos_x = (rand() % (length - 3) + 1);		//限定坐标范围
			snake2[0].pos_y = (rand() % (width - 3) + 1);
			if (wall[snake1[0].pos_x][snake1[0].pos_y] == 1 || foodpos[snake1[0].pos_x][snake1[0].pos_x] == 1 || wall[snake2[0].pos_x][snake2[0].pos_y] == 1 || foodpos[snake2[0].pos_x][snake2[0].pos_x] == 1)	//是否生成在适当的位置，若没有则重新生成
				continue;
			if ((snake1[0].pos_x - snake2[0].pos_x) * (snake1[0].pos_x - snake2[0].pos_x) + (snake1[0].pos_y - snake2[0].pos_y) * (snake1[0].pos_y - snake2[0].pos_y) < 360)
				continue;
			break;
		}
		init_snakeflag = 0;
	}
	return;
}
void Snake::tpcheck()
{
	char inputc;
	while (_kbhit())	//是否有键盘输入
	{
		inputc = _getch();
		switch (inputc)	//改变方向，但不能回头反着走 wasd 上下左右
		{
			case 'W':
			case 'w':
				if (direction1 != down_)
					direction1 = up_;
				break;
			case 'A':
			case 'a':
				if (direction1 != right_)
					direction1 = left_;
				break;
			case 'S':
			case 's':
				if (direction1 != up_)
					direction1 = down_;
				break;
			case 'D':
			case 'd':
				if (direction1 != left_)
					direction1 = right_;
				break;
			case' ':
				_getch();
				break;
			case 'Q':
			case 'q':
				returnflag = 1;
				break;
			case -32:
				inputc = _getch();
				switch (inputc)
				{
					case 72:
						if (direction2 != down_)
							direction2 = up_;
						break;
					case 77:
						if (direction2 != left_)
							direction2 = right_;
						break;
					case 80:
						if (direction2 != up_)
							direction2 = down_;
						break;
					case 75:
						if (direction2 != right_)
							direction2 = left_;
						break;
				}
		}
	}
}
void Snake::tpmove()
{
	tail1.pos_x = snake1[bodysize1 - 1].pos_x;				//记录本次移动前的蛇尾坐标，之后在画蛇时移除
	tail1.pos_y = snake1[bodysize1 - 1].pos_y;
	tail2.pos_x = snake2[bodysize2 - 1].pos_x;				//记录本次移动前的蛇尾坐标，之后在画蛇时移除
	tail2.pos_y = snake2[bodysize2 - 1].pos_y;
	if (foodpos[snake1[0].pos_x][snake1[0].pos_y] != 0)	//吃到食物，体长+1，食物数量-1
	{
		bodysize1++;
		foodcount--;
		foodpos[snake1[0].pos_x][snake1[0].pos_y] = 0;
	}
	for (int i = bodysize1 - 1; i > 0; i--)				//坐标向前移动让蛇动起来
	{
		snake1[i].pos_x = snake1[i - 1].pos_x;
		snake1[i].pos_y = snake1[i - 1].pos_y;
	}
	if (foodpos[snake2[0].pos_x][snake2[0].pos_y] != 0)	//吃到食物，体长+1，食物数量-1
	{
		bodysize2++;
		foodcount--;
		foodpos[snake2[0].pos_x][snake2[0].pos_y] = 0;
	}
	for (int i = bodysize2 - 1; i > 0; i--)				//坐标向前移动让蛇动起来
	{
		snake2[i].pos_x = snake2[i - 1].pos_x;
		snake2[i].pos_y = snake2[i - 1].pos_y;
	}
	switch (direction1)									//移动方向，上下左右，分别对应进行蛇头方向变换
	{
		case up_:
			snake1[0].pos_y -= 1;
			break;
		case down_:
			snake1[0].pos_y += 1;
			break;
		case left_:
			snake1[0].pos_x -= 1;
			break;
		case right_:
			snake1[0].pos_x += 1;
			break;
	}
	switch (direction2)									//移动方向，上下左右，分别对应进行蛇头方向变换
	{
		case up_:
			snake2[0].pos_y -= 1;
			break;
		case down_:
			snake2[0].pos_y += 1;
			break;
		case left_:
			snake2[0].pos_x -= 1;
			break;
		case right_:
			snake2[0].pos_x += 1;
			break;
	}
}
void Snake::tpdrawsnake()
{
	clearrectangle(tail1.pos_x * unitsize, tail1.pos_y * unitsize, tail1.pos_x * unitsize + unitsize, tail1.pos_y * unitsize + unitsize);
	clearrectangle(tail2.pos_x * unitsize, tail2.pos_y * unitsize, tail2.pos_x * unitsize + unitsize, tail2.pos_y * unitsize + unitsize);
	for (int i = 0; i < bodysize1; i++)														//画蛇
	{
		switch (p1color)
		{
			case'A':
			case'a':
				setfillcolor(RGB(255, 192, 203));
				break;
			case'B':
			case'b':
				setfillcolor(RGB(30, 144, 255));
				break;
			case'C':
			case'c':
				setfillcolor(RGB(0, 255, 0));
				break;
			case'D':
			case'd':
				setfillcolor(RGB(255, 215, 0));
				break;
			case'E':
			case'e':
				setfillcolor(RGB(138, 43, 226));
				break;
			case'F':
			case'f':
				setfillcolor(RGB(0, 255, 255));
				break;
		}
		fillrectangle(snake1[i].pos_x * unitsize, snake1[i].pos_y * unitsize, snake1[i].pos_x * unitsize + unitsize, snake1[i].pos_y * unitsize + unitsize);
	}
	for (int j = 0; j < bodysize2; j++)														//画蛇
	{
		switch (p2color)
		{
			case'A':
			case'a':
				setfillcolor(RGB(255, 192, 203));
				break;
			case'B':
			case'b':
				setfillcolor(RGB(30, 144, 255));
				break;
			case'C':
			case'c':
				setfillcolor(RGB(0, 255, 0));
				break;
			case'D':
			case'd':
				setfillcolor(RGB(255, 215, 0));
				break;
			case'E':
			case'e':
				setfillcolor(RGB(138, 43, 226));
				break;
			case'F':
			case'f':
				setfillcolor(RGB(0, 255, 255));
				break;
		}
		fillrectangle(snake2[j].pos_x * unitsize, snake2[j].pos_y * unitsize, snake2[j].pos_x * unitsize + unitsize, snake2[j].pos_y * unitsize + unitsize);
	}
}
void Snake::colorsettp()
{
	int x, y;
	system("cls");
	cout << "请选择玩家1和玩家2蛇的颜色,输入A~F(A(红色),B(蓝色),C(绿色),D(黄色),E(紫色),F(青色)):" << endl;
	cout << "请选择p1的颜色: ";
	getxy(x, y);
	while (1)
	{
		cin >> p1color;
		if (!cin.good())
		{
			cout << "输入错误,请重新选择。" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			gotoxy(x, y);
			getxy(x, y);
			cout << "                                                                         ";
			gotoxy(x, y);
			continue;
		}
		if ((p1color < 'A' || p1color>'F'))
		{
			cout << "输入错误,请重新选择。" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			gotoxy(x, y);
			getxy(x, y);
			cout << "                                                                         ";
			gotoxy(x, y);
			continue;
		}
		cout << "\n设置成功!\n";
		cout << "请选择p2的颜色: ";
		getxy(x, y);
		while (1)
		{
			cin >> p2color;
			if (!cin.good())
			{
				cout << "输入错误,请重新选择。" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				gotoxy(x, y);
				getxy(x, y);
				cout << "                                                                         ";
				gotoxy(x, y);
				continue;
			}
			if ((p1color < 'A' || p1color>'F'))
			{
				cout << "输入错误,请重新选择。" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				gotoxy(x, y);
				getxy(x, y);
				cout << "                                                                         ";
				gotoxy(x, y);
				continue;
			}
			cout << "\n设置成功!\n";
			break;
		}
		break;
	}
	cout << "(按任意键开始游戏)";
	_getch();
}
bool Snake::tpsnakedead()
{
	if (snake1[0].pos_x == snake2[0].pos_x && snake1[0].pos_y == snake2[0].pos_y)
		return 1;
	if (wall[snake1[0].pos_x][snake1[0].pos_y] == 1 && wall[snake2[0].pos_x][snake2[0].pos_y] != 1)
	{
		p2win = 1;
		return 1;
	}
	if (wall[snake1[0].pos_x][snake1[0].pos_y] != 1 && wall[snake2[0].pos_x][snake2[0].pos_y] == 1)
	{
		p1win = 1;
		return 1;
	}
	if (wall[snake1[0].pos_x][snake1[0].pos_y] == 1 && wall[snake2[0].pos_x][snake2[0].pos_y] == 1)
		return 1;
	for (int i = 1; i < bodysize1; i++)
		if (snake1[0].pos_x == snake1[i].pos_x && snake1[0].pos_y == snake1[i].pos_y)	//被自己撞死
		{
			p2win = 1;
			return 1;
		}
	for (int i = 1; i < bodysize2; i++)
		if (snake2[0].pos_x == snake2[i].pos_x && snake2[0].pos_y == snake2[i].pos_y)	//被自己撞死
		{
			p1win = 1;
			return 1;
		}
	for (int i = 1; i < bodysize2; i++)
		if (snake1[0].pos_x == snake2[i].pos_x && snake1[0].pos_y == snake2[i].pos_y)	//撞到对方蛇身
		{
			p2win = 1;
			return 1;
		}
	for (int i = 1; i < bodysize1; i++)
		if (snake2[0].pos_x == snake1[i].pos_x && snake2[0].pos_y == snake1[i].pos_y)	//撞到对方蛇身
		{
			p1win = 1;
			return 1;
		}
	return 0;
}
