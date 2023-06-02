#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<string>
#include<vector>
#include"graph.hpp"
#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define ACT_COL 11
#define DEF_COL 15
#define RED 12
#define GREEN 10
using namespace std;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
int s_choice(const char* e, int col)
{
	string choice_menu[] = { "����� (ESC)" };
	SetConsoleTextAttribute(hStdOut, DEF_COL);
	int active_menu = 0;
	char ch;
	while (1)
	{
		system("cls");
		ConsoleCursorVisible(false, 100);
		SetConsoleTextAttribute(hStdOut, col);
		cout << e << endl << endl;
		for (int i = 0; i < size(choice_menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, ACT_COL);
			else SetConsoleTextAttribute(hStdOut, DEF_COL);
			cout << choice_menu[i] << endl;
			ch = _getch();
			if (ch == -32) ch = _getch();
		}
		switch (ch)
		{
		case ESC:
			return 2;
		case UP:
			if (active_menu > 0) active_menu--;
			system("cls");
			break;
		case DOWN:
			if (active_menu < size(choice_menu) - 1) active_menu++;
			system("cls");
			break;
		case ENTER:
			switch (active_menu)
			{
			case 1:
				return 2;
			case 0:
				return 1;
			}
		default:
			break;
		}
	}
}
int s_choice(int mist)
{
	string choice_menu[] = { "���������� �����","����� (ESC)" };
	SetConsoleTextAttribute(hStdOut, DEF_COL);
	int active_menu = 0;
	char ch;
	while (1)
	{
		system("cls");
		ConsoleCursorVisible(false, 100);
		if (mist == 1)
		{
			SetConsoleTextAttribute(hStdOut, RED);
			cout << "Text was entered" << endl << endl;
		}
		else if (mist == 2)
		{
			SetConsoleTextAttribute(hStdOut, RED);
			cout << "Integer was expected but float was entered" << endl << endl;
		}
		for (int i = 0; i < size(choice_menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, ACT_COL);
			else SetConsoleTextAttribute(hStdOut, DEF_COL);
			cout << choice_menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch(ch)
		{
		case ESC:
			return 2;
		case UP:
			if (active_menu > 0) active_menu--;
			system("cls");
			break;
		case DOWN:
			if (active_menu < size(choice_menu) - 1) active_menu++;
			system("cls");
			break;
		case ENTER:
			switch (active_menu)
			{
			case 1:
				return 2;
			case 0:
				return 1;
			}
		default:
			break;
		}
	}
}

template<typename Vertex_type, typename Distance_type>
void add_v(Graph<Vertex_type, Distance_type>& gr)
{
	Vertex_type new_v;
	while (1)
	{
		SetConsoleTextAttribute(hStdOut, DEF_COL);
		system("cls");
		cout << "enter value: " ;
		ConsoleCursorVisible(true, 100);
		int choice = 0;
		while (!(cin >> new_v) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');

			choice = s_choice(1);

			break;
		}
		if (choice == 1) continue;
		else if (choice == 2) return;
		else break;
	}
	try
	{
		gr.add_vertex(new_v);
	}
	catch(const char* e)
	{
		int choice = s_choice(e, RED);
		if (choice) return;
	}
	return;
}

template<typename Vertex_type, typename Distance_type>
void check4v(Graph<Vertex_type, Distance_type>& gr)
{
	Vertex_type new_v;
	while (1)
	{
		SetConsoleTextAttribute(hStdOut, DEF_COL);
		system("cls");
		cout << "enter value" << endl;
		int choice = 0;
		while (!(cin >> new_v) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');

			choice = s_choice(1);

			break;
		}
		if (choice == 1) continue;
		else if (choice == 2) return;
		else break;
	}
	try
	{
		int choice;
		if (gr.has_vertex(new_v)) choice = s_choice("This graph has this vertex", GREEN);
		else choice = s_choice("This graph does not have this vertex", RED);
	}
	catch (const char* e)
	{
		cout << e;
		return;
	}
	return;
}
template<typename Vertex_type, typename Distance_type>
void add_e(Graph<Vertex_type, Distance_type>& gr)
{
	Vertex_type from, to;
	Distance_type dis;
	system("cls");
	cout << "enter from" << endl;
	cin >> from;
	cout << endl << "enter to" << endl;
	cin >> to;
	cout << endl << "enter distance" << endl;
	cin >> dis;
	try
	{
		gr.add_edge(from, to, dis);
	}
	catch (const char* e)
	{
		cout << e;
		return;
	}
	return;
}

int main()
{
	setlocale(0, "rus");
	string main_menu[] = {"�������� �������","��������� ������� �������","������� �������","�������� �����","������� �����",
		"������� ����� � ������ ����������","��������� (ESC)"};
	int active_menu = 0;
	char ch;
	Graph<int> gr;
	while (1)
	{
		system("cls");
		ConsoleCursorVisible(false, 100);
		if (!gr._empty())
		{
			SetConsoleTextAttribute(hStdOut, GREEN);
			cout << "����:" << endl;
			gr.print();
			cout << endl;
		}
		else
		{
			SetConsoleTextAttribute(hStdOut, RED);
			cout << "���� ����" << endl << endl;
		}


		for (int i = 0; i < size(main_menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, ACT_COL);
			else SetConsoleTextAttribute(hStdOut, DEF_COL);
			cout << main_menu[i] << endl;
		}

		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch)
		{
		case ESC:
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			exit(0);
		case UP:
			if (active_menu > 0) active_menu--;
			system("cls");
			break;
		case DOWN:
			if (active_menu < size(main_menu) - 1) active_menu++;
			system("cls");
			break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				add_v(gr);
				break;
			case 1:
				check4v(gr);
				break;
			case 2:
				//del_v(gr);
				break;
			case 3:
				add_e(gr);
				break;
			case 4:
				//del_e(false);
				break;
			case 5:
				//del_e(true);
				break;
			case size(main_menu) - 1:
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				exit(0);
			}
		default:
			break;
		}
	}
}