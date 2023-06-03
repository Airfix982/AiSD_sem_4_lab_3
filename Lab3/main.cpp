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

int s_choice(int col = DEF_COL, const char* e = "nothing")
{
	string choice_menu[] = { "Попытаться снова","Назад (ESC)" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	char ch;
	while (1)
	{
		system("cls");
		SetConsoleTextAttribute(hStdOut, col);
		cout << e << endl << endl;
		for (int i = 0; i < size(choice_menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, ACT_COL);
			else SetConsoleTextAttribute(hStdOut, DEF_COL);
			cout << choice_menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
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

template<typename Vertex_type, typename Distance_type>
void add_v(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			cout << "enter value: ";
			ConsoleCursorVisible(true, 100);
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

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
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void has_v(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter value";
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text vas entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		try
		{
			int choice;
			if (gr.has_vertex(new_v)) choice = s_choice(GREEN, "This graph has this vertex");
			else choice = s_choice(RED, "This graph does not have this vertex");
			if (choice == 2)return;
			else continue;
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void add_e(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type from, to;
		Distance_type dis;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter distance: ";
			int choice = 0;
			while (!(cin >> dis) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else break;
		}
		try
		{
			gr.add_edge(from, to, dis);
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void del_v(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			cout << "enter value: ";
			ConsoleCursorVisible(true, 100);
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else break;
		}
		try
		{
			gr.remove_vertex(new_v);
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void del_e(Graph<Vertex_type, Distance_type>& gr, bool with_dist)
{
	while (1)
	{
		Vertex_type from, to;
		Distance_type dis;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		if (with_dist)
		{
			while (1)
			{
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				system("cls");
				ConsoleCursorVisible(true, 100);
				cout << "enter distance: ";
				int choice = 0;
				while (!(cin >> dis) || (cin.peek() != '\n'))
				{
					cin.clear();
					while (cin.get() != '\n');

					choice = s_choice(RED, "Text was entered");

					break;
				}
				if (choice == 1) continue;
				else if (choice == 2) return;
				else break;
			}
		}
		try
		{
			if (!with_dist)
			{
				gr.remove_edge(from, to);
			}
			else
			{
				gr.remove_edge(from, to, dis);
			}
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void has_e(Graph<Vertex_type, Distance_type>& gr, bool with_dist)
{
	while (1)
	{
		Vertex_type from, to;
		Distance_type dis;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		if (with_dist)
		{
			while (1)
			{
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				system("cls");
				ConsoleCursorVisible(true, 100);
				cout << "enter distance: ";
				int choice = 0;
				while (!(cin >> dis) || (cin.peek() != '\n'))
				{
					cin.clear();
					while (cin.get() != '\n');

					choice = s_choice(RED, "Text was entered");

					break;
				}
				if (choice == 1) continue;
				else if (choice == 2) return;
				else break;
			}
		}
		try
		{
			int choice;
			if (!with_dist)
			{
				if (gr.has_edge(from, to)) choice = s_choice(GREEN, "This graph has this vertex");
				else choice = s_choice(RED, "This graph does not have this vertex");
				if (choice == 2)return;
				else continue;
			}
			else
			{
				if (gr.has_edge(from, to, dis)) choice = s_choice(GREEN, "This graph has this vertex");
				else choice = s_choice(RED, "This graph does not have this vertex");
				if (choice == 2)return;
				else continue;
			}
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void all_e(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			cout << "enter value: ";
			ConsoleCursorVisible(true, 100);
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else break;
		}
		try
		{
			vector<Edge<Vertex_type, Distance_type>> eds;
			eds = gr.edges(new_v);
			system("cls");
			cout << "Ребра вершины " << new_v << ":" << endl;
			for (auto i = eds.begin(); i != eds.end(); i++)
			{
				cout << "Вершина " << i->to << ", дистанция " << i->weight << endl;
			}
			char ch = _getch();
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

int main()
{
	setlocale(0, "rus");
	string main_menu[] = { "Добавить вершину","Проверить наличие вершины","Удалить вершину","Добавить ребро","Удалить ребро",
		"Удалить ребро с учетом расстояния","Проверить наличие ребра","Проверить наличие ребра с учетом расстояния","Все ребра из вершины",
		"Закончить (ESC)"};
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
			cout << "Граф:" << endl;
			gr.print();
			cout << endl;
		}
		else
		{
			SetConsoleTextAttribute(hStdOut, RED);
			cout << "Граф пуст" << endl << endl;
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
			return 0;
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
				has_v(gr);
				break;
			case 2:
				del_v(gr);
				break;
			case 3:
				add_e(gr);
				break;
			case 4:
				del_e(gr, false);
				break;
			case 5:
				del_e(gr, true);
				break;
			case 6:
				has_e(gr, false);
				break;
			case 7:
				has_e(gr, true);
				break;
			case 8:
				all_e(gr);
				break;
			case size(main_menu) - 1:
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				return 0;
			}
		default:
			break;
		}
	}
}