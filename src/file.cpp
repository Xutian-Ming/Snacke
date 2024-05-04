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

//����ʷ��¼������صĺ���
extern void gotoxy(const int X, const int Y);
extern void getxy(int& x, int& y);


//������ȡĳ����ʷ��¼�ķ���
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

//��ĳ����Ϸ���д����ʷ��¼
void Snake::historyrecordwrite()
{
	File.open("snake-historyrecord", ios::in | ios::out | ios::app);//|ios::binary);
	if (!File.is_open())
	{
		cout << "�ļ���ʧ��!\n";
		return;
	}
	if (choice == 1)
	{
		strcpy(version, "���Ű�");
	}
	if (choice == 2)
	{
		strcpy(version, "���װ�");
	}
	if (choice == 3)
	{
		strcpy(version, "�߼���");
	}
	if (choice == 4)
	{
		strcpy(version, "Ȥζ��");
	}
	File << "�汾: " << version << " ��Ϸ���ǳ�: " << playername << " �÷�: " << score << '\n';
	File.close();
}

//������ʷ��¼�õ���ͬģʽ����ʷ��߷�
void Snake::historyrecordread()
{
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		cout << "�ļ���ʧ��!\n";
		return;
	}
	char buffer[52];
	int bestscore[6] = { 0 };
	while (!File.eof())
	{
		File.getline(buffer, 51);
		if (!(strstr(buffer, "�汾: ���Ű�") == NULL))
		{
			bestscore[1] = gethistoryscore(buffer);
			if (bestscore[1] > historybestscore[1])
				historybestscore[1] = bestscore[1];
		}
		if (!(strstr(buffer, "�汾: ���װ�") == NULL))
		{
			bestscore[2] = gethistoryscore(buffer);
			if (bestscore[2] > historybestscore[2])
				historybestscore[2] = bestscore[2];
		}
		if (!(strstr(buffer, "�汾: �߼���") == NULL))
		{
			bestscore[3] = gethistoryscore(buffer);
			if (bestscore[3] > historybestscore[3])
				historybestscore[3] = bestscore[3];
		}
		if (!(strstr(buffer, "�汾: Ȥζ��") == NULL))
		{
			bestscore[4] = gethistoryscore(buffer);
			if (bestscore[4] > historybestscore[4])
				historybestscore[4] = bestscore[4];
		}
	}
	File.close();

}

//չʾ������ʷ��¼״̬
void Snake::historyrecordshow()
{
	system("cls");
	cout << "��ʷ��¼״̬����: " << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
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
		cout << "Ŀǰû����ʷ��¼(����������ز˵�)" << endl;
		choice = 0;
		_getch();
		system("cls");
		return;
	}
	cout << "(��������ɷ��ز˵�)" << endl;
	File.close();
	_getch();
	choice = 0;
	system("cls");
}

//�����ǳ�������ʷ��¼��չʾ
void Snake::historyrecordsearch()
{
	system("cls");
	cout << "��ʷ��¼״̬����: " << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
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
		cout << "Ŀǰû����ʷ��¼(����������ز˵�)" << endl;
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
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
		_getch();
		return;
	}
	char searchname[70];
	char buffer[52];
	bool flag = 0, flag2 = 0;
	int x, y;
	cout << "��������Ҫ���ҵ���Ϸ���ǳ�: " << endl;
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
					cout << "�����ɹ�����¼���������ʾ����!" << endl;
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
			cout << "\n�ǳƲ�����,���������롣";
			strcpy(searchname,"");
			File.seekg(0, ios::beg);
			gotoxy(x, y);
			cout << "                                                           ";
			gotoxy(x, y);
			continue;
		}
		File.close();
		cout << "������������ز˵���";
		choice = 0;
		_getch();
		system("cls");
		return;
	}

}

//ɾ��ĳ����ʷ��¼
void Snake::historyrecorddelete()
{
	system("cls");
	cout << "��ʷ��¼״̬����: " << endl;
	File.open("snake-historyrecord", ios::out | ios::in | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
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
		cout << "Ŀǰû����ʷ��¼(����������ز˵�)" << endl;
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
	cout << "\n(��   q   �����Է������˵�,��   c   ������ִ��ɾ��������ʷ��¼����,��    p    ������ɾ��ȫ����ʷ��¼)\n\n";
	cout << "��������Ҫɾ������ʷ��¼(����Ϊ�汾(���Ű桢���װ桢�߼���)����Ϸ���ǳơ����������ÿո����): " << endl;
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
				cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
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
			cout << "\nɾ���ɹ�!������������ز˵���";
			_getch();
			system("cls");
			return;
		}
	}
	cout << "\n������:";
	File.open("snake-historyrecord", ios::out | ios::in | ios::binary);
	if (!File.is_open())
	{
		choice = 0;
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
		_getch();
		system("cls");
		return;
	}
	getxy(x, y);
	newFile.open("filetochange", ios::in | ios::out | ios::binary | ios::trunc);
	if (!newFile.is_open())
	{
		choice = 0;
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
		_getch();
		File.close();		//�ر�֮ǰ�򿪹����ļ�
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
				cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
				_getch();
				File.close();		//�ر�֮ǰ�򿪹����ļ�
				system("cls");
				return;
			}
			cin.clear();
			cin.ignore(1024, '\n');
			gotoxy(x, y);
			cout << "                                     ";
			gotoxy(x, y+1);
			cout << "��¼������,����������(��   q   �����Է������˵�  ��   c  ����������)��";
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
			cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
			_getch();
			system("cls");
			return;
		}
		fstream file("snake-historyrecord", ios::in | ios::out | ios::trunc);
		if (!file.is_open())
		{
			choice = 0;
			cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
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
		cout << "\nɾ���ɹ�!������������ز˵���";
		_getch();
		system("cls");
		return;
	}
}

//�ı�ĳ����ʷ��¼����Ϸ���ǳ�
void Snake::historyrecordchangename()
{
	system("cls");
	File.open("snake-historyrecord", ios::out | ios::in | ios::binary | ios::app);
	if (!File.is_open())
	{
		choice = 0;
		cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
		_getch();
		return;
	}
	char show[70];
	char ch;
	int counts = 0;
	cout << "��ʷ��¼״̬Ϊ: " << endl;
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
		cout << "Ŀǰû����ʷ��¼(����������ز˵�)" << endl;
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
	cout << "\n(��  q  �����Է������˵�,��   c   �������޸��ǳƲ���)\n\n";
	cout << "��������Ҫ������Ϸ���ǳƵ���ʷ��¼(����Ϊ�汾(���Ű桢���װ桢�߼���)����Ϸ���ǳơ����������ÿո����): " << endl;
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
	cout << "\n������:";
	getxy(x, y);
	fstream newFile("filetochange1", ios::out | ios::in | ios::binary | ios::trunc);
	if (!newFile.is_open())
	{
		cout << "�ļ���ʧ��!\n";
		return;
	}
	File.open("snake-historyrecord", ios::out | ios::in | ios::binary | ios::app);
	if (!File.is_open())
	{
		newFile.close();
		cout << "�ļ���ʧ��!\n";
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
				cout << endl << endl << "�����ɹ����������µ���Ϸ������(������20���ֽ�):     ";
				getxy(x, y);
				while (1)
				{
					cin >> newname;
					if (int(strlen(newname)) > 20)
					{
						cout << "�µ���Ϸ�����Ƴ��ȳ�����Χ,����������";
						cout << "(��q�����Է������˵�c������ִ���������)��";
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
					strcpy(newbuffer, "�汾: ");
					strcat(newbuffer, searchversion);
					strcat(newbuffer, " ��Ϸ������: ");
					strcat(newbuffer, newname);
					strcat(newbuffer, " �÷�: ");
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
			cout << "\n��¼������,����������\n(��q�����Է������˵�c����������)��";
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
			cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
			_getch();
			File.close();		//�ر�֮ǰ�򿪹����ļ�
			system("cls");
			return;
		}
		fstream file("snake-historyrecord", ios::in | ios::out | ios::trunc | ios::binary);
		if (!file.is_open())
		{
			choice = 0;
			cout << "�ļ���ʧ��!������Ҫ����һ����Ϸ����֤��һ����ʷ��¼(����������ز˵�)\n";
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
		cout << "\n\n\n�޸ĳɹ�!������������ز˵���";
		_getch();
		system("cls");
		return;
	}
}

//�浵
void Snake::preservehistory()
{
	preFile.open("preservehistory", ios::out | ios::binary);
	if (!preFile.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
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

//����
void Snake::readhistory()
{
	preFile.open("preservehistory", ios::in | ios::binary);
	if (!preFile.is_open())
	{
		system("cls");
		cout << "��ȡʧ��" << endl;
		cout << "Ŀǰ��û�д浵������������ز˵���" << endl;
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