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
#define length 60 /*����Ī������û��������Щ�������������л���copy������*/
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

/*������Ϸ�����class��Ա����*/

//��ͼ�߿����
void Snake::drawwall()
{
	if (startflag)
	{
		for (int i = 0; i < length + 2; i++)		//���ɶ�ά������г�ʼ��	
			for (int j = 0; j < width + 2; j++)
			{
				wall[i][j] = 0;
			}
	}
	for (int i = 0; i < length; i++)		//���ö�ά�����Ǽ�¼ǽ��λ�ò�����
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
//��ֹ�����ű߽���Ĩ���߽����
void Snake::keepwallline()
{
	line(unitsize, unitsize, unitsize, unitsize * (width - 1));
	line(unitsize, unitsize, (length - 1) * unitsize, unitsize);
	line((length - 1) * unitsize, unitsize, (length - 1) * unitsize, unitsize * (width - 1));
	line(unitsize, unitsize * (width - 1), (length - 1) * unitsize, unitsize * (width - 1));
}

//����ʳ��
void Snake::drawwall2()
{
	for (int i = 1; i < length + 2; i++)		//���ɶ�ά������г�ʼ��	
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
		foodcount = rand() % 5 + 1;					//����1-5��ʳ��
	if (choice == 6 && foodcount == 0)
		foodcount = rand() % 15 + 1;
	if (startflag)
	{
		for (int i = 0; i < (length + 1); i++)			//��ʼ����ά����������¼ʳ���λ��
			for (int j = 0; j < (width + 1); j++)
				foodpos[i][j] = 0;
	}
	while (count < foodcount)
	{
		food[count].pos_fx = (rand() % (length - 3) + 1);		//�޶����귶Χ
		food[count].pos_fy = (rand() % (width - 3) + 1);
		if (foodpos[food[count].pos_fx][food[count].pos_fy] == 1 || wall[food[count].pos_fx][food[count].pos_fy] == 1)	 //�ж�ʳ�����ɵ�λ���Ƿ��ظ�����ǽ��
			continue;
		for (int j = 0; j < bodysize; j++)							 //�ж�ʳ�����ɵ�λ���Ƿ���������
			if (food[count].pos_fx == snake[j].pos_x && food[count].pos_fy == snake[j].pos_y)
			{
				flag = 1;
				break;
			}
		if (!flag)										//�ʵ�λ�ñ��ʳ�����ɳɹ�
		{
			foodpos[food[count].pos_fx][food[count].pos_fy] = 1;
			flag = 0;
			count++;
		}
	}

}

//��ʼ��������
void Snake::init_snake()
{
	if (init_snakeflag)		//������ͷλ��
	{
		while (1)
		{
			snake[0].pos_x = (rand() % (length - 3) + 1);		//�޶����귶Χ
			snake[0].pos_y = (rand() % (width - 3) + 1);
			if (wall[snake[0].pos_x][snake[0].pos_y] == 1 || foodpos[snake[0].pos_x][snake[0].pos_x] == 1)	//�Ƿ��������ʵ���λ�ã���û������������
				continue;
			break;
		}
		init_snakeflag = 0;
	}
	return;
}

//����
void Snake::drawsnake()
{
	clearrectangle(tail.pos_x * unitsize, tail.pos_y * unitsize, tail.pos_x * unitsize + unitsize, tail.pos_y * unitsize + unitsize);	//ȥ��֮ǰ����βʹ�߲��䳤���ƶ�
	for (int i = 0; i < bodysize; i++)														//����
	{
		fillrectangle(snake[i].pos_x * unitsize, snake[i].pos_y * unitsize, snake[i].pos_x * unitsize + unitsize, snake[i].pos_y * unitsize + unitsize);
	}
}

//��ʳ��
void Snake::drawfood()
{
	for (int i = 0; i < foods; i++)								//��ʳ��
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

//�ߵ��ƶ�״̬
void Snake::move()
{

	tail.pos_x = snake[bodysize - 1].pos_x;				//��¼�����ƶ�ǰ����β���֮꣬���ڻ���ʱ�Ƴ�
	tail.pos_y = snake[bodysize - 1].pos_y;
	if (foodpos[snake[0].pos_x][snake[0].pos_y] != 0)	//�Ե�ʳ��峤+1��ʳ������-1
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
		foodpos[snake[0].pos_x][snake[0].pos_y] = 0;	//��ʳ��ӵ�ͼ�����
	}
	for (int i = bodysize - 1; i > 0; i--)				//������ǰ�ƶ����߶�����
	{
		snake[i].pos_x = snake[i - 1].pos_x;
		snake[i].pos_y = snake[i - 1].pos_y;
	}
	switch (direction)									//�ƶ������������ң��ֱ��Ӧ������ͷ����任
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

//��������ļ�� ��ȡ��������
void Snake::inputcheck()
{
	char inputc;
	while (_kbhit())	//�Ƿ��м�������
	{
		inputc = _getch();
		switch (inputc)	//�ı䷽�򣬵����ܻ�ͷ������ wasd ��������
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
				outtextxy(0, UIheight + 16 * unitsize, _T("�Ƿ�浵���汾����Ϸ���Ȳ��˳���(�Ḳ��֮ǰһ�εĴ浵) ��  Y  ѡ��ȷ�� ��  N  ѡ��� "));
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
				outtextxy(0, UIheight + 16 * unitsize, _T("�����������                                                                                                                                                     "));
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

//�ж����ǲ���û��
bool Snake::snakedead()
{
	if (wall[snake[0].pos_x][snake[0].pos_y] == 1)		//ײǽ��
	{
		if (choice == 2 || choice == 3)
		{
			setfillcolor(GREEN);
			fillrectangle(snake[0].pos_x * unitsize, snake[0].pos_y * unitsize, snake[0].pos_x * unitsize + unitsize, snake[0].pos_y * unitsize + unitsize);
			for (int i = 0; i < bodysize - 1; i++)				//��ԭ����֮ǰ��״̬
			{
				snake[i].pos_x = snake[i + 1].pos_x;
				snake[i].pos_y = snake[i + 1].pos_y;
			}
			snake[bodysize - 1] = tail;
		}
		return 1;
	}
	for (int i = 1; i < bodysize; i++)
		if (snake[0].pos_x == snake[i].pos_x && snake[0].pos_y == snake[i].pos_y)	//���Լ�ײ��
		{
			if (choice == 2 || choice == 3)
			{
				if (choice == 2)
					setfillcolor(GREEN);
				if (choice == 3)
					setfillcolor(RED);
				fillrectangle(snake[0].pos_x * unitsize, snake[0].pos_y * unitsize, snake[0].pos_x * unitsize + unitsize, snake[0].pos_y * unitsize + unitsize);
				for (int i = 0; i < bodysize - 1; i++)				//��ԭ����֮ǰ��״̬
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
//�ı��ߵ����� �ٶȣ���ɫ
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
//UI��ʾ
void Snake::UIstate_show()
{
	if (!startclock)				//��¼��Ϸ��ʼʱ��
	{
		start_time = time(0);
		startclock = 1;
	}
	now_time = time(0);		//��¼��Ϸ��ǰʱ��
	settextcolor(WHITE);	//UI���
	outtextxy(0, UIheight + 14 * unitsize, _T("���ո������ͣ��Ϸ�ٴΰ��ո���ɼ�����Ϸ����q���˳�������Ϸ����oѡ���Ƿ�浵"));
	outtextxy(0, UIheight, _T("��Ϸʱ��Ϊ: "));
	outtextxy(0, UIheight + 16 * unitsize, _T("                                                                                                                              "));
	TCHAR s[10];
	if (readhistoryflag)
		_stprintf(s, _T("%lld%c%lld%c%c"), ((sec + now_time - start_time) / 60), ':', (sec + now_time - start_time) % 60, ' ', ' '); //��ʾʱ��ת����sΪ��λ
	else
		_stprintf(s, _T("%lld%c%lld%c%c"), (now_time - start_time) / 60, ':', (now_time - start_time) % 60, ' ', ' '); //��ʾʱ��ת����sΪ��λ
	outtextxy(9 * unitsize, UIheight, s);
	if (choice != 6)
	{
		if (choice == 5)
			outtextxy(0, UIheight + 3 * unitsize, _T("�Ե��Ĺ�ͷ����Ϊ: "));
		else
			outtextxy(0, UIheight + 3 * unitsize, _T("��ǰ����Ϊ: "));
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
		outtextxy(0, UIheight + 6 * unitsize, _T("��ʷ��ߵ÷�: "));
	TCHAR s2[10];
	if (choice == 1)
	{
		if (score > historybestscore[1])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("�¼�¼����!"));
			historybestscore[1] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[1]);
	}
	if (choice == 2)
	{
		if (score > historybestscore[2])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("�¼�¼����!"));
			historybestscore[2] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[2]);
	}
	if (choice == 3)
	{
		if (score > historybestscore[3])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("�¼�¼����!"));
			historybestscore[3] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[3]);
	}
	if (choice == 4)
	{
		if (score > historybestscore[4])
		{
			outtextxy(20 * unitsize, UIheight + 6 * unitsize, _T("�¼�¼����!"));
			historybestscore[4] = score;
		}
		_stprintf(s2, _T("%d"), historybestscore[4]);
	}
	if (choice != 5 && choice != 6)
		outtextxy(12 * unitsize, UIheight + 6 * unitsize, s2);
	if (choice == 5)
		outtextxy(0, UIheight + 9 * unitsize, _T("��ǰ��ͷ����Ϊ: "));
	if (choice <= 4 && choice >= 1)
		outtextxy(0, UIheight + 9 * unitsize, _T("�ߵĳ���: "));
	TCHAR s3[10];
	_stprintf(s3, _T("%d"), bodysize);
	if (choice == 5)
		outtextxy(12 * unitsize, UIheight + 9 * unitsize, s3);
	else
		outtextxy(9 * unitsize, UIheight + 9 * unitsize, s3);
	if (choice == 3)
	{
		outtextxy(0, UIheight + 12 * unitsize, _T("��ʣ���������: "));
		TCHAR s4[10];
		_stprintf(s4, _T("%d"), life);
		outtextxy(12 * unitsize, UIheight + 12 * unitsize, s4);
	}
	if (choice == 4)
	{
		outtextxy(0, UIheight + 12 * unitsize, _T("��ǰ����: "));
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
//��Ϸ��������
void Snake::gameover()
{
	cleardevice();
	if (prehistoryflag)
	{
		outtextxy(0, 0, _T("�浵�ɹ�!�ɰ���������ز˵�"));
	}
	else
	{
		if (choice <= 4)
		{
			outtextxy(0, 0, _T("��Ϸ����,�ɰ���������ز˵�"));
			outtextxy(0, 3 * unitsize, _T("�������շ���Ϊ: "));
			TCHAR s1[10];
			_stprintf(s1, _T("%d"), score);
			outtextxy(12 * unitsize, 3 * unitsize, s1);
			outtextxy(0, 6 * unitsize, _T("��ģʽ��ʷ��ߵ÷�Ϊ:"));
			TCHAR s2[10];
			_stprintf(s2, _T("%d"), historybestscore[choice]);
			outtextxy(16 * unitsize, 6 * unitsize, s2);
		}
		if (choice == 5)
			outtextxy(0, 0, _T("��Ϸ����,�ɰ���������ز˵�(doge)"));
		if (choice == 6)
		{
			if (p1win)
				outtextxy(0, 0, _T("��Ϸ����,���1���ʤ��!�ɰ���������ز˵�"));
			else if (p2win)
				outtextxy(0, 0, _T("��Ϸ����,���2���ʤ��!�ɰ���������ز˵�"));
			else
				outtextxy(0, 0, _T("��Ϸ����,�ɰ���������ز˵�"));
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

//��ͬ��Ϸģʽ
//choice1	�����
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
			outtextxy(0, UIheight + 16 * unitsize, _T("׼���ð��������ʼ"));
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

//choice2	���װ�
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
//choice2��������ǽ
void Snake::afterdeath_wall()
{
	for (int i = 0; i < bodysize; i++)
	{
		wall[snake[i].pos_x][snake[i].pos_y] = 1;
		setfillcolor(GREEN);
		fillrectangle(snake[i].pos_x * unitsize, snake[i].pos_y * unitsize, snake[i].pos_x * unitsize + unitsize, snake[i].pos_y * unitsize + unitsize);
		snake[i].pos_x = length + 1;		//��ֹ���ߵ��ƶ��������ɵ�ǽĨȥ
		snake[i].pos_y = width + 1;
	}
	init_snakeflag = 1;
	bodysize = 1;
}
//choice2��3�����Ƿ��пռ�
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


//choice3	�߼���
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
//choice3������ʳ��
void Snake::afterdeath_food()
{
	for (int i = 0; i < bodysize; i++)
	{
		foodpos[snake[i].pos_x][snake[i].pos_y] = 1;
		food[foodcount + i].pos_fx = snake[i].pos_x;
		food[foodcount + i].pos_fy = snake[i].pos_y;
		snake[i].pos_x = length + 1;		//��ֹ���ߵ��ƶ���ʳ��Ĩȥ
		snake[i].pos_y = width + 1;
	}
	foodcount += bodysize;
	init_snakeflag = 1;
	bodysize = 1;
}
