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

//与历史记录操作相关的函数
extern void gotoxy(const int X, const int Y);
extern void getxy(int& x, int& y);


//用来获取某条历史记录的分数
int xm(int x, int n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	else
	{
		for (int i = 2; i <= n; i++)
			x *= x;
	}
	return x;

}
int Snake::gethistoryscore(char* buffer)
{
	int num = 0, count = 0;
	char* ch = buffer + strlen(buffer) - 1;
	while (*ch != ' ')
	{
		if (*ch == '\r' || *ch == '\n')
		{
			ch--;
			continue;
		}
		num += int((*ch - '0') * xm(10, count));
		ch--;
		count++;
	}
	return num;
}

//将某次游戏结果写入历史记录
void Snake::historyrecordwrite()
{
	File.open("snake-historyrecord", ios::in | ios::out | ios::app);//|ios::binary);
	if (!File.is_open())
	{
		cout << "文件打开失败!\n";
		return;
	}
	if (choice == 1)
	{
		strcpy(version, "入门版");
	}
	if (choice == 2)
	{
		strcpy(version, "进阶版");
	}
	if (choice == 3)
	{
		strcpy(version, "高级版");
	}
	if (choice == 4)
	{
		strcpy(version, "趣味版");
	}
	File << "版本: " << version << " 游戏者昵称: " << playername << " 得分: " << score << '\n';
	File.close();
}

//读入历史记录得到不同模式的历史最高分
void Snake::historyrecordread()
{
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		cout << "文件打开失败!\n";
		return;
	}
	char buffer[52];
	int bestscore[6] = { 0 };
	while (!File.eof())
	{
		File.getline(buffer, 51);
		if (!(strstr(buffer, "版本: 入门版") == NULL))
		{
			bestscore[1] = gethistoryscore(buffer);
			if (bestscore[1] > historybestscore[1])
				historybestscore[1] = bestscore[1];
		}
		if (!(strstr(buffer, "版本: 进阶版") == NULL))
		{
			bestscore[2] = gethistoryscore(buffer);
			if (bestscore[2] > historybestscore[2])
				historybestscore[2] = bestscore[2];
		}
		if (!(strstr(buffer, "版本: 高级版") == NULL))
		{
			bestscore[3] = gethistoryscore(buffer);
			if (bestscore[3] > historybestscore[3])
				historybestscore[3] = bestscore[3];
		}
		if (!(strstr(buffer, "版本: 趣味版") == NULL))
		{
			bestscore[4] = gethistoryscore(buffer);
			if (bestscore[4] > historybestscore[4])
				historybestscore[4] = bestscore[4];
		}
	}
	File.close();

}

//展示所有历史记录状态
void Snake::historyrecordshow()
{
	system("cls");
	cout << "历史记录状态如下: " << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		return;
	}
	char ch;
	bool flag = 0;
	while (1)
	{
		if (File.peek() == EOF)
			break;
		ch = File.get();
		flag = 1;
		cout << ch;
	}
	if (flag == 0)
	{
		File.close();
		cout << "目前没有历史记录(按任意键返回菜单)" << endl;
		choice = 0;
		_getch();
		system("cls");
		return;
	}
	cout << "(按任意键可返回菜单)" << endl;
	File.close();
	_getch();
	choice = 0;
	system("cls");
}

//根据昵称搜索历史记录并展示
void Snake::historyrecordsearch()
{
	system("cls");
	cout << "历史记录状态如下: " << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		return;
	}
	//char show[70];
	char ch;
	bool flag1 = 0;
	while (1)
	{
		if (File.peek() == EOF)
			break;
		ch = File.get();
		flag1 = 1;
		cout << ch;
	}
	if (flag1 == 0)
	{
		File.close();
		cout << "目前没有历史记录(按任意键返回菜单)" << endl;
		choice = 0;
		_getch();
		system("cls");
		return;
	}
	File.close();
	cout << endl << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app | ios::binary);
	if (!File.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		return;
	}
	char searchname[70];
	char buffer[52];
	bool flag = 0, flag2 = 0;
	int x, y;
	cout << "请输入你要查找的游戏者昵称: " << endl;
	getxy(x, y);
	while (1)
	{
		cin >> searchname;
		while (1)
		{
			if (File.peek() == EOF)
				break;
			File.getline(buffer, 51);
			if (!(strstr(buffer, searchname) == NULL))//&& !(strstr(buffer, searchversion) == NULL) && searchscore == gethistoryscore(buffer))
			{
				if (!flag2)
				{
					cout << "搜索成功，记录搜索结果显示如下!" << endl;
					flag2 = 1;
				}
				cout << buffer << endl;
				flag = 1;
				continue;
			}
		}
		if (flag == 0)
		{
			File.seekg(0, ios::beg);
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "\n昵称不存在,请重新输入。";
			strcpy(searchname,"");
			File.seekg(0, ios::beg);
			gotoxy(x, y);
			cout << "                                                           ";
			gotoxy(x, y);
			continue;
		}
		File.close();
		cout << "（按任意键返回菜单）";
		choice = 0;
		_getch();
		system("cls");
		return;
	}

}

//删除某条历史记录
void Snake::historyrecorddelete()
{
	system("cls");
	cout << "历史记录状态如下: " << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		return;
	}
	char ch;
	bool flag1 = 0;
	while (1)
	{
		if (File.peek() == EOF)
			break;
		ch = File.get();
		flag1 = 1;
		cout << ch;
	}
	if (flag1 == 0)
	{
		File.close();
		cout << "目前没有历史记录(按任意键返回菜单)" << endl;
		choice = 0;
		_getch();
		system("cls");
		return;
	}
	File.close();
	cout << endl << endl;
	char deleteversion[20];
	char deletename[30];
	int  deletescore;
	char buffer[70];
	int x, y;
	bool flag = 0;
	char ch1;
	cout << "\n(按   q   键可以返回至菜单,按   c   键继续执行删除单条历史记录操作,按    p    键可以删除全部历史记录)\n\n";
	cout << "请输入你要删除的历史记录(内容为版本(入门版、进阶版、高级版)、游戏者昵称、分数，请用空格隔开): " << endl;
	while ((ch1 = _getch()) != '\n')
	{
		if (ch1 == 'q' || ch1 == 'Q')
		{
			choice = 0;
			system("cls");
			return;
		}
		if (ch1 == 'c' || ch1 == 'C')
			break;
		if (ch1 == 'p' || ch1 == 'P')
		{
			File.open("snake-historyrecord", ios::out | ios::in | ios::trunc);
			if (!File.is_open())
			{
				choice = 0;
				cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
				_getch();
				system("cls");
				return;
			}
			File.close();
			choice = 0;
			historybestscore[1] = 0;
			historybestscore[2] = 0;
			historybestscore[3] = 0;
			historybestscore[4] = 0;
			cout << "\n删除成功!（按任意键返回菜单）";
			_getch();
			system("cls");
			return;
		}
	}
	cout << "\n请输入:";
	File.open("snake-historyrecord", ios::out | ios::in | ios::binary);
	if (!File.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		system("cls");
		return;
	}
	getxy(x, y);
	newFile.open("filetochange", ios::in | ios::out | ios::binary | ios::trunc);
	if (!newFile.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		File.close();		//关闭之前打开过的文件
		system("cls");
		return;
	}
	int deleteline = 0, count = 0;
	while (1)
	{
		cin >> deleteversion;
		cin >> deletename;
		cin >> deletescore;
		while (1)
		{
			if (File.peek() == EOF)
				break;
			File.getline(buffer, 1024);
			if (!(strstr(buffer, deletename) == NULL) && !(strstr(buffer, deleteversion) == NULL) && deletescore == gethistoryscore(buffer))
			{
				flag = 1;
				continue;
			}
			newFile << buffer << endl;
		}
		if (flag == 0)
		{
			File.seekg(0, ios::beg);
			newFile.close();
			newFile.open("filetochange", ios::in | ios::out | ios::binary | ios::trunc);
			if (!newFile.is_open())
			{
				choice = 0;
				cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
				_getch();
				File.close();		//关闭之前打开过的文件
				system("cls");
				return;
			}
			cin.clear();
			cin.ignore(1024, '\n');
			gotoxy(x, y);
			cout << "                                     ";
			gotoxy(x, y+1);
			cout << "记录不存在,请重新输入(按   q   键可以返回至菜单  按   c  键重新输入)。";
			gotoxy(x, y);
			char ch;
			while ((ch = _getch()) != '\n')
			{
				if (ch == 'q' || ch == 'Q')
				{
					choice = 0;
					system("cls");
					return;
				}
				if (ch == 'c' || ch == 'C')
				{
					break;
				}
			}
			continue;
		}
		File.close();
		newFile.close();
		newFile.open("filetochange", ios::in | ios::out);
		if (!newFile.is_open())
		{
			choice = 0;
			cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
			_getch();
			system("cls");
			return;
		}
		fstream file("snake-historyrecord", ios::in | ios::out | ios::trunc);
		if (!file.is_open())
		{
			choice = 0;
			cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
			newFile.close();
			_getch();
			system("cls");
			return;
		}
		count = 0;
		while (1)
		{
			if (newFile.peek() == EOF)
				break;
			newFile.getline(buffer, 1024);
			file << buffer << endl;
		}
		file.close();
		newFile.close();
		choice = 0;
		cout << "\n删除成功!（按任意键返回菜单）";
		_getch();
		system("cls");
		return;
	}
}

//改变某次历史记录的游戏者昵称
void Snake::historyrecordchangename()
{
	system("cls");
	File.open("snake-historyrecord", ios::out | ios::in | ios::binary | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
		_getch();
		return;
	}
	char show[70];
	char ch;
	int counts = 0;
	cout << "历史纪录状态为: " << endl;
	while (1)
	{
		if (File.peek() == EOF)
			break;
		File.getline(show, 1024);	// \r!!*/
		counts++;
		cout << show << endl;
	}
	if (counts == 0)
	{
		cout << "目前没有历史记录(按任意键返回菜单)" << endl;
		choice = 0;
		File.close();
		_getch();
		system("cls");
		return;
	}
	File.close();
	char searchversion[20];
	char searchname[70];
	char newname[70];
	int  searchscore;
	char buffer[52];
	char newbuffer[52];
	char ch1;
	bool flag = 0;
	int x, y;
	cout << "\n(按  q  键可以返回至菜单,按   c   键继续修改昵称操作)\n\n";
	cout << "请输入你要更改游戏者昵称的历史记录(内容为版本(入门版、进阶版、高级版)、游戏者昵称、分数，请用空格隔开): " << endl;
	getxy(x, y);
	while ((ch1 = _getch()) != '\n')
	{
		if (ch1 == 'q' || ch1 == 'Q')
		{
			choice = 0;
			system("cls");
			return;
		}
		if (ch1 == 'c' || ch1 == 'C')
			break;
	}
	cout << "\n请输入:";
	getxy(x, y);
	fstream newFile("filetochange1", ios::out | ios::in | ios::binary | ios::trunc);
	if (!newFile.is_open())
	{
		cout << "文件打开失败!\n";
		return;
	}
	File.open("snake-historyrecord", ios::out | ios::in | ios::binary | ios::app);
	if (!File.is_open())
	{
		newFile.close();
		cout << "文件打开失败!\n";
		return;
	}
	while (1)
	{
		cin >> searchversion;
		cin >> searchname;
		cin >> searchscore;
		while (1)
		{
			if (File.peek() == EOF)
				break;
			File.getline(buffer, 51);
			if (!(strstr(buffer, searchname) == NULL) && !(strstr(buffer, searchversion) == NULL) && searchscore == gethistoryscore(buffer))
			{
				cout << endl << endl << "搜索成功，请输入新的游戏者名称(不超过20个字节):     ";
				getxy(x, y);
				while (1)
				{
					cin >> newname;
					if (int(strlen(newname)) > 20)
					{
						cout << "新的游戏者名称长度超出范围,请重新输入";
						cout << "(按q键可以返回至菜单c键继续执行输入操作)。";
						while ((ch = _getch()) != '\n')
						{
							if (ch == 'q' || ch == 'Q')
							{
								File.close();
								newFile.close();
								choice = 0;
								system("cls");
								return;
							}
							if (ch == 'c' || ch == 'C')
							{
								break;
							}
						}
						gotoxy(x, y);
						cout << "                                                                   ";
						gotoxy(x, y);
						continue;
					}
					flag = 1;
					strcpy(newbuffer, "版本: ");
					strcat(newbuffer, searchversion);
					strcat(newbuffer, " 游戏者名称: ");
					strcat(newbuffer, newname);
					strcat(newbuffer, " 得分: ");
					break;
				}
				newFile << newbuffer << searchscore << endl;
				continue;
			}
			newFile << buffer << endl;
		}

		if (flag == 0)
		{
			newFile.seekg(0, ios::beg);
			File.seekg(0, ios::beg);
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "\n记录不存在,请重新输入\n(按q键可以返回至菜单c键重新输入)。";
			while ((ch = _getch()) != '\n')
			{
				if (ch == 'q' || ch == 'Q')
				{
					choice = 0;
					system("cls");
					return;
				}
				if (ch == 'c' || ch == 'C')
				{
					break;
				}
			}
			gotoxy(x, y);
			cout << "                                                           ";
			gotoxy(x, y);
			continue;
		}
		File.close();
		newFile.close();
		newFile.open("filetochange1", ios::in | ios::binary);
		if (!newFile.is_open())
		{
			choice = 0;
			cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
			_getch();
			File.close();		//关闭之前打开过的文件
			system("cls");
			return;
		}
		fstream file("snake-historyrecord", ios::in | ios::out | ios::trunc | ios::binary);
		if (!file.is_open())
		{
			choice = 0;
			cout << "文件打开失败!可能需要进行一场游戏来保证有一条历史记录(按任意键返回菜单)\n";
			_getch();
			system("cls");
			return;
		}
		while (1)
		{
			if (newFile.peek() == EOF)
				break;
			newFile.getline(buffer, 1024);
			file << buffer << endl;
		}
		file.close();
		newFile.close();
		choice = 0;
		cout << "\n\n\n修改成功!（按任意键返回菜单）";
		_getch();
		system("cls");
		return;
	}
}

//存档
void Snake::preservehistory()
{
	preFile.open("preservehistory", ios::out | ios::binary);
	if (!preFile.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	preFile.write((char*)&choice, sizeof(int));
	preFile.write((char*)snake, sizeof(snake));
	preFile.write((char*)foodpos, sizeof(foodpos));
	preFile.write((char*)wall, sizeof(wall));
	preFile.write((char*)&direction, sizeof(Direction));
	preFile.write((char*)&tail, sizeof(snake_));
	preFile.write((char*)&score, sizeof(int));
	preFile.write((char*)&bodysize, sizeof(int));
	preFile.write((char*)&speed, sizeof(int));
	preFile.write((char*)food, sizeof(food));
	preFile.write((char*)&energy, sizeof(double));
	preFile.write((char*)&sec, sizeof(time_t));
	preFile.write((char*)badfood, sizeof(badfood));
	preFile.write((char*)&goodfood, sizeof(Food));
	preFile.write((char*)&foodcount, sizeof(int));
	preFile.write((char*)&badfoodcount, sizeof(int));
	preFile.write((char*)&life, sizeof(int));
	preFile.write((char*)&goodfoodsymbol, sizeof(bool));
	preFile.write(version, sizeof(version));
	preFile.write(playername, sizeof(playername));
	preFile.write((char*)&init_snakeflag, sizeof(bool));
	preFile.write((char*)&create_foodflag, sizeof(bool));
	preFile.write((char*)&startflag, sizeof(bool));
	prehistoryflag = 1;
	preFile.close();
}

//读档
void Snake::readhistory()
{
	preFile.open("preservehistory", ios::in | ios::binary);
	if (!preFile.is_open())
	{
		system("cls");
		cout << "读取失败" << endl;
		cout << "目前还没有存档（按任意键返回菜单）" << endl;
		_getch();
		choice = 0;
		return;
	}
	preFile.read((char*)&choice, sizeof(int));
	preFile.read((char*)snake, sizeof(snake));
	preFile.read((char*)foodpos, sizeof(foodpos));
	preFile.read((char*)wall, sizeof(wall));
	preFile.read((char*)&direction, sizeof(Direction));
	preFile.read((char*)&tail, sizeof(snake_));
	preFile.read((char*)&score, sizeof(int));
	preFile.read((char*)&bodysize, sizeof(int));
	preFile.read((char*)&speed, sizeof(int));
	preFile.read((char*)food, sizeof(food));
	preFile.read((char*)&energy, sizeof(double));
	preFile.read((char*)&sec, sizeof(time_t));
	preFile.read((char*)badfood, sizeof(badfood));
	preFile.read((char*)&goodfood, sizeof(Food));
	preFile.read((char*)&foodcount, sizeof(int));
	preFile.read((char*)&badfoodcount, sizeof(int));
	preFile.read((char*)&life, sizeof(int));
	preFile.read((char*)&goodfoodsymbol, sizeof(bool));
	preFile.read(version, sizeof(version));
	preFile.read(playername, sizeof(playername));
	preFile.read((char*)&init_snakeflag, sizeof(bool));
	preFile.read((char*)&create_foodflag, sizeof(bool));
	preFile.read((char*)&startflag, sizeof(bool));
	readhistoryflag = 1;
	preFile.close();
}