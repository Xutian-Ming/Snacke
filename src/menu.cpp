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

//��˵���صĺ���

/*ʹ�˵���������淶�����н����ĸ�������*/
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

/*������غ���*/
void Snake::menu()
{
	if (choice != 0)
		return;
	if (choice == 0)
	{
		system("cls");
		int x, y;
		cout << "=================̰���ߴ���ս=================" << endl;
		cout << "1.���Ű�0v0" << endl;
		cout << "2.���װ�^0^" << endl;
		cout << "3.�߼���0+0" << endl;
		cout << "4.Ȥζ�����0o0" << endl;
		cout << "5.ͼƬ��" << endl;
		cout << "6.˫��ģʽ" << endl;
		cout << "7.��ʷ��¼��ʾ" << endl;
		cout << "8.��ʷ��¼ɾ��" << endl;
		cout << "9.������Ϸ���ǳƲ�����ʷ��¼" << endl;
		cout << "10.�޸���ʷ��¼�е���Ϸ���ǳ�" << endl;
		cout << "11.�浵��ȡ" << endl;
		cout << "(����-1�����˳�����)" << endl;
		cout << "==============================================" << endl;
		cout << "��ѡ��(��������1~9)��" << endl;
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
			cout << "��Ϸ������ҿ��Ʒ������w��a��s��d������С�ߵ�ǰ������\nʹ�߳Ե���������λ���ϵ�ʳ�λ�����������Ϊ1-5�������" << endl
				<< "\nÿ�γɹ��Ե�ʳ���С���峤������һ�㣬�÷����ӡ�\n�ߵ���ɫ���ƶ��ٶ������߳��ı�\nʳ��Թ����ٴ����������" << endl
				<< "\n��С��ײ���߽������ͷ��������ײʱ���߽��ҵ�����Ϸ������" << endl << "����˵��: w/�� ���� a/�� ���� s/�� ���� d/�� ����" <<
				"(�����������...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 2)
		{
			system("cls");
			cout << "��Ϸ������ҿ��Ʒ������w��a��s��d������С�ߵ�ǰ������\nʹ�߳Ե���������λ���ϵ�ʳ�λ�����������Ϊ1-5�������" << endl
				<< "ÿ�γɹ��Ե�ʳ���С���峤������һ�㣬�÷����ӡ�\n�ߵ���ɫ���ƶ��ٶ������߳��ı�\nʳ��Թ����ٴ����������" << endl
				<< "��С��ײ���߽������ͷ��������ײʱ���߽��ҵ���" << endl <<
				"�߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ��ɱ߽磬����������µ�ʳ����ߣ���Ϸ������ֱ��ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ" << endl << "����˵��: w ���� a ���� s ���� d ����" <<
				"(�����������...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 3)
		{
			system("cls");
			cout << "��Ϸ������ҿ��Ʒ������w��a��s��d������С�ߵ�ǰ������\nʹ�߳Ե���������λ���ϵ�ʳ�λ�����������Ϊ1-5�������" << endl
				<< "\nÿ�γɹ��Ե�ʳ���С���峤������һ�㣬�÷����ӡ�\n�ߵ���ɫ���ƶ��ٶ������߳��ı�\nʳ��Թ����ٴ����������" << endl
				<< "��С��ײ���߽������ͷ��������ײʱ���߽��ҵ���" << endl <<
				"�߹ҵ����ߵ����������һ����ʱ��ʬ��ı���ʾ��ɫ���ʳ�����������µ�ʳ����ߣ���Ϸ������" << endl
				<< "ֱ������������Ϊ0����Ϸ����" << endl << "����˵��: w/�� ���� a/�� ���� s/�� ���� d/�� ����" <<
				"(�����������...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 4)
		{
			system("cls");
			cout << "��Ϸ������ҿ��Ʒ������w��a��s��d������С�ߵ�ǰ������\n" << "��ӵ��һ�����ۣܲ��ߵ����ܻ�����ߵĳ����Բ�ͬ�������ٶ�˥�������ߵ�����˥����0��Ϸ����\n"
				<< "\n��ģʽʳ����ֵĻ����!ʳ����ܣ��ڵ�ͼ�ϻ�������ֵĲ�ͬ��ʳ�����ɫ����ɫ����ɫ����ɫ����\n������ɫʳ���߳��˽���ҵ�������ɫ����ɫ����ɫʳ����������ߵ����ܣ����Ⱥͷ���\n�ߵ���ɫ���ƶ��ٶ������߳��ı�" <<
				"\n��ɫʳ������ָܻ����ͷ������ں�ɫʳ���ɫʳ���߳Ե��󽫻�ָ��������ܡ�" << endl
				<< "�졢����������ʳ��Թ���ٴ������������ɫʳ��Ҳ��������֣�����ɫʳ�ﲢ����һֱ�����������������ޣ���" << endl
				<< "��С������Ϊ0���߳Ե���ɫʳ�����ײ���߽������ͷ��������ײʱ���߽��ҵ���" << endl <<
				endl << "������˵��: w/�� ���� a/�� ���� s/�� ���� d/�� ���ң�" <<
				"(�����������...)";
			_getch();
			system("cls");
			setname();
			system("cls");
			return;
		}
		if (choice == 5)
		{
			system("cls");
			cout << "̰������һ�������ѣ����������������Ҳ�����ǵĺ����ѣ���Ҷ���ϲ����\n��һ��̰��������һ���Σ�" <<
				"�ε��Լ�����˺����ѵ�ģ��\n�������ξ����Լ�������кö�ö������ϲ���Ե�ʳ��\n����Ǳ��ʶ�������Ҫ�Թ�������Щʳ����뷨�����������ֲ��������ض�������..." << endl
				<< "(�����������...)";
			_getch();
			system("cls");
			cout << "����˵��: w/�� ���� a/�� ���� s/�� ���� d/�� ����,��������(doge)";
			"(���������ʼ��Ϸ...)";
			_getch();
		}
		if (choice == 6)
		{
			system("cls");
			cout << "˵��:˫��ģʽ�����1�����2�ֱ�ͨ��w,a,s,d���͡���������������ʵ�����ϡ����¡��ҵ��ƶ�\n��ʳ�����Լ����Ƶ���������\n"
				<< "���һ����ҵĿ��Ƶ���ͷײ������һ����ҵ���������һ����һ����ʤ����\n����Ե�ʳ���峤���ڵ���2��˫����ͷ��ײ��ͬʱײ����ǽ����Ϊƽ��\n";
			cout << "�������������...��" << endl;
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
	cout << "����һ��Ĭ������snake,��Ȼ��Ҳ����ѡ��Ϊ����һ������(��ʮ���ַ�����)" << endl << "(�Ƿ�Ҫ��һ���µ�����,����������y|Y������������n|N��������Ϸ) \n";
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
			cout << "\n�������,���������롣";
			cout << "                                   ";
			gotoxy(x, y);
		}
	}
	while (1)
	{
		cout << endl << endl << "�������Զ�������:     ";
		getxy(x, y);
		cin >> playername;
		if (int(strlen(playername)) > 20)
		{
			cout << "�û������ȳ�����Χ,����������";
			gotoxy(x, y);
			cout << "                                                                   ";
			gotoxy(x, y);
			continue;
		}
		while (1)
		{
			cout << endl << endl << "ȷ��ʹ�ø�������? ������ y || Y ȷ����������Ϸ�������� n || N ����ѡ��: ";
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
				cout << "\n�������,���������롣";
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
int Snake::getchoice()  //��֪��ǰ��ѡ��ģʽ
{
	return choice;
}