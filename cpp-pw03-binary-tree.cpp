/*
// Задание №1.
//  Создать класс для работы с бинарным деревом, содержащим англо-русский словарь.
//  Каждый узел содержит счетчик обращений к слову в данном узле.
//  В процессе эксплуатации словаря при каждом вызове слова в счетчик
//  обращений добавляется единица.
//  Написать программу, которая:
// ■ обеспечивает начальный ввод словаря с конкретными значениями счетчика
//    обращений;
// ■ позволяет отобразить слово и его перевод;
// ■ позволяет добавить, заменить, удалить перевод слова;
// ■ отображает топ-3 самых популярных слов (определяем популярность на
//    основании счетчика обращений);
// ■ отображает топ-3 самых непопулярных слов (определяем непопулярность на
//    основании счетчика обращений).

#ifndef _MENU_H_
#define _MENU_H_

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>

class Menu
{
private:
	int m_iWidth;
	char *m_szTitle;
	int m_nCursor;
	struct MenuItem
	{
		char *name;
		int (*func)(void *);
		void *arg;
	};
	MenuItem *Item;
	int Count;

public:
	Menu();
	Menu(const char *szTitle);
	~Menu();
	void AddItem(const char *, int (*)(void *) = nullptr, void *arg = nullptr);
	void Run();
	int GetSelect();
	static void Wait(void);
	static void Message(const char *msg, int sec = 1000);
};

#endif // _MENU_H_

#define COLOR_TITLE FOREGROUND_GREEN | FOREGROUND_RED
#define COLOR_FRAME FOREGROUND_GREEN
#define COLOR_ITEM FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define COLOR_CURSOR BACKGROUND_BLUE | BACKGROUND_GREEN
#define COLOR_ERROR FOREGROUND_RED

using namespace std;

Menu::Menu()
{
	m_iWidth = 0;
	m_szTitle = nullptr;
	m_nCursor = 0;
	Item = NULL;
	Count = 0;
}

Menu::Menu(const char *szTitle)
{
	m_iWidth = 0;
	m_szTitle = nullptr;
	m_nCursor = 0;
	Item = NULL;
	Count = 0;
	m_szTitle = new char[strlen(szTitle) + 1];
	strcpy(m_szTitle, szTitle);
	if (m_iWidth < (int)strlen(szTitle) + 4)
		m_iWidth = strlen(szTitle) + 4;
}

Menu::~Menu()
{
	for (int i = 0; i < Count; i++)
		delete[] Item[i].name;
	delete[] Item;
	delete[] m_szTitle;
}

void Menu::AddItem(const char *name, int (*func)(void *), void *arg)
{
	MenuItem *old = Item;
	Item = new MenuItem[Count + 1];
	for (int i = 0; i < Count; i++)
		Item[i] = old[i];
	Item[Count].name = new char[strlen(name) + 1];
	strcpy(Item[Count].name, name);
	Item[Count].func = func;
	Item[Count].arg = arg;
	Count++;
	if (m_iWidth < (int)strlen(name) + 4)
		m_iWidth = strlen(name) + 4;
	delete[] old;
}

void Menu::Run(void)
{
	int ch;
	bool end = false;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	COORD pos;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	// сохраняем текущую кодовую страницу
	int PrevCP = GetConsoleCP();

	// сохраняем текущие цвета консоли
	GetConsoleScreenBufferInfo(hStdout, &screen);
	WORD PrevColor = screen.wAttributes;

	// делаем курсор невидимым
	GetConsoleCursorInfo(hStdout, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hStdout, &cursor);

	char s = cout.fill(' ');

	system("cls");

	do
	{
		GetConsoleScreenBufferInfo(hStdout, &screen);
		pos.X = (screen.dwSize.X - m_iWidth) / 2;
		pos.Y = (25 - Count) / 2;

		SetConsoleCursorPosition(hStdout, pos);
		SetConsoleTextAttribute(hStdout, COLOR_FRAME);
		SetConsoleOutputCP(866);

		if (m_szTitle)
		{
			cout << (char)218 << setfill((char)196) << setw((m_iWidth - 2 - strlen(m_szTitle)) / 2) << ' ';

			SetConsoleTextAttribute(hStdout, COLOR_TITLE);
			SetConsoleOutputCP(1251);
			cout << m_szTitle << ' ';

			SetConsoleTextAttribute(hStdout, COLOR_FRAME);
			SetConsoleOutputCP(866);

			cout << setw((m_iWidth - 2 - strlen(m_szTitle)) / 2);

			if (m_iWidth % 2 != 0)
				cout << (char)196;

			cout << (char)191;
		}
		else
		{
			cout << (char)218 << setfill((char)196) << setw(m_iWidth - 1ll) << (char)191;
		}

		cout.fill(32);

		for (int i = 0; i < Count; i++)
		{
			pos.Y++;

			SetConsoleCursorPosition(hStdout, pos);
			SetConsoleTextAttribute(hStdout, COLOR_FRAME);
			cout << (char)179 << ' ';

			SetConsoleOutputCP(1251);

			if (i == m_nCursor)
				SetConsoleTextAttribute(hStdout, COLOR_CURSOR);
			else
				SetConsoleTextAttribute(hStdout, COLOR_ITEM);

			cout << setw(m_iWidth - 4ll) << setfill(' ') << left << Item[i].name;

			SetConsoleTextAttribute(hStdout, COLOR_FRAME);
			SetConsoleOutputCP(866);
			cout << ' ' << (char)179 << endl;
		}

		pos.Y++;

		SetConsoleCursorPosition(hStdout, pos);
		cout << (char)192 << setfill((char)196) << setw(m_iWidth - 1ll) << right << (char)217 << endl;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 72 && m_nCursor > 0)
				m_nCursor--;
			else if (ch == 80 && m_nCursor < Count - 1)
				m_nCursor++;
		}
		else if (ch == 13)
		{
			if (Item[m_nCursor].func)
			{
				system("cls");

				// включаем курсор
				cursor.bVisible = true;
				SetConsoleCursorInfo(hStdout, &cursor);

				// востанавливаем цвета консоли
				SetConsoleTextAttribute(hStdout, PrevColor);

				// востанавливаем кодовую странмцу
				SetConsoleOutputCP(PrevCP);

				cout.fill(s);

				if (Item[m_nCursor].func(Item[m_nCursor].arg) == 1)
					Wait();

				cursor.bVisible = false;
				SetConsoleCursorInfo(hStdout, &cursor);

				system("cls");
			}
			else
				end = true;
		}
	} while (!end);
	system("cls");

	// включаем курсор
	cursor.bVisible = true;
	SetConsoleCursorInfo(hStdout, &cursor);

	// востанавливаем цвета консоли
	SetConsoleTextAttribute(hStdout, PrevColor);

	// востанавливаем кодовую странмцу
	SetConsoleOutputCP(PrevCP);
}

int Menu::GetSelect()
{
	int ch;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	COORD pos;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	// сохраняем текущую кодовую страницу
	int PrevCP = GetConsoleCP();

	// сохраняем текущие цвета консоли
	GetConsoleScreenBufferInfo(hStdout, &screen);
	WORD PrevColor = screen.wAttributes;

	// делаем курсор невидимым
	GetConsoleCursorInfo(hStdout, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hStdout, &cursor);

	char s = cout.fill(' ');

	system("cls");

	do
	{
		GetConsoleScreenBufferInfo(hStdout, &screen);
		pos.X = (screen.dwSize.X - m_iWidth) / 2;
		pos.Y = (25 - Count) / 2;

		SetConsoleCursorPosition(hStdout, pos);
		SetConsoleTextAttribute(hStdout, COLOR_FRAME);
		SetConsoleOutputCP(866);

		if (m_szTitle)
		{
			cout << (char)218 << setfill((char)196) << setw((m_iWidth - 2 - strlen(m_szTitle)) / 2) << ' ';

			SetConsoleTextAttribute(hStdout, COLOR_TITLE);
			SetConsoleOutputCP(1251);
			cout << m_szTitle << ' ';

			SetConsoleTextAttribute(hStdout, COLOR_FRAME);
			SetConsoleOutputCP(866);

			cout << setw((m_iWidth - 2 - strlen(m_szTitle)) / 2);

			if (m_iWidth % 2 != 0)
				cout << (char)196;

			cout << (char)191;
		}
		else
		{
			cout << (char)218 << setfill((char)196) << setw(m_iWidth - 1ll) << (char)191;
		}

		cout.fill(32);

		for (int i = 0; i < Count; i++)
		{
			pos.Y++;

			SetConsoleCursorPosition(hStdout, pos);
			SetConsoleTextAttribute(hStdout, COLOR_FRAME);
			cout << (char)179 << ' ';

			SetConsoleOutputCP(1251);

			if (i == m_nCursor)
				SetConsoleTextAttribute(hStdout, COLOR_CURSOR);
			else
				SetConsoleTextAttribute(hStdout, COLOR_ITEM);

			cout << setw(m_iWidth - 4ll) << setfill(' ') << left << Item[i].name;

			SetConsoleTextAttribute(hStdout, COLOR_FRAME);
			SetConsoleOutputCP(866);
			cout << ' ' << (char)179 << endl;
		}

		pos.Y++;

		SetConsoleCursorPosition(hStdout, pos);
		cout << (char)192 << setfill((char)196) << setw(m_iWidth - 1ll) << right << (char)217 << endl;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 72 && m_nCursor > 0)
				m_nCursor--;
			else if (ch == 80 && m_nCursor < Count - 1)
				m_nCursor++;
		}
		else if (ch == 13)
		{
			// включаем курсор
			cursor.bVisible = true;
			SetConsoleCursorInfo(hStdout, &cursor);

			// востанавливаем цвета консоли
			SetConsoleTextAttribute(hStdout, PrevColor);

			// востанавливаем кодовую странмцу
			SetConsoleOutputCP(PrevCP);

			cout.fill(s);

			return m_nCursor;
		}
	} while (true);
}

void Menu::Wait(void)
{
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << " Press ENTER...";
	std::cin.get();
}

void Menu::Message(const char *msg, int msec)
{
	int nWidth = strlen(msg);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	COORD pos;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	char s = cout.fill(' ');

	// сохраняем текущую кодовую страницу
	int PrevCP = GetConsoleCP();

	// сохраняем текущие цвета консоли
	GetConsoleScreenBufferInfo(hStdout, &screen);
	WORD PrevColor = screen.wAttributes;

	// делаем курсор невидимым
	GetConsoleCursorInfo(hStdout, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hStdout, &cursor);

	system("cls");

	GetConsoleScreenBufferInfo(hStdout, &screen);
	pos.X = (screen.dwSize.X - nWidth) / 2;
	pos.Y = (25 - 1) / 2;

	SetConsoleCursorPosition(hStdout, pos);
	SetConsoleTextAttribute(hStdout, COLOR_ERROR);
	SetConsoleOutputCP(866);

	cout << (char)218 << setfill((char)196) << setw(nWidth + 3ll) << (char)191;

	cout.fill(32);

	pos.Y++;
	SetConsoleCursorPosition(hStdout, pos);
	SetConsoleTextAttribute(hStdout, COLOR_ERROR);
	cout << (char)179 << ' ';

	SetConsoleOutputCP(1251);

	SetConsoleTextAttribute(hStdout, COLOR_ITEM);

	cout << setw(nWidth - 4ll) << setfill(' ') << left << msg;

	SetConsoleTextAttribute(hStdout, COLOR_ERROR);
	SetConsoleOutputCP(866);
	cout << ' ' << (char)179 << endl;

	pos.Y++;
	SetConsoleCursorPosition(hStdout, pos);
	cout << (char)192 << setfill((char)196) << setw(nWidth + 3ll) << right << (char)217 << endl;

	Sleep(msec);

	// включаем курсор
	cursor.bVisible = true;
	SetConsoleCursorInfo(hStdout, &cursor);

	// востанавливаем цвета консоли
	SetConsoleTextAttribute(hStdout, PrevColor);

	// востанавливаем кодовую странмцу
	SetConsoleOutputCP(PrevCP);

	cout.fill(s);
}

#pragma once

template <typename Data>
class Tree
{
	struct Node
	{
		Data data;
		Node *left;
		Node *right;

		Node() : left(nullptr), right(nullptr) {}
		Node(Data data) : data(data), left(nullptr), right(nullptr) {}
	};

	Node *root;
	Node *tmp;

	Node *insert(Node *node, Data data);
	template <typename Key>
	Node *search(Node *node, Key key);
	template <typename Key>
	Node *remove(Node *node, Key key);
	Node &find_min(Node *node);
	void OrderTraversal(Node *node, void (*action)(Data &date));
	void clear(Node *node);

public:
	Tree();
	~Tree();
	Data &insert(Data data);
	template <typename Key>
	Data *search(Key key);
	template <typename Key>
	void remove(Key key);
	void OrderTraversal(void (*action)(Data &date));
	void clear();
};

template <typename Data>
inline typename Tree<Data>::Node *Tree<Data>::insert(Node *node, Data data)
{
	if (!node)
	{
		tmp = new Node(data);
		return tmp;
	}
	if (node->data > data)
		node->left = insert(node->left, data);
	else if (node->data < data)
		node->right = insert(node->right, data);
	else
		tmp = node;
	return node;
}

template <typename Data>
inline typename Tree<Data>::Node &Tree<Data>::find_min(Node *node)
{
	if (node->left)
		return find_min(node->left);
	else
		return *node;
}

template <typename Data>
void Tree<Data>::OrderTraversal(Node *node, void (*action)(Data &date))
{
	if (node)
	{
		OrderTraversal(node->left, action);
		action(node->data);
		OrderTraversal(node->right, action);
	}
}

template <typename Data>
inline void Tree<Data>::clear(Node *node)
{
	if (node)
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

template <typename Data>
inline Tree<Data>::Tree() : root(nullptr), tmp(nullptr) {}

template <typename Data>
inline Tree<Data>::~Tree() { clear(); }

template <typename Data>
inline Data &Tree<Data>::insert(Data data)
{
	root = insert(root, data);
	return tmp->data;
}

template <typename Data>
void Tree<Data>::OrderTraversal(void (*action)(Data &date)) { OrderTraversal(root, action); }

template <typename Data>
inline void Tree<Data>::clear()
{
	clear(root);
	root = nullptr;
}

template <typename Data>
template <typename Key>
inline typename Tree<Data>::Node *Tree<Data>::search(Node *node, Key key)
{
	if (!node || node->data == key)
		return node;
	else if (node->data > key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

template <typename Data>
template <typename Key>
inline typename Tree<Data>::Node *Tree<Data>::remove(Node *node, Key key)
{
	if (node)
	{
		if (node->data > key)
		{
			node->left = remove(node->left, key);
			return node;
		}
		else if (node->data < key)
		{
			node->right = remove(node->right, key);
			return node;
		}

		if (!node->left)
			return node->right;
		else if (!node->right)
			return node->left;
		else
		{
			auto min_key = find_min(node->right).data;
			node->data = min_key;
			node->right = remove(node->right, min_key);
			return node;
		}
	}
	return nullptr;
}

template <typename Data>
template <typename Key>
inline Data *Tree<Data>::search(Key key)
{
	if (tmp = search(root, key))
		return &tmp->data;
	else
		return nullptr;
}

template <typename Data>
template <typename Key>
inline void Tree<Data>::remove(Key key)
{
	root = remove(root, key);
}

#include <Windows.h>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Word
{
	string en;
	string ru;
	int uses;

	bool operator>(Word word)
	{
		return en > word.en;
	}
	bool operator<(Word word)
	{
		return en < word.en;
	}
	bool operator==(string word)
	{
		return en == word;
	}
	bool operator>(string word)
	{
		return en > word;
	}
	bool operator<(string word)
	{
		return en < word;
	}
};

Tree<Word> dictionary;

int max1, max2, max3;
int min1 = 65535, min2 = 65535, min3 = 65535;
std::string maxstr1, maxstr2, maxstr3;
std::string minstr1, minstr2, minstr3;

int AddWord(void *);
int RemoveWord(void *);
int Show(void *);
void ShowWord(Word &);
int Translate(void *);
int ShowMax(void *);
int ShowMin(void *);

int main()
{
	int PrevCP = GetConsoleCP();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu("Англо-русский словарь ");
	menu.AddItem("Добавить слово", AddWord);
	menu.AddItem("Изменить слово");
	menu.AddItem("Удалить слово", RemoveWord);
	menu.AddItem("Показать словарь", Show);
	menu.AddItem("Перевести слово", Translate);
	menu.AddItem("3 сомых популярных слова", ShowMax);
	menu.AddItem("3 самых не популярных слова", ShowMin);
	menu.AddItem("Выход");
	menu.Run();

	SetConsoleCP(PrevCP);
	SetConsoleOutputCP(PrevCP);

	return 0;
}

int AddWord(void *)
{
	Word word;
	cout << "Слово на английском ";
	cin >> word.en;
	cout << "Слово на русском ";
	cin >> word.ru;
	cout << "Число обращений ";
	cin >> word.uses;
	dictionary.insert(word);
	return 0;
}

int RemoveWord(void *)
{
	string en;
	cout << "Слово на английском ";
	cin >> en;
	dictionary.remove(en);
	return 0;
}

int Show(void *)
{
	dictionary.OrderTraversal(ShowWord);
	return 1;
}

void ShowWord(Word &word)
{
	cout << word.en << " = " << word.ru << " ("
		 << "использовано " << word.uses << ")" << endl;
}

int Translate(void *)
{
	string en;
	Word *word;
	cout << "Слово на английском ";
	cin >> en;
	if (word = dictionary.search(en))
	{
		word->uses++;
		cout << "Перевод: " << word->ru << endl;
		cout << "Использовано: " << word->uses << endl;
		return 1;
	}
	else
		Menu::Message("Слово не найдено");
	return 0;
}

void MinMax(Word &word)
{
	for (int n = 0; n < 3; n++)
	{
		if (word.uses > max1)
		{
			max1 = word.uses;
			maxstr1 = word.en;
		}
		if (word.uses > max2 && word.en != maxstr1 && word.en != maxstr2 && word.en != maxstr3)
		{
			max2 = word.uses;
			maxstr2 = word.en;
		}
		if (word.uses > max3 && word.en != maxstr1 && word.en != maxstr2 && word.en != maxstr3)
		{
			max3 = word.uses;
			maxstr3 = word.en;
		}
		// =========================

		if (word.uses < min1)
		{
			min1 = word.uses;
			minstr1 = word.en;
		}
		if (word.uses < min2 && word.en != minstr1 && word.en != minstr2 && word.en != minstr3)
		{
			min2 = word.uses;
			minstr2 = word.en;
		}
		if (word.uses < min3 && word.en != minstr1 && word.en != minstr2 && word.en != minstr3)
		{
			min3 = word.uses;
			minstr3 = word.en;
		}
	}
}

int ShowMax(void *)
{
	dictionary.OrderTraversal(MinMax);
	cout << "max 1 = " << maxstr1 << endl;
	cout << "max 2 = " << maxstr2 << endl;
	cout << "max 3 = " << maxstr3 << endl;
	return 1;
}

int ShowMin(void *)
{
	dictionary.OrderTraversal(MinMax);
	cout << "min 1 = " << minstr1 << endl;
	cout << "min 2 = " << minstr2 << endl;
	cout << "min 3 = " << minstr3 << endl;

	return 1;
}
*/

// Задание №2.
//  Написать программу, моделирующую работу автобусного парка.
//  Сведения о каждом автобусе содержат: номер автобуса, фамилию и имя водителя,
//   номер маршрута, количество мест в автобусе.
//  Сформировать информацию об автобусах в виде бинарного дерева.
//  Ключом для формирования дерева является номер автобуса.
// Программа должна:
// ■ Предоставить интерфейс типа «меню»;
// ■ Выполнять поиск по указанному ключу;
// ■ Выводить информацию о найденном автобусе на экран;
// ■ Записать информацию об автобусах в упорядоченном виде в файл.
// ■ Иметь возможность считать информацию из файла.

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

void dash(int);
void dot(int);
void dotdot(int);
void equal(int);
void tabs(int);
void apostrophe(int);
void underscore(int);
void eatline(void);
int valueTypeI();

///////////////////////////////////////////////////////////////////////////////

class StationList
{
public:
	string number; // Номер автобуса
	string route;  // Маршрут автобуса
	int seat;	   // Места в автобусе

	string name;	// Имя водителя автобуса
	string surname; // Фамилия водителя автобуса

	StationList(string);

	void show();
	void save(ofstream &);

	bool operator<(StationList obj);
	bool operator==(StationList obj);
};

class Tree
{

public:
	Tree();
	StationList *search(string);
	void set(string, string, string, string, int);
	void destroy(string number);
	int show();
	int save();
	int load();

private:
	struct Node
	{
		StationList *station_list;
		Node *left;
		Node *right;
		Node();
		Node(string);
	};

	Node *root;
	Node *destroy(Node *, string);
	Node *findMin(Node *);

	int show(Node *);
	int save(Node *, ofstream &);
};

StationList::StationList(string number)
{
	this->number = number;
}

void StationList::show()
{
	cout << " | " << setw(10) << number << " |                       |                                        |" << endl;
	cout << " |            |  Номер маршрута: " << setw(4) << route << " |     Имя водителя: " << setw(20) << name << " |" << endl;
	cout << " |            | Количество мест: " << setw(4) << seat << " | Фамилия водителя: " << setw(20) << surname << " |" << endl;
	cout << " |-----------------------------------------------------------------------------|" << endl;
}

void StationList::save(ofstream &file)
{
	file << number << endl;
	file << route << endl;
	file << name << endl;
	file << surname << endl;
	file << seat << endl;

	file.write((char *)&seat, sizeof(int));
}

bool StationList::operator<(StationList obj)
{
	return this->number < obj.number;
}

bool StationList::operator==(StationList obj)
{
	return this->number == obj.number;
}

Tree::Tree()
{
	root = nullptr;
}

Tree::Node::Node(string number)
{
	station_list = new StationList(number);
	left = nullptr;
	right = nullptr;
}

StationList *Tree::search(string number)
{
	Node *node = root;
	while (node)
	{
		if (node->station_list->number == number)
			return node->station_list;
		else if (number < node->station_list->number)
			node = node->left;
		else
			node = node->right;
	}

	return nullptr;
}

void Tree::set(string number, string name, string surname, string route, int seat)
{
	Node *node = root;
	Node *parent = nullptr;
	while (node)
	{
		parent = node;
		if (number < node->station_list->number)
			node = node->left;
		else if (number > node->station_list->number)
			node = node->right;
		else
		{
			node->station_list->name = name;
			node->station_list->surname = surname;
			node->station_list->route = route;
			node->station_list->seat = seat;
		}
	}

	Node *temp = new Node(number);
	temp->station_list->name = name;
	temp->station_list->surname = surname;
	temp->station_list->route = route;
	temp->station_list->seat = seat;

	if (!root)
		root = temp;
	else if (number < parent->station_list->number)
		parent->left = temp;
	else
		parent->right = temp;
}

int Tree::show()
{
	if (show(root) == 1)
		return 1;
	else
		return -1;
}

int Tree::show(Node *node)
{
	if (node)
	{
		show(node->left);
		node->station_list->show();
		show(node->right);
		return 1;
	}
	return -1;
}

int Tree::save()
{
	ofstream file("DatаStationBus.txt", ios::out | ios::binary | ios::trunc);
	if (save(root, file) == 1)
	{
		file.close();
		return 1;
	}
	else
	{
		file.close();
		return -1;
	}
}

int Tree::save(Node *node, ofstream &file)
{
	if (node)
	{
		save(node->left, file);
		node->station_list->save(file);
		save(node->right, file);
		return 1;
	}
	return -1;
}

int Tree::load()
{
	string route;
	string number;

	string name;
	string surname;

	int seat = 0;

	ifstream file("DatаStationBus.txt", ios::in | ios::binary);
	if (file)
	{
		while (file)
		{
			getline(file, number);
			getline(file, route);
			getline(file, name);
			getline(file, surname);

			file >> seat;
			file.ignore();

			if (!file)
				break;

			file.read((char *)&seat, sizeof(int));

			set(number, name, surname, route, seat);
		}
		file.close();
		return 1;
	}
	file.close();
	return -1;
}

void Tree::destroy(string number)
{
	root = destroy(root, number);
}

Tree::Node *Tree::destroy(Node *node, string number)
{
	if (!node)
		return nullptr;

	if (number < node->station_list->number)
	{
		node->left = destroy(node->left, number);
		return node;
	}
	else if (number > node->station_list->number)
	{
		node->right = destroy(node->right, number);
		return node;
	}

	if (!node->left)
		return node->right;
	else if (!node->right)
		return node->left;
	else
	{
		string min_number = findMin(node->right)->station_list->number;
		node->station_list->number = min_number;
		node->right = destroy(node->right, min_number);
		return node;
	}
}

Tree::Node *Tree::findMin(Node *node)
{
	if (!node->left)
		return findMin(node->left);

	return node;
}

int main()
{
	int i1 = GetConsoleCP();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Tree tree;

	string number; // Номер автобуса
	string route;  // Маршрут автобуса
	int seat;	   // Места в автобусе

	string name;	// Имя водителя автобуса
	string surname; // Фамилия водителя автобуса

	int menu;
	bool install = false;
	bool goback = true;
	do
	{
		system("cls");
		equal(80);
		cout << endl;
		tabs(9);
		cout << endl;
		apostrophe(80);
		cout << endl;
		cout << "\t\t   ***| Практическая работа №3  Задача №2 |***" << endl
			 << endl
			 << endl;
		cout << "\t________________________| Главное меню |________________________________" << endl;
		cout << "\t    Выберите ПУНКТ меню для работы:" << endl;
		cout << "\t 1) Добавить информацию в автобусный парк." << endl;
		cout << "\t 2) Вывод на экран весь список данных по автобусному парку." << endl;
		cout << "\t 3) Вывод на экран информацию по номеру автобуса." << endl;
		cout << "\t 4) Удалить запись данных по номеру автобуса." << endl;
		cout << "\t 5) Сохранить файл." << endl;
		cout << "\t 6) Загрузить файл." << endl;
		cout << "\t 7)  | ВыхоД |";

		menu = valueTypeI();
		cout << endl;

		switch (menu)
		{
		case 1:
		{
			int ask;

			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
				 << endl;
			cout << "\t   Добавить информацию в автобусный парк?" << endl;
			cout << "\t1. ДА." << endl;
			cout << "\t2. НЕТ.";
			do
			{
				ask = 0;
				ask = valueTypeI();

				if (ask != 1 && ask != 2)
				{
					cout << endl
						 << "\tНекорректный ввод (Ответ = 2 -нет).";
					cout << endl
						 << "\tПожалуйста правильно ответьте на вопрос.";
				}

			} while (ask != 1 && ask != 2);

			if (ask == 1)
			{
				char repeat = '\0';

				do
				{
					StationList *temp = nullptr;

					cout << endl;
					dot(26);
					cout << endl
						 << endl;

					cout << "\t=== Введите данные автобуса ===";
					do
					{
						cout << endl
							 << "\tВведите номер автобуса:" << endl;
						cout << "     |" << endl;
						cout << "     '->";
						getline(cin, number);
					} while (number.size() == 0 || number.size() > 8 || (temp = tree.search(number)));
					do
					{
						cout << endl
							 << "\tВведите номер маршрута:" << endl;
						cout << "     |" << endl;
						cout << "     '->";
						getline(cin, route);
					} while (route.size() == 0 || route.size() > 4);
					do
					{
						cout << endl
							 << "\tВведите количество мест в автобусе:";
						seat = valueTypeI();
					} while (seat <= 9 || seat > 150);

					cout << endl
						 << "\t";
					dotdot(50);
					cout << endl
						 << endl;

					cout << "\t=== Введите данные водителя автобуса №" << number << " ===";
					do
					{
						cout << endl
							 << "\tВведите имя" << endl;
						cout << "     |" << endl;
						cout << "     '->";
						getline(cin, name);
					} while (name.size() == 0 || name.size() > 10);
					do
					{
						cout << endl
							 << "\tВведите фамилию" << endl;
						cout << "     |" << endl;
						cout << "     '->";
						getline(cin, surname);
					} while (surname.size() == 0 || surname.size() > 20);

					tree.set(number, name, surname, route, seat);

					cout << "\t";
					dotdot(50);
					cout << endl
						 << "\tY - Добавить еще запись.";
					cout << endl
						 << "     |  Q - Выход в Главное меню.";
					cout << endl
						 << "     '->";
					repeat = cin.get();
					eatline();
				} while (repeat == 'y' || repeat == 'Y');

				install = true;
			}
			if (ask == 2)
			{
				break;
			}
		}
		break;

		case 2:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
				 << endl;

			if (install)
			{
				cout << " ._____________________________________________________________________________." << endl;
				cout << " | № Автобуса |    Данные автобуса    |             Данные водителя            |" << endl;
				cout << " |-----------------------------------------------------------------------------|" << endl;
				if (tree.show() == 1)
					;
				else
				{
					cout << endl;
					cout << "\tБаза данных по автобусному парку пуста." << endl;
					cout << "\tДобавьте данные по автобусному парку (1 или 6 пункт меню)." << endl;
					install = false;
				}
			}
			else
				cout << "\tДобавьте данные по автобусному парку (1 или 6 пункт меню)." << endl;

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			cin.get();
		}
		break;

		case 3:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
				 << endl;

			if (install)
			{
				StationList *temp = nullptr;
				do
				{
					cout << endl
						 << "\tВведите номер автобуса для поиска:" << endl;
					cout << "     |" << endl;
					cout << "     '->";
					getline(cin, number);
				} while (number.size() == 0 || number.size() > 8);

				cout << endl;
				dot(26);
				cout << endl
					 << endl;

				if (temp = tree.search(number))
				{
					cout << " ._____________________________________________________________________________." << endl;
					cout << " | № Автобуса |    Данные автобуса    |             Данные водителя            |" << endl;
					cout << " |-----------------------------------------------------------------------------|" << endl;
					temp->show();
				}
				else
				{
					cout << "\tАвтобус с таким номером не найден." << endl;
				}
			}
			else
				cout << "\tДобавьте данные по автобусному парку (1 или 6 пункт меню)." << endl;

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			cin.get();
		}
		break;

		case 4:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl
				 << endl;

			if (install)
			{
				string ask;
				StationList *temp = nullptr;

				do
				{
					cout << endl
						 << "\tВведите номер автобуса для удаления:" << endl;
					cout << "     |" << endl;
					cout << "     '->";
					getline(cin, number);
				} while (number.size() == 0 || number.size() > 8);

				cout << endl;
				dot(26);
				cout << endl
					 << endl;

				if (temp = tree.search(number))
				{
					cout << " ._____________________________________________________________________________." << endl;
					cout << " | № Автобуса |    Данные автобуса    |             Данные водителя            |" << endl;
					cout << " |-----------------------------------------------------------------------------|" << endl;
					temp->show();

					cout << endl
						 << "\t";
					dotdot(25);
					cout << endl;
					cout << "\tУдалить данные?  (y/n)" << endl;
					cout << "     |" << endl;
					cout << "     '->";
					getline(cin, ask);

					if (!ask.compare("y") || !ask.compare("Y"))
					{
						tree.destroy(number);
						cout << endl;
						cout << "\tВсе данные автобуса №" << number << " удалены." << endl;
					}
				}
				else
					cout << "\tАвтобус с таким номером не найден." << endl;
			}
			else
				cout << "\tДобавьте данные по автобусному парку (1 или 6 пункт меню)." << endl;

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			cin.get();
		}
		break;

		case 5:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
				 << endl
				 << endl;

			if (install)
			{
				int ask;

				cout << "\t   При имеющемся файле (DatаStationBus.txt), файл будет перезаписан." << endl;
				cout << "\t   >>> COХРАНИТЬ <<< ?" << endl;
				cout << "\t1. ДА." << endl;
				cout << "\t2. НЕТ.";
				do
				{
					ask = 0;
					ask = valueTypeI();

					if (ask != 1 && ask != 2)
					{
						cout << endl
							 << "\tНекорректный ввод (Ответ = 2 -нет).";
						cout << endl
							 << "\tПожалуйста правильно ответьте на вопрос.";
					}

				} while (ask != 1 && ask != 2);

				cout << endl;
				dot(26);
				cout << endl
					 << endl;

				if (ask == 1)
				{
					if (tree.save() == 1)
						cout << "\tДанные по автобусному парку успешно сохранены в файл." << endl;
					else
						cout << "\tНе удается открыть файл для записи." << endl;
				}
				if (ask == 2)
				{
					break;
				}
			}
			else
				cout << "\tДобавьте данные по автобусному парку (1 или 6 пункт меню)." << endl;

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			cin.get();
		}
		break;

		case 6:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
				 << endl
				 << endl;

			int ask;

			if (install)
			{
				cout << "\t   Имеющийся данные будут потеряны. (если не были сохранены)" << endl;
				cout << "\t   >>> ЗАГРУЗИТЬ <<< ? (будут загружены данные из файла)" << endl;
				cout << "\t1. ДА." << endl;
				cout << "\t2. НЕТ.";
				do
				{
					ask = 0;
					ask = valueTypeI();

					if (ask != 1 && ask != 2)
					{
						cout << endl
							 << "\tНекорректный ввод (Ответ = 2 -нет).";
						cout << endl
							 << "\tПожалуйста правильно ответьте на вопрос.";
					}

				} while (ask != 1 && ask != 2);

				cout << endl;
				dot(26);
				cout << endl
					 << endl;

				if (ask == 1)
				{
					if (tree.load() == 1)
					{
						cout << "\tФайл считан успешно." << endl;
						install = true;
					}
					else
						cout << "\tНе удается открыть файл для чтения." << endl;
				}
				if (ask == 2)
				{
					break;
				}
			}
			else
			{
				cout << "\t   >>> ЗАГРУЗИТЬ <<< ? (будет загружен массив из файла)" << endl;
				cout << "\t1. ДА." << endl;
				cout << "\t2. НЕТ.";
				do
				{
					ask = 0;
					ask = valueTypeI();

					if (ask != 1 && ask != 2)
					{
						cout << endl
							 << "\tНекорректный ввод (Ответ = 2 -нет).";
						cout << endl
							 << "\tПожалуйста правильно ответьте на вопрос.";
					}

				} while (ask != 1 && ask != 2);

				cout << endl;
				dot(26);
				cout << endl
					 << endl;

				if (ask == 1)
				{
					if (tree.load() == 1)
					{
						cout << "\tФайл считан успешно." << endl;
						install = true;
					}
					else
						cout << "\tНе удается открыть файл для чтения." << endl;
				}
				if (ask == 2)
				{
					break;
				}
			}
			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			cin.get();
		}
		break;

		case 7:
			goback = false;
			break;

		default:
			cout << endl;
			cout << "\tНеверный пункт меню." << endl;
			cout << "\tБудьте внимательны!!!" << endl;
			cout << "\tДля продолжения-<ENTER>";
			cin.get();
			break;
		}

	} while (goback);

	cout << endl
		 << "\t\t\t    ..........................";
	cout << endl
		 << "\t\t\t    |                        |";
	cout << endl
		 << "\t\t\t    |       До свидания      |";
	cout << endl
		 << "\t\t\t    |                        |";
	cout << endl
		 << "\t\t\t    ''''''''''''''''''''''''''" << endl;

	cout << endl;
	dotdot(80);
	cout << endl;
	tabs(9);
	cout << endl;
	equal(80);

	cout << endl
		 << "_ПРОГРАММА ЗАВЕРШЕНА";
	cout << endl
		 << "_____Hажмите-<ENTER>";
	cin.get();

	SetConsoleCP(i1);
	SetConsoleOutputCP(i1);

	return 0;
}

// Tип данных int
int valueTypeI()
{
	int a;

	cout << endl;
	cout << "     |" << endl;
	cout << "     '->";
	cin >> a;
	eatline();

	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();

	return a;
}

//=============================================================================
void dash(int count)
{
	for (int i = 0; i < count; i++)
		cout << "-";
}
void dot(int count)
{
	for (int i = 0; i < count; i++)
		cout << "  .";
}
void dotdot(int count)
{
	for (int i = 0; i < count; i++)
		cout << ".";
}
void equal(int count)
{
	for (int i = 0; i < count; i++)
		cout << "=";
}
void tabs(int count)
{
	for (int i = 0; i < count; i++)
		cout << "\t|";
}
void apostrophe(int count)
{
	for (int i = 0; i < count; i++)
		cout << "`";
}
void underscore(int count)
{
	for (int i = 0; i < count; i++)
		cout << "_";
}
void eatline(void)
{
	cin.clear();
	while (cin.get() != '\n')
	{
		continue;
	}
}
