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
#include<math.h>
using namespace std;
#define length 60 /*总是莫名其妙没有声明这些量但程序还能运行还是copy过来了*/
#define width 60
#define Maxbodysize (length-1)*(width-1)
#define unitsize 10
#define foods 30
#define UIheight (width+1)*unitsize
#define hardlevel 5
#define speedunit 10
#define beginspeed 120
#define normalfoodscore 10
#define beginenergy 500
#define energyunit 0.1
#define badfoodmax 15

/*负责游戏界面的class成员函数*/

//地图边框绘制
void Snake::drawwall()
{
	if (startflag)
	{
		for (int i = 0; i < length + 2; i++)		//生成二维数组进行初始化	
			for (int j = 0; j < width + 2; j++)
			{
				wall[i][j] = 0;
			}
	}
	for (int i = 0; i < length; i++)		//利用二维数组标记记录墙的位置并绘制
	{

		wall[i][0] = 1;
		wall[i][(width - 1)] = 1;
		setfillcolor(GREEN);
		fillrectangle(i * unitsize, 0, i * unitsize + unitsize, unitsize);
		fillrectangle(i * unitsize, unitsize * (width - 1), i * unitsize + unitsize, width * unitsize);
	}
	for (int i = 0; i < width; i++)
	{
		wall[0][i] = 1;
		wall[(length - 1)][i] = 1;
		fillrectangle(0, i * unitsize, unitsize, i * unitsize + unitsize);
		fillrectangle((length - 1) * unitsize, unitsize * i, length * unitsize, unitsize * i + unitsize);
	}

}
//防止蛇贴着边界走抹掉边界的线
void Snake::keepwallline()
{
	line(unitsize, unitsize, unitsize, unitsize * (width - 1));
	line(unitsize, unitsize, (length - 1) * unitsize, unitsize);
	line((length - 1) * unitsize, unitsize, (length - 1) * unitsize, unitsize * (width - 1));
	line(unitsize, unitsize * (width - 1), (length - 1) * unitsize, unitsize * (width - 1));
}

//生成食物
void Snake::drawwall2()
{
	for (int i = 1; i < length + 2; i++)		//生成二维数组进行初始化	
		for (int j = 1; j < width + 1; j++)
		{
			if (wall[i][j] == 1)
				fillrectangle(i * unitsize, j * unitsize, i * unitsize + unitsize, j * unitsize + unitsize);
		}
}
void Snake::create_food()
{
	int count = 0;
	bool flag = 0;

	if (foodcount == 0)
		foodcount = rand() % 5 + 1;					//生成1-5个食物
	if (choice == 6 && foodcount == 0)
		foodcount = rand() % 15 + 1;
	if (startflag)
	{
		for (int i = 0; i < (length + 1); i++)			//初始化二维数组用来记录食物的位置
			for (int j = 0; j < (width + 1); j++)
				foodpos[i][j] = 0;
	}
	while (count < foodcount)
	{
		food[count].pos_fx = (rand() % (length - 3) + 1);		//限定坐标范围
		food[count].pos_fy = (rand() % (width - 3) + 1);
		if (foodpos[food[count].pos_fx][food[count].pos_fy] == 1 || wall[food[count].pos_fx][food[count].pos_fy] == 1)	 //判断食物生成的位置是否重复或在墙上
			continue;
		for (int j = 0; j < bodysize; j++)							 //判断食物生成的位置是否在蛇身上
			if (food[count].pos_fx == snake[j].pos_x && food[count].pos_fy == snake[j].pos_y)
			{
				flag = 1;
				break;
			}
		if (!flag)										//适当位置标记食物生成成功
		{
			foodpos[food[count].pos_fx][food[count].pos_fy] = 1;
			flag = 0;
			count++;
		}
	}

}

//初始化生成蛇
void Snake::init_snake()
{
	if (init_snakeflag)		//生成蛇头位置
	{
		while (1)
		{
			snake[0].pos_x = (rand() % (length - 3) + 1);		//限定坐标范围
			snake[0].pos_y = (rand() % (width - 3) + 1);
			if (wall[snake[0].pos_x][snake[0].pos_y] == 1 || foodpos[snake[0].pos_x][snake[0].pos_x] == 1)	//是否生成在适当的位置，若没有则重新生成
				continue;
			break;
		}
		init_snakeflag = 0;
	}
	return;
}

//画蛇
void Snake::drawsnake()
{
	clearrectangle(tail.pos_x * unitsize, tail.pos_y * unitsize, tail.pos_x * unitsize + unitsize, tail.pos_y * unitsize + unitsize);	//去掉之前的蛇尾使蛇不变长地移动
	for (int i = 0; i < bodysize; i++)														//画蛇
	{
		fillrectangle(snake[i].pos_x * unitsize, snake[i].pos_y * unitsize, snake[i].pos_x * unitsize + unitsize, snake[i].pos_y * unitsize + unitsize);
	}
}

//画食物
void Snake::drawfood()
{
	for (int i = 0; i < foods; i++)								//画食物
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
	}
}

//蛇的移动状态
void Snake::move()
{

	tail.pos_x = snake[bodysize - 1].pos_x;				//记录本次移动前的蛇尾坐标，之后在画蛇时移除
	tail.pos_y = snake[bodysize - 1].pos_y;
	if (foodpos[snake[0].pos_x][snake[0].pos_y] != 0)	//吃到食物，体长+1，食物数量-1
	{
		if (choice == 4 && foodpos[snake[0].pos_x][snake[0].pos_y] == -1)
		{
			return;
		}
		bodysize++;
		foodcount--;
		if (choice != 4)
			score += normalfoodscore;
		if (choice == 4)
		{
			if (foodpos[snake[0].pos_x][snake[0].pos_y] == 1)
			{
				energy += 2;
				score += normalfoodscore;
			}
			if (foodpos[snake[0].pos_x][snake[0].pos_y] == 2)
			{
				energy += 4;
				score += normalfoodscore * 2;
			}
			if (foodpos[snake[0].pos_x][snake[0].pos_y] == 3)
			{
				energy = beginenergy;
				score += normalfoodscore * 4;
				goodfoodsymbol = 1;
			}
		}
		foodpos[snake[0].pos_x][snake[0].pos_y] = 0;	//将食物从地图上清除
	}
	for (int i = bodysize - 1; i > 0; i--)				//坐标向前移动让蛇动起来
	{
		snake[i].pos_x = snake[i - 1].pos_x;
		snake[i].pos_y = snake[i - 1].pos_y;
	}
	switch (direction)									//移动方向，上下左右，分别对应进行蛇头方向变换
	{
		case up_:
			snake[0].pos_y -= 1;
			break;
		case down_:
			snake[0].pos_y += 1;
			break;
		case left_:
			snake[0].pos_x -= 1;
			break;
		case right_:
			snake[0].pos_x += 1;
			break;
	}
}

//键盘输入的检测 读取键盘输入
void Snake::inputcheck()
{
	char inputc;
	while (_kbhit())	//是否有键盘输入
	{
		inputc = _getch();
		switch (inputc)	//改变方向，但不能回头反着走 wasd 上下左右
		{
			case 'W':
			case 'w':
				if (direction != down_)
					direction = up_;
				break;
			case 'A':
			case 'a':
				if (direction != right_)
					direction = left_;
				break;
			case 'S':
			case 's':
				if (direction != up_)
					direction = down_;
				break;
			case 'D':
			case 'd':
				if (direction != left_)
					direction = right_;
				break;
			case ' ':
				_getch();
				break;
			case 'Q':
			case 'q':
				returnflag = 1;
				break;
			case 'o':
			case 'O':
				char qo;
				outtextxy(0, UIheight + 16 * unitsize, _T("是否存档保存本次游戏进度并退出？(会覆盖之前一次的存档) 按  Y  选择确定 按  N  选择否 "));
				while ((qo = _getch()) != '\n')
				{
					if (qo == 'y' || qo == 'Y')
					{
						startclock = 0;
						startflag = 0;
						sec = sec + time(0) - start_time;
						preservehistory();
						returnflag = 1;
						break;
					}
					if (qo == 'n' || qo == 'N')
						break;
				}
				outtextxy(0, UIheight + 16 * unitsize, _T("按任意键继续                                                                                                                                                     "));
				_getch();
				break;
			case -32:
				inputc = _getch();
				switch (inputc)
				{
					case 72:
						if (direction != down_)
							direction = up_;
						break;
					case 77:
						if (direction != left_)
							direction = right_;
						break;
					case 80:
						if (direction != up_)
							direction = down_;
						break;
					case 75:
						if (direction != right_)
							direction = left_;
						break;
				}
		}
	}
}

//判断蛇是不是没了
bool Snake::snakedead()
{
	if (wall[snake[0].pos_x][snake[0].pos_y] == 1)		//撞墙死
	{
		if (choice == 2 || choice == 3)
		{
			setfillcolor(GREEN);
			fillrectangle(snake[0].pos_x * unitsize, snake[0].pos_y * unitsize, snake[0].pos_x * unitsize + unitsize, snake[0].pos_y * unitsize + unitsize);
			for (int i = 0; i < bodysize - 1; i++)				//还原蛇死之前的状态
			{
				snake[i].pos_x = snake[i + 1].pos_x;
				snake[i].pos_y = snake[i + 1].pos_y;
			}
			snake[bodysize - 1] = tail;
		}
		return 1;
	}
	for (int i = 1; i < bodysize; i++)
		if (snake[0].pos_x == snake[i].pos_x && snake[0].pos_y == snake[i].pos_y)	//被自己撞死
		{
			if (choice == 2 || choice == 3)
			{
				if (choice == 2)
					setfillcolor(GREEN);
				if (choice == 3)
					setfillcolor(RED);
				fillrectangle(snake[0].pos_x * unitsize, snake[0].pos_y * unitsize, snake[0].pos_x * unitsize + unitsize, snake[0].pos_y * unitsize + unitsize);
				for (int i = 0; i < bodysize - 1; i++)				//还原蛇死之前的状态
				{
					snake[i].pos_x = snake[i + 1].pos_x;
					snake[i].pos_y = snake[i + 1].pos_y;
				}
				snake[bodysize - 1] = tail;
			}
			return 1;
		}
	if (choice == 4 && foodpos[snake[0].pos_x][snake[0].pos_y] == -1)
		return 1;
	if (choice == 4 && energy < 0)
		return 1;
	return 0;
}
//改变蛇的属性 速度，颜色
void Snake::snakestateset()
{
	if (bodysize < 5)
	{
		setfillcolor(RGB(255, 215, 0));//MAGENTA);
		speed = beginspeed - speedunit;
	}
	if (bodysize >= 5 && bodysize < 10)
	{
		setfillcolor(CYAN);
		speed = beginspeed - speedunit;
	}
	if (bodysize >= 10 && bodysize < 20)
	{
		setfillcolor(GREEN);
		speed = beginspeed - 2 * speedunit;
	}
	if (bodysize >= 20 && bodysize < 30)
	{
		setfillcolor(LIGHTCYAN);
		speed = beginspeed - 3 * speedunit;
	}
	if (bodysize >= 30 && bodysize < 40)
	{
		setfillcolor(LIGHTBLUE);
		speed = beginspeed - 4 * speedunit;
	}
	if (bodysize >= 40 && bodysize < 50)
	{
		setfillcolor(LIGHTMAGENTA);
		speed = beginspeed - 5 * speedunit;
	}
	if (bodysize >= 50)
	{
		setfillcolor(RGB(255, 215, 0));
		speed = beginspeed - 10 * speedunit;
	}
}
//UI显示
void Snake::UIstate_show()
{
	if (!startclock)				//记录游戏开始时间
	{
		start_time = time(0);
		startclock = 1;
	}
	now_time = time(0);		//记录游戏当前时间
	settextcolor(WHITE);	//UI输出
	outtextxy(0, UIheight + 14 * unitsize, _T("按空格键可暂停游戏再次按空格键可继续游戏，按q键退出本次游戏，按o选择是否存档"));
	outtextxy(0, UIheight, _T("游戏时间为: "));
	outtextxy(0, UIheight + 16 * unitsize, _T("                                                                                                                              "));
	TCHAR s[10];
	if (readhistoryflag)
		_stprintf(s, _T("%lld%c%lld%c%c"), ((sec + now_time - start_time) / 60), ':', (sec + now_time - start_time) % 60, ' ', ' '); //显示时间转换成s为单位
	else
		_stprintf(s, _T("%lld%c%lld%c%c"), (now_time - start_time) / 60, ':', (now_time - start_time) % 60, ' ', ' '); //显示时间转换成s为单位
	outtextxy(9 * unitsize, UIheight, s);
	if (choice != 6)
	{
		if (choice == 5)
			outtextxy(0, UIheight + 3 * unitsize, _T("吃到的骨头数量为: "));
		else
			outtextxy(0, UIheight + 3 * unitsize, _T("当前分数为: "));
	}
	TCHAR s1[10];
	if (choice == 5)
		_stprintf(s1, _T("%d"), score / 10);
	else
		_stprintf(s1, _T("%d"), score);
	if (choice == 5)
		outtextxy(14 * unitsize, UIheight + 3 * unitsize, s1);
	else
		outtextxy(9 * unitsize, UIheight + 3 * unitsize, s1);
	if (choice != 5)
		outtextxy(0, UIheight + 6 * unitsize, _T("历史最高得分: "));
	TCHAR s2[10];
	if (choice == 1)
	{
		if (score > historybestscore[1])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("新纪录诞生!"));
			historybestscore[1] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[1]);
	}
	if (choice == 2)
	{
		if (score > historybestscore[2])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("新纪录诞生!"));
			historybestscore[2] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[2]);
	}
	if (choice == 3)
	{
		if (score > historybestscore[3])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("新纪录诞生!"));
			historybestscore[3] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[3]);
	}
	if (choice == 4)
	{
		if (score > historybestscore[4])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("新纪录诞生!"));
			historybestscore[4] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[4]);
	}
	if (choice != 5 && choice != 6)
		outtextxy(12 * unitsize, UIheight + 6 * unitsize, s2);
	if (choice == 5)
		outtextxy(0, UIheight + 9 * unitsize, _T("当前狗头数量为: "));
	if (choice <= 4 && choice >= 1)
		outtextxy(0, UIheight + 9 * unitsize, _T("蛇的长度: "));
	TCHAR s3[10];
	_stprintf(s3, _T("%d"), bodysize);
	if (choice == 5)
		outtextxy(12 * unitsize, UIheight + 9 * unitsize, s3);
	else
		outtextxy(9 * unitsize, UIheight + 9 * unitsize, s3);
	if (choice == 3)
	{
		outtextxy(0, UIheight + 12 * unitsize, _T("蛇剩余的生命数: "));
		TCHAR s4[10];
		_stprintf(s4, _T("%d"), life);
		outtextxy(12 * unitsize, UIheight + 12 * unitsize, s4);
	}
	if (choice == 4)
	{
		outtextxy(0, UIheight + 12 * unitsize, _T("当前体能: "));
		if (energy > beginenergy * 3 / 4)
			setfillcolor(GREEN);
		if (energy< beginenergy * 3 / 4 && energy>beginenergy / 4)
			setfillcolor(YELLOW);
		if (energy < beginenergy / 4 && energy>0)
			setfillcolor(RED);
		if (int(fabs((unitsize * 6 + energy)))>=unitsize*10)
		{
			clearrectangle(unitsize * 8, UIheight + 12 * unitsize, unitsize * 6 + 1000, UIheight + 13 * unitsize);
			solidrectangle(unitsize * 10, UIheight + 12 * unitsize, int(fabs((unitsize * 6 + energy))), UIheight + 13 * unitsize);
		}
	}
}
//游戏结束画面
void Snake::gameover()
{
	cleardevice();
	if (prehistoryflag)
	{
		outtextxy(0, 0, _T("存档成功!可按任意键返回菜单"));
	}
	else
	{
		if (choice <= 4)
		{
			outtextxy(0, 0, _T("游戏结束,可按任意键返回菜单"));
			outtextxy(0, 3 * unitsize, _T("本次最终分数为: "));
			TCHAR s1[10];
			_stprintf(s1, _T("%d"), score);
			outtextxy(12 * unitsize, 3 * unitsize, s1);
			outtextxy(0, 6 * unitsize, _T("本模式历史最高得分为:"));
			TCHAR s2[10];
			_stprintf(s2, _T("%d"), historybestscore[choice]);
			outtextxy(16 * unitsize, 6 * unitsize, s2);
		}
		if (choice == 5)
			outtextxy(0, 0, _T("游戏结束,可按任意键返回菜单(doge)"));
		if (choice == 6)
		{
			if (p1win)
				outtextxy(0, 0, _T("游戏结束,玩家1获得胜利!可按任意键返回菜单"));
			else if (p2win)
				outtextxy(0, 0, _T("游戏结束,玩家2获得胜利!可按任意键返回菜单"));
			else
				outtextxy(0, 0, _T("游戏结束,可按任意键返回菜单"));
		}
	}
	choice = 0;
	bodysize = 1;
	bodysize1 = 1, bodysize2 = 1;
	score = 0;
	speed = beginspeed;
	life = 5;
	foodcount = 0;
	init_snakeflag = 1;
	badfoodcount = 0;
	goodfoodsymbol = 1;
	startflag = 1;
	startclock = 0;
	energy = beginenergy;
	returnflag = 0;
	p1win = p2win = 0;
	readhistoryflag = 0;
	prehistoryflag = 0;
	strcpy(playername, "snake");
	_getch();
	closegraph();
	return;
}

//不同游戏模式
//choice1	经典版
void Snake::game1()
{
	bool stayflag = 1;
	historyrecordread();
	drawwall();
	init_snake();
	if (!readhistoryflag)
	{
		sec = 0;
		create_food();
	}
	while (1)
	{

		if (foodcount == 0)
			create_food();
		if (foodcount > 0)
			drawfood();
		inputcheck();
		if (returnflag)
		{
			historyrecordwrite();
			gameover();
			break;
		}
		move();
		snakestateset();
		drawsnake();
		if (readhistoryflag && stayflag)
		{
			outtextxy(0, UIheight + 16 * unitsize, _T("准备好按任意键开始"));
			_getch();
			outtextxy(0, UIheight + 16 * unitsize, _T("                                                                 "));
			stayflag = 0;
		}
		keepwallline();
		if (snakedead())
		{
			historyrecordwrite();
			gameover();
			break;
		}
		UIstate_show();
		Sleep(speed);
	}
}

//choice2	进阶版
void Snake::game2()
{
	historyrecordread();
	drawwall();
	init_snake();
	if (!readhistoryflag)
	{
		sec = 0;
		create_food();
	}
	if (readhistoryflag)
		drawwall2();
	while (1)
	{
		UIstate_show();
		if (snakedead())
		{
			if (havespace())
			{
				afterdeath_wall();
				init_snake();
			}
			else
			{
				historyrecordwrite();
				gameover();
				break;
			}
		}
		if (foodcount == 0)
			create_food();
		if (foodcount > 0)
			drawfood();
		snakestateset();
		inputcheck();
		keepwallline();
		if (returnflag)
		{
			historyrecordwrite();
			gameover();
			break;
		}
		move();
		drawsnake();
		Sleep(speed);
	}
}
//choice2死后生成墙
void Snake::afterdeath_wall()
{
	for (int i = 0; i < bodysize; i++)
	{
		wall[snake[i].pos_x][snake[i].pos_y] = 1;
		setfillcolor(GREEN);
		fillrectangle(snake[i].pos_x * unitsize, snake[i].pos_y * unitsize, snake[i].pos_x * unitsize + unitsize, snake[i].pos_y * unitsize + unitsize);
		snake[i].pos_x = length + 1;		//防止因蛇的移动将新生成的墙抹去
		snake[i].pos_y = width + 1;
	}
	init_snakeflag = 1;
	bodysize = 1;
}
//choice2、3死后是否还有空间
bool Snake::havespace()
{
	for (int i = 1; i < (length - 1); i++)
		for (int j = 1; j < (width - 1); j++)
			if (wall[i][j] == 0 || foodpos[i][j] == 0)
			{
				return 1;
			}
	return 0;
}


//choice3	高级版
void Snake::game3()
{
	historyrecordread();
	drawwall();
	init_snake();
	if (!readhistoryflag)
	{
		sec = 0;
		create_food();
	}
	while (1)
	{
		UIstate_show();
		if (snakedead())
		{
			life--;
			if (life == 0 || !havespace())
			{
				historyrecordwrite();
				gameover();
				break;
			}
			afterdeath_food();
			init_snake();
		}
		if (foodcount == 0)
			create_food();
		if (foodcount > 0)
			drawfood();
		snakestateset();
		inputcheck();
		keepwallline();
		if (returnflag)
		{
			historyrecordwrite();
			gameover();
			break;
		}
		move();
		drawsnake();
		Sleep(speed);
	}
}
//choice3死后变成食物
void Snake::afterdeath_food()
{
	for (int i = 0; i < bodysize; i++)
	{
		foodpos[snake[i].pos_x][snake[i].pos_y] = 1;
		food[foodcount + i].pos_fx = snake[i].pos_x;
		food[foodcount + i].pos_fy = snake[i].pos_y;
		snake[i].pos_x = length + 1;		//防止因蛇的移动将食物抹去
		snake[i].pos_y = width + 1;
	}
	foodcount += bodysize;
	init_snakeflag = 1;
	bodysize = 1;
}
