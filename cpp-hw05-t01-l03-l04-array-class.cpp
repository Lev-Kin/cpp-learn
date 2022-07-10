// Создайте класс Array .
// Класс Array - это класс динамического массива.
// Размер массива может быть передан в качестве параметра или задан с помощью вызова функции-члена.
// Класс должен позволять заполнять массив значениями, отображать содержимое массива, изменять
// размер массива, отсортировать массив, определять минимальное и максимальное значение.
// Класс должен содержать набор конструкторов (конструктор копирования обязателен), деструктор.

#include <windows.h>
#include <conio.h>
#include <iostream>
// в заголовочном файле <ctime> содержится прототип функции time()
#include <ctime>
// в заголовочном файле <iomanip> содержится прототип функции setprecision(), setw()
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////

void dash(int);
void dot(int);
void dotdot(int);
void equal(int);
void tabs(int);
void apostrophe(int);
void underscore(int);
void eatline(void);

///////////////////////////////////////////////////////////

int getValueInt();
double getValueDouble();

///////////////////////////////////////////////////////////

class Array
{

public:
	int size;
	double *array;
	Array()
	{
		size = 0;
		array = new double[size];
	}
	Array(const Array &obj)
	{
		size = obj.size;
		array = new double[size];
		for (int i = 0; i < size; i++)
		{
			array[i] = obj.array[i];
		}
	}
	~Array()
	{
		delete[] array;
		array = nullptr;
	}
	void initialize(int n);
	void inputArray();
	void inputArrayRandom();
	void outputArray();
	void sortArray();
	void reinitialize(int resize, int select);
	int maxIndex();
	int minIndex();
	double maxElement();
	double minElement();
};

//=============================================================================
void Array::initialize(int n)
{
	size = n;
	array = new double[size];
}

void Array::inputArray()
{
	for (int i = 0; i < size; i++)
	{
		do
		{
			cout << endl
				 << "\tВведите [" << i << "] элемент массива:";
			array[i] = getValueDouble();

		} while (array[i] < -10 || array[i] > 10);
	}
}

void Array::inputArrayRandom()
{

	for (int i = 0; i < size; i++)
	{
		//заполнение массива случайными числами с масштабированием от -10 до 10
		array[i] = (rand() % 21 - 10) / float((rand() % 10 + 1));
	}
}

void Array::outputArray()
{
	cout << "\tМассив данных:" << endl
		 << endl
		 << "\t";
	for (int i = 0; i < size; i++)
	{
		if (i < 10)
		{
			cout << " [" << i << "] = " << setprecision(2) << setw(8) << left << array[i];
			if ((i + 1) % 5 == 0)
				cout << endl
					 << "\t";
		}
		else if (i >= 100)
		{
			cout << "[" << setw(3) << i << "] = " << setprecision(2) << setw(7) << left << array[i];
			if ((i + 1) % 5 == 0)
				cout << endl
					 << "       ";
		}
		else
		{
			cout << "[" << setw(2) << i << "] = " << setprecision(2) << setw(8) << left << array[i];
			if ((i + 1) % 5 == 0)
				cout << endl
					 << "\t";

			if (i == 99)
				cout << endl
					 << "       ";
		}
	}
}

void Array::sortArray()
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (array[i] > array[j])
			{
				double temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

void Array::reinitialize(int resize, int select)
{
	if (resize <= size)
	{
		double *array_new = new double[resize];
		for (int i = 0; i < resize; i++)
		{
			array_new[i] = array[i];
		}
		delete[] array;
		array = array_new;
		size = resize;
	}
	if (resize > size && select == 1)
	{
		double *array_new = new double[resize];
		for (int i = 0; i < resize; i++)
		{
			array_new[i] = array[i];
		}
		for (int i = size; i < resize; i++)
		{
			//заполнение массива случайными числами с масштабированием от -10 до 10
			array_new[i] = (rand() % 21 - 10) / float((rand() % 10 + 1));
		}
		delete[] array;
		array = array_new;
		size = resize;
	}
	else
	{
		double *array_new = new double[resize];
		for (int i = 0; i < resize; i++)
		{
			array_new[i] = array[i];
		}
		for (int i = size; i < resize; i++)
		{
			do
			{
				cout << endl
					 << "\tВведите [" << i << "] элемент массива:";
				array_new[i] = getValueDouble();

			} while (array_new[i] < -10 || array_new[i] > 10);
		}
		delete[] array;
		array = array_new;
		size = resize;
	}
}

int Array::maxIndex()
{
	int j = 0;
	double max = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] > max)
			j = i;
	}
	return j;
}
int Array::minIndex()
{
	int j = 0;
	double min = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min)
			j = i;
	}
	return j;
}

double Array::maxElement()
{
	double max = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	return max;
}
double Array::minElement()
{
	double min = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min)
			min = array[i];
	}
	return min;
}

//=============================================================================
int main()
{
	int i1 = GetConsoleCP();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned int)time(nullptr));

	Array array;

	int size;
	int resize;

	int menu;
	int option;
	int select = 0;
	char enter;

	bool install = false;
	bool operate = false;
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
		cout << "\t\t\t      ***| Класс Array |***" << endl
			 << endl
			 << endl;
		cout << "\t________________________| Главное меню |________________________________" << endl;
		cout << "\t   Выберите ПУНКТ меню:" << endl;
		cout << "\t1. Задать параметры массива." << endl;
		cout << "\t2. Просмотр значений массива." << endl;
		cout << "\t3. Редактирование массива." << endl;
		cout << "\t4. Сортировка массива." << endl;
		cout << "\t5. Нахождение min и max значения массива." << endl;
		cout << "\t6.   | ВыхоД |";
		do
		{
			menu = 0;
			menu = getValueInt();

		} while (menu <= 0);

		cout << endl;

		switch (menu)
		{
		case 1: // инсталляция
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
				 << endl
				 << endl;
			cout << "\t1. Заполнить массив случайными числами." << endl;
			cout << "\t2. Заполнить массив вручную." << endl;
			cout << "\t3.   | Отмена |"; // оставить как есть

			do // защита ввода
			{
				option = 0;
				option = getValueInt();

				if (option != 1 && option != 2 && option != 3)
				{
					cout << endl
						 << "\tНекорректный ввод (Действие = 3 -отмена).";
					cout << endl
						 << "\tПожалуйста сделайте выбор.";
				}
			} while (option != 1 && option != 2 && option != 3);

			cout << endl;
			dot(26);
			cout << endl
				 << endl;

			if (option == 1)
			{
				if (install == false)
				{

					cout << "\tВведите размер массива (1 - 100): ";
					do
					{
						size = getValueInt();

					} while (size <= 0 || size > 100);

					array.initialize(size);
					array.inputArrayRandom();

					cout << endl
						 << "\tМассив инициализирован." << endl;
					operate = true;
					install = true;
				}
				else
				{
					cout << endl
						 << "\tМассив инициализирован.";
					cout << endl
						 << "\tДля редактирования массива воспользуйтесь 3 пунктом меню." << endl;
				}

				cout << endl;
				dotdot(80);
				cout << endl;
				tabs(9);
				cout << endl;
				equal(80);
				cout << endl
					 << "\tВернутся в главное меню нажмите-<ENTER>";
				enter = getche();
			}
			if (option == 2)
			{
				if (install == false)
				{

					cout << "\tВведите размер массива (1 - 100): ";
					do
					{
						size = getValueInt();

					} while (size <= 0 || size > 100);

					array.initialize(size);
					array.inputArray();

					cout << endl
						 << "\tМассив инициализирован." << endl;
					operate = true;
					install = true;
				}
				else
				{
					cout << endl
						 << "\tМассив инициализирован.";
					cout << endl
						 << "\tДля редактирования массива воспользуйтесь 3 пунктом меню." << endl;
				}

				cout << endl;
				dotdot(80);
				cout << endl;
				tabs(9);
				cout << endl;
				equal(80);
				cout << endl
					 << "\tВернутся в главное меню нажмите-<ENTER>";
				enter = getche();
			}
		}
		break;

		case 2:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
				 << endl
				 << endl;

			if (operate)
			{
				array.outputArray();
			}
			else
				cout << "\tПараметры массива не заданы (1 пункт меню).\n";

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			enter = getche();
		}
		break;

		case 3:
		{
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
				 << endl
				 << endl;

			if (operate)
			{
				cout << "\t1. Создать новый массив." << endl;
				cout << "\t2. Изменения массива с сохранением значений." << endl;
				cout << "\t3.   | Отмена |"; // оставить как есть

				do // защита ввода
				{
					option = 0;
					option = getValueInt();

					if (option != 1 && option != 2 && option != 3)
					{
						cout << endl
							 << "\tНекорректный ввод (Действие = 3 -отмена).";
						cout << endl
							 << "\tПожалуйста сделайте выбор.";
					}
				} while (option != 1 && option != 2 && option != 3);

				cout << endl;
				dot(26);
				cout << endl
					 << endl;

				if (option == 1)
				{
					cout << "\tВведите размер массива (1 - 100):";
					do
					{
						resize = getValueInt();

					} while (resize <= 0 || resize > 100);

					cout << endl
						 << "\t";
					dotdot(40);
					cout << endl;
					cout << "\t1. Заполнить массив случайными числами." << endl;
					cout << "\t2. Заполнить массив вручную." << endl;
					cout << "\t3.   | Отмена |"; // оставить как есть

					do // защита ввода
					{
						select = 0;
						select = getValueInt();

						if (select != 1 && select != 2 && select != 3)
						{
							cout << endl
								 << "\tНекорректный ввод (Действие = 3 -отмена).";
							cout << endl
								 << "\tПожалуйста сделайте выбор.";
						}
					} while (select != 1 && select != 2 && select != 3);

					if (select == 1)
					{
						array.initialize(resize);
						array.inputArrayRandom();

						cout << endl
							 << "\tМассив создан заново." << endl;
					}
					if (select == 2)
					{
						array.initialize(resize);
						array.inputArray();

						cout << endl
							 << "\tМассив создан заново." << endl;
					}
				}
				if (option == 2)
				{
					cout << "\tВведите новый размер включая существующий массив (1 - 200):";
					do
					{
						resize = getValueInt();

					} while (resize <= 0 || resize > 200);

					cout << endl
						 << "\t";
					dotdot(40);
					cout << endl;
					cout << "\t1. Заполнить массив случайными числами." << endl;
					cout << "\t2. Заполнить массив вручную." << endl;
					cout << "\t3.   | Отмена |"; // оставить как есть

					do // защита ввода
					{
						select = 0;
						select = getValueInt();

						if (select != 1 && select != 2 && select != 3)
						{
							cout << endl
								 << "\tНекорректный ввод (Действие = 3 -отмена).";
							cout << endl
								 << "\tПожалуйста сделайте выбор.";
						}
					} while (select != 1 && select != 2 && select != 3);

					if (select == 1)
					{
						array.reinitialize(resize, select);
						if (resize <= size)
						{
							cout << endl
								 << "\tРазмер массива изменен (уменьшен).";
							cout << endl
								 << "\tЭлементы вошедшие в диапазон массива остались без изменений." << endl;
							size = resize;
						}
						else
						{
							cout << endl
								 << "\tРазмер массива изменен (увеличен).";
							cout << endl
								 << "\tВ массив успешно добавлены случайные элементы." << endl;
							size = resize;
						}
					}
					if (select == 2)
					{
						array.reinitialize(resize, select);
						if (resize <= size)
						{
							cout << endl
								 << "\tРазмер массива изменен (уменьшен).";
							cout << endl
								 << "\tЭлементы вошедшие в диапазон массива остались без изменений." << endl;
							size = resize;
						}
						else
						{
							cout << endl
								 << "\tРазмер массива изменен (увеличен).";
							cout << endl
								 << "\tВ массив успешно добавлены случайные элементы." << endl;
							size = resize;
						}
					}
				}
			}
			else
				cout << "\tПараметры массива не заданы (1 пункт меню).\n";

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			enter = getche();
		}
		break;

		case 4:
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl
				 << endl
				 << endl;

			if (operate)
			{
				array.sortArray();
				cout << "\tЭлементы массива отсортированы по возрастанию.\n";
			}
			else
				cout << "\tПараметры массива не заданы (1 пункт меню).\n";

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			enter = getche();
			break;

		case 5:
			dash(80);
			cout << endl;
			cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
				 << endl
				 << endl;

			if (operate)
			{
				cout << "\tМинимальный  элемент массива:" << endl;
				cout << "\t[" << array.minIndex() << "] = " << array.minElement() << endl
					 << endl;
				cout << "\tМаксимальный элемент массива:" << endl;
				cout << "\t[" << array.maxIndex() << "] = " << array.maxElement() << endl;
			}
			else
				cout << "\tПараметры массива не заданы (1 пункт меню).\n";

			cout << endl;
			dotdot(80);
			cout << endl;
			tabs(9);
			cout << endl;
			equal(80);
			cout << endl
				 << "\tВернутся в главное меню нажмите-<ENTER>";
			enter = getche();
			break;

		case 6:
			goback = false;
			break;

		default:
			cout << endl;
			cout << "\tНеверный пункт меню." << endl;
			cout << "\tБудьте внимательны!!!" << endl;
			cout << "\tДля продолжения-<ENTER>";
			enter = getch();
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

	SetConsoleCP(i1);
	SetConsoleOutputCP(i1);

	return 0;
}

// проверка ввода int
int getValueInt()
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

// проверка ввода double
double getValueDouble()
{
	double d;
	cout << endl;
	cout << "     |" << endl;
	cout << "     '->";
	cin >> d;
	eatline();

	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();

	return d;
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
	while (getchar() != '\n')
		continue;
}
