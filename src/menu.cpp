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

//与菜单相关的函数

/*使菜单界面输入规范、进行交互的辅助函数*/
void gotoxy(const int X, const int Y)
{
	const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(__hout, coord);
}
void getxy(int& x, int& y)
{
	const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(__hout, &binfo);
	x = binfo.dwCursorPosition.X;
	y = binfo.dwCursorPosition.Y;
	return;
}

/*界面相关函数*/
void Snake::menu()
{
	if (choice != 0)
		return;
	if (choice == 0)
	{
		system("cls");
		int x, y;
		cout << "=================贪吃蛇大作战=================" << endl;
		cout << "1.入门版0v0" << endl;
		cout << "2.进阶版^0^" << endl;
		cout << "3.高级版0+0" << endl;
		cout << "4.趣味规则版0o0" << endl;
		cout << "5.图片版" << endl;
		cout << "6.双人模式" << endl;
		cout << "7.历史记录显示" << endl;
		cout << "8.历史记录删除" << endl;
		cout << "9.根据游戏者昵称查找历史记录" << endl;
		cout << "10.修改历史记录中的游戏者昵称" << endl;
		cout << "11.存档读取" << endl;
		cout << "(输入-1可以退出程序)" << endl;
		cout << "==============================================" << endl;
		cout << "请选择(键盘输入1~9)：" << endl;
		getxy(x, y);
		while (1)
		{
			cin >> choice;
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				gotoxy(x, y);
				getxy(x, y);
				cout << "                                                                         ";
				gotoxy(x, y);
			}
			if ((choice < 1 || choice>11) && choice != -1)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				gotoxy(x, y);
				getxy(x, y);
				cout << "                                                                         ";
				gotoxy(x, y);
			}
			if ((choice >= 1 && choice <= 11) || choice == -1)
				break;
		}
		if (choice == 1)
		{
			system("cls");
			cout << "游戏规则：玩家控制方向键或w、a、s、d来控制小蛇的前进方向\n使蛇吃掉面板上随机位置上的食物（位置随机，数量为1-5随机）。" << endl
				<< "\n每次成功吃掉食物后小蛇体长将增加一点，得分增加。\n蛇的颜色和移动速度随着蛇长改变\n食物吃光则再次随机产生。" << endl
				<< "\n当小蛇撞到边界或者蛇头与蛇身相撞时，蛇将挂掉，游戏结束。" << endl << "按键说明: w/↑ 向上 a/← 向左 s/↓ 向下 d/→ 向右" <<
				"(按任意键继续...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 2)
		{
			system("cls");
			cout << "游戏规则：玩家控制方向键或w、a、s、d来控制小蛇的前进方向\n使蛇吃掉面板上随机位置上的食物（位置随机，数量为1-5随机）。" << endl
				<< "每次成功吃掉食物后小蛇体长将增加一点，得分增加。\n蛇的颜色和移动速度随着蛇长改变\n食物吃光则再次随机产生。" << endl
				<< "当小蛇撞到边界或者蛇头与蛇身相撞时，蛇将挂掉。" << endl <<
				"蛇挂掉后，此时蛇尸身改变显示颜色变成边界，再随机产生新的食物和蛇，游戏继续。直到剩余空间不足以生成新的蛇和食物为止" << endl << "按键说明: w 向上 a 向左 s 向下 d 向右" <<
				"(按任意键继续...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 3)
		{
			system("cls");
			cout << "游戏规则：玩家控制方向键或w、a、s、d来控制小蛇的前进方向\n使蛇吃掉面板上随机位置上的食物（位置随机，数量为1-5随机）。" << endl
				<< "\n每次成功吃掉食物后小蛇体长将增加一点，得分增加。\n蛇的颜色和移动速度随着蛇长改变\n食物吃光则再次随机产生。" << endl
				<< "当小蛇撞到边界或者蛇头与蛇身相撞时，蛇将挂掉。" << endl <<
				"蛇挂掉后，蛇的生命数会减一，此时蛇尸身改变显示颜色变成食物，再随机产生新的食物和蛇，游戏继续。" << endl
				<< "直到蛇生命数变为0，游戏结束" << endl << "按键说明: w/↑ 向上 a/← 向左 s/↓ 向下 d/→ 向右" <<
				"(按任意键继续...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 4)
		{
			system("cls");
			cout << "游戏规则：玩家控制方向键或w、a、s、d来控制小蛇的前进方向\n" << "蛇拥有一个体能槽，蛇的体能会根据蛇的长度以不同快慢的速度衰减，当蛇的体能衰减到0游戏结束\n"
				<< "\n本模式食物出现的会更多!食物介绍，在地图上会随机出现的不同的食物，有绿色，红色，蓝色，粉色四种\n其中绿色食物蛇吃了将会挂掉，而红色、蓝色、粉色食物可以增加蛇的体能，长度和分数\n蛇的颜色和移动速度随着蛇长改变" <<
				"\n蓝色食物的体能恢复量和分数高于红色食物，粉色食物蛇吃掉后将会恢复所有体能。" << endl
				<< "红、蓝、粉三种食物吃光会再次随机产生，绿色食物也会随机出现（但绿色食物并不会一直出现其数量存在上限）。" << endl
				<< "当小蛇体能为0或者吃到绿色食物或者撞到边界或者蛇头与蛇身相撞时，蛇将挂掉。" << endl <<
				endl << "（按键说明: w/↑ 向上 a/← 向左 s/↓ 向下 d/→ 向右）" <<
				"(按任意键继续...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 5)
		{
			system("cls");
			cout << "贪吃蛇有一个好朋友，而它的这个好朋友也是我们的好朋友，大家都很喜欢它\n有一天贪吃蛇做了一个梦，" <<
				"梦到自己变成了好朋友的模样\n它发现梦境里自己的身边有好多好多好朋友喜欢吃的食物\n它的潜意识里产生了要吃光所有这些食物的想法，它的身体又不由自主地动了起来..." << endl
				<< "(按任意键继续...)";
			_getch();
			system("cls");
			cout << "按键说明: w/↑ 向上 a/← 向左 s/↓ 向下 d/→ 向右,经典版规则(doge)";
			"(按任意键开始游戏...)";
			_getch();
		}
		if (choice == 6)
		{
			system("cls");
			cout << "说明:双人模式，玩家1和玩家2分别通过w,a,s,d键和↑、←、↓、→键实现蛇上、左、下、右的移动\n吃食物让自己控制的蛇身增长\n"
				<< "如果一名玩家的控制的蛇头撞到了另一名玩家的蛇身，则另一名玩家获得了胜利。\n如果吃掉食物体长大于等于2后双方蛇头相撞或同时撞到了墙壁则为平局\n";
			cout << "（按任意键继续...）" << endl;
			_getch();
			colorsettp();
			system("cls");
		}
		if (choice == -1)
		{
			system("cls");
			return;
		}
	}
}
void Snake::setname()
{
	int x, y;
	cout << "蛇有一个默认名字snake,当然你也可以选择为蛇起一个名字(二十个字符以内)" << endl << "(是否要起一个新的名字,若是请输入y|Y，若否请输入n|N并进入游戏) \n";
	char choiceyorn;
	char ch;
	bool flag = 0;
	getxy(x, y);
	while (1)
	{
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
			break;
		if (ch == 'n' || ch == 'N')
			return;
		else
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "\n输入错误,请重新输入。";
			cout << "                                   ";
			gotoxy(x, y);
		}
	}
	while (1)
	{
		cout << endl << endl << "请输入自定义名字:     ";
		getxy(x, y);
		cin >> playername;
		if (int(strlen(playername)) > 20)
		{
			cout << "用户名长度超出范围,请重新输入";
			gotoxy(x, y);
			cout << "                                                                   ";
			gotoxy(x, y);
			continue;
		}
		while (1)
		{
			cout << endl << endl << "确定使用该名字吗? （输入 y || Y 确定并进入游戏，或输入 n || N 重新选择）: ";
			getxy(x, y);
			cin >> choiceyorn;
			if (choiceyorn == 'y' || choiceyorn == 'Y')
				break;
			if (choiceyorn == 'n' || choiceyorn == 'N')
			{
				flag = 1;
				break;
			}
			else
			{
				cout << "\n输入错误,请重新输入。";
				gotoxy(x, y);
				cout << "                                   ";
				gotoxy(x, y);
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
		}
		if (flag)
		{
			flag = 0;
			continue;
		}
		break;
	}
}
int Snake::getchoice()  //获知当前的选择模式
{
	return choice;
}