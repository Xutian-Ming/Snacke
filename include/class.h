#pragma once
#include<iostream>
#include<fstream>
using namespace std;

#define length 60
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
//记录蛇、食物坐标的结构体
struct snake_ {
	int pos_x;
	int pos_y;
};
struct Food {
	int pos_fx;
	int pos_fy;
};
//表示方向的枚举
typedef enum
{
	up_, down_, left_, right_
}Direction;

class Snake
{
private:
	Food food[foods];
	Food badfood[badfoodmax], goodfood;
	snake_ snake[Maxbodysize], tail, snake1[Maxbodysize], snake2[Maxbodysize], tail1, tail2;
	Direction direction = right_, direction1 = up_, direction2 = down_;
	time_t start_time, now_time, sec;
	fstream File, newFile;
	fstream preFile;
	IMAGE img1, img2, img3, img4;
	int speed = beginspeed;
	int choice = 0;
	int score = 0;
	int bodysize = 1, bodysize1 = 1, bodysize2 = 1;
	int historybestscore[6] = { 0 };
	int foodcount = 0;
	int badfoodcount = 0;
	int life = 5;
	bool returnflag = 0;
	bool readhistoryflag = 0;
	bool prehistoryflag = 0;
	bool goodfoodsymbol = 1;
	double energy = beginenergy;
	char version[20];
	char playername[50] = { "snake" };
	char p1color, p2color;
	bool init_snakeflag = 1;
	bool create_foodflag = 1;
	bool startflag = 1;
	bool startclock = 0;
	bool p1win = 0, p2win = 0;
	int foodpos[(length + 2)][(width + 2)];
	bool wall[(length + 2)][(width + 2)];
public:
	void menu();
	void setname();
	void game1();
	void game2();
	void game3();
	void game4();
	void game5();
	void game6();
	void drawwall();
	void drawwall2();
	void drawpicturewall();
	void keepwallline();
	void drawsnake();
	void tpdrawsnake();
	void drawdoge();
	void drawfood();
	void drawbone();
	void creategoodfood();
	void drawbadfood();
	void drawfoodmore();
	void create_food();
	void create_foodmore();
	void createbadfood();
	void init_snake();
	void init_2snake();
	void inputcheck();
	void tpcheck();
	void colorsettp();
	void move();
	void tpmove();
	void UIstate_show();
	void gameover();
	void snakestateset();
	void afterdeath_wall();
	void afterdeath_food();
	void energydecrease();
	void historyrecordwrite();
	void historyrecordread();
	void historyrecordshow();
	void historyrecordsearch();
	void historyrecorddelete();
	void historyrecordchangename();
	void preservehistory();
	void readhistory();
	bool havespace();
	bool snakedead();
	bool tpsnakedead();
	int getchoice();
	int gethistoryscore(char*);
};