/*
// 1. Создайте класс Circle (окружность):
//     Реализуйте через перегруженные операторы;
//    - Проверка на равенство радиусов двух окружностей (операция ==);
//    - Сравнения длин двух окружностей (операция >).
//    - Пропорциональное изменение размеров окружности, путем изменения ее радиуса
//      (операция += и -=).

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cmath>

using namespace std;

class Circle
{
private:
    double radius;
    double length;
public:
    Circle();
    Circle(double pRadius, double pLength);
    void set(double pRadius, double pLength);
    void show();

    // создаем прототипы
    bool operator== (Circle& obj2);
    bool operator>  (Circle& obj2);
    bool operator!= (Circle& obj2);
    Circle operator+= (const double num);
    Circle operator-= (const double num);
    const double PI = 3.14; // ПИ - для изменения размеров окружности
};


//--------- ввод/вывод данных -----------------------------
Circle::Circle()
{
    radius = 0;
    length = 0;
}
Circle::Circle(double pRadius, double pLength)
{
    radius = pRadius;
    length = pLength;
}

void Circle::set(double pRadius, double pLength)
{
    this->radius = pRadius;
    this->length = pLength;
}

void Circle::show()
{
    cout << "\tРадиус окружности = "<< radius << endl;
    cout << "\tДлина  окружности = "<< length << endl;
}


//--------- оператор сравнения == -------------------------
bool Circle::operator==(Circle& op2) // сравнение радиусов
{
    if (this->radius == op2.radius)
        return true;
    else
        return false;
}

//--------- оператор сравнения > --------------------------
bool Circle::operator>(Circle& op2) // сравнение длин
{
    if (this->length > op2.length)
        return true;
    else
        return false;
}

//--------- оператор сравнения != -------------------------
bool Circle::operator!= (Circle& op2) // сравнение длин
{
    if (this->length != op2.length)
        return true;
    else
        return false;
}

//--------- перегрузка оператора += -----------------------
Circle Circle::operator+= (const double num)
{
    this->radius += num;
    this->length = 2 * PI * this->radius;
    return *this;
}

//--------- перегрузка оператора -= -----------------------
Circle Circle::operator-= (const double num)
{
    this->radius -= num;
    this->length = 2 * PI * this->radius;
    return *this;
}

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

void displayMenu();
int getValueInt();
double getValueDouble();

///////////////////////////////////////////////////////////

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double radius1 = 0.0;
    double radius2 = 0.0;
    double lengh1 = 0.0;
    double lengh2 = 0.0;
    double pi = 3.14;

    Circle obj1(radius1, lengh1);
    Circle obj2(radius2, lengh2);

    char enter;    // для подтверждения выхода в главное меню
    char repeat;
    int selection; // переменная для выбора меню
    int option;

    bool goback = true;
    bool work = false;

    do
    {
        displayMenu();
        // защита ввода
        do
        {
            selection = 0;
            selection = getValueInt();

        } while (selection <= 0);

        cout << endl;
        switch (selection)
        {
        case 1: // инсталляция величин окружностей
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl;
            cout << "\t1. Задать радиусы окружностей (переопределить)." << endl;
            cout << "\t2.   | Отмена |"; // оставить как есть

            do// защита ввода
            {
                option = 0;
                option = getValueInt();

                if (option != 1 && option != 2)
                {
                    cout << endl << "\tНекорректный ввод (Действие = 2 -отмена).";
                    cout << endl << "\tПожалуйста сделайте выбор.";
                }
            } while (option != 1 && option != 2 );

            cout << endl;
            dot(26);
            cout << endl << endl;

            if (option == 1)
            {
                do
                {
                    cout << "\tВведите радиус Первой окружности.";
                    do
                    {
                        radius1 = 0;
                        radius1 = getValueDouble();

                        if (radius1 <= 0)
                        {
                            cout << endl << "\tРадиус на может иметь отрицательное значение или равным нулю.";
                            cout << endl << "\tБудьте внимательны!!!";
                        }

                    } while (radius1 <= 0);
                    lengh1 = radius1 * 2 * pi;

                    cout << endl<<"\t";
                    dotdot(35);
                    cout << endl;

                    cout << "\tВведите радиус Второй окружности.";
                    do
                    {
                        radius2 = 0;
                        radius2 = getValueDouble();

                        if (radius2 <= 0)
                        {
                            cout << endl;
                            cout << "\tРадиус на может иметь отрицательное значение или равным нулю." << endl;
                            cout << "\tБудьте внимательны!!!" << endl;
                        }

                    } while (radius2 <= 0);
                    lengh2 = radius2 * 2 * pi;

                    obj1.set(radius1, lengh1);
                    obj2.set(radius2, lengh2);
                    work = true;

                    cout << "\t";
                    dotdot(55);
                    cout << endl << "\tY - Заново ввести радиусы окружностей (перезадать).";
                    cout << endl << "     |  Q - Выход в Главное меню.";
                    cout << endl << "     '->";
                    repeat = getche();
                } while (repeat == 'y' || repeat == 'Y');
            }
            break;

        case 2:  // показать значения
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl << endl << endl;
            if (work)
            {
                cout << "\tЗаданы следующие параметры окружностей:" << endl << endl;
                cout << "\tПервая окружность:" << endl;
                obj1.show();
                cout << endl;
                cout << "\tВторая окружность:" << endl;
                obj2.show();
            }
            else
                cout << "\tПараметры окружности не заданны (1 пункт меню).";

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();
            break;

        case 3:  // проверка на равенство (операция ==)
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl << endl << endl;
            if (work)
            {
                cout << "\tПараметры первой окружности:" << endl;
                obj1.show();
                cout << endl;
                cout << "\tПараметры второй окружности:" << endl;
                obj2.show();

                cout << endl;
                dot(26);
                cout << endl << endl;

                cout << "\tРезультат 3 пункта меню:" << endl;
                cout << "\t------------------------" << endl;
                if (obj1 == obj2)
                    cout << "\tРадиусы окружностей равны." << endl;
                else
                    cout << "\tРадиусы окружностей НЕ равны." << endl;
            }
            else
                cout << "\tПараметры окружности не заданы (1 пункт меню).";

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();
            break;

        case 4:  // проверка длин окружностей (операция >)
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl << endl << endl;
            if (work)
            {
                cout << "\tПараметры первой окружности:" << endl;
                obj1.show();
                cout << endl;
                cout << "\tПараметры второй окружности:" << endl;
                obj2.show();

                cout << endl;
                dot(26);
                cout << endl << endl;

                cout << "\tРезультат 4 пункта меню:" << endl;
                cout << "\t------------------------" << endl;
                if (obj1 != obj2)
                {
                    if (obj1 > obj2)
                        cout << "\tДлина первой окружности больше второй." << endl;
                    else
                        cout << "\tДлина первой окружности меньше второй." << endl;
                }
                else
                    cout << "\tДлины равны." << endl;
            }
            else
                cout << "\tПараметры окружности не заданы (1 пункт меню).";

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();
            break;

        case 5:  // пропорциональное изменение размеров окружности
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl << endl << endl;
            if (work)
            {
                cout << "\t1. Пропорциональное изменение размеров окружности (изменение радиуса)." << endl;
                cout << "\t2.   | Отмена |"; // оставить без изменений
                do// защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2)
                    {
                        cout << endl << "\tНекорректный ввод (Действие = 2 -отмена).";
                        cout << endl << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2);

                if (option == 1)
                {
                    double rate1;
                    double rate2;
                    int er;

                    do
                    {
                        cout << endl;
                        dot(26);
                        cout << endl << endl;
                        cout << "\tПараметры первой окружности:" << endl;
                        obj1.show();
                        cout << endl;
                        cout << "\tПараметры второй окружности:" << endl;
                        obj2.show();
                        cout << endl;
                        dot(26);
                        cout << endl << endl;

                        cout << "\tЗадайте значение для изменения радиуса Первой окружности:";
                        do
                        {
                            rate1 = 0;
                            er = 0;
                            rate1 = getValueDouble();

                            if (rate1 < 0)
                            {
                                if (abs(rate1) >= radius1)
                                {
                                    cout << endl;
                                    cout << "\tOшибка!!!" << endl;
                                    cout << "\tЗаданое отрицательное значение превышает радиус окружности.";
                                    er = 1;
                                }
                            }

                        } while (rate1 == 0 || er == 1);

                        cout << endl;
                        cout << "\tЗадайте значение для изменения радиуса Второй окружности:" << endl;
                        do
                        {
                            rate2 = 0;
                            er = 0;
                            rate2 = getValueDouble();

                            if (rate2 < 0)
                            {
                                if (abs(rate2) >= radius2)
                                {
                                    cout << endl;
                                    cout << "\tOшибка!!!" << endl;
                                    cout << "\tЗаданое отрицательное значение превышает радиус окружности." << endl;
                                    er = 1;
                                }
                            }

                        } while (rate2 == 0 || er == 1);

                        cout << endl;
                        dot(26);
                        cout << endl << endl;

                        if (rate1 > 0)
                        {
                            radius1 = radius1 + rate1;
                            obj1 += rate1;
                        }
                        else
                        {
                            radius1 = radius1 - rate1;
                            obj1 -= abs(rate1);
                        }

                        if (rate2 > 0)
                        {
                            radius2 = radius2 + rate2;
                            obj2 += rate2;
                        }
                        else
                        {
                            radius2 = radius2 - rate1;
                            obj2 -= abs(rate2);
                        }

                        cout << "\tРезультат 5 пункта меню:" << endl;
                        cout << "\t----------------------------" << endl;

                        cout << "\tПараметры первой окружности:" << endl;
                        obj1.show();
                        cout << endl;
                        cout << "\tПараметры второй окружности:" << endl;
                        obj2.show();

                        cout << "\t";
                        dotdot(40);
                        cout << endl << "\tY - Повторить пункт 5 (изменить радиусы).";
                        cout << endl << "     |  Q - Выход в Главное меню.";
                        cout << endl << "     '->";
                        repeat = getche();
                    } while (repeat == 'y' || repeat == 'Y');
                }
            }
            else
                cout << "\tПараметры окружности не заданы (1 пункт меню).";

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
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

void displayMenu() // menu options
{
    system("cls");
    equal(80);
    cout << endl;
    tabs(9);
    cout << endl;
    apostrophe(80);
    cout << endl;
    cout << "\t\t\t  ***| Задание 2. Лекция 5 |***" << endl << endl << endl;
    cout << "\t________________________| Главное меню |________________________________" << endl;
    cout << "\t   Выберите ПУНКТ меню:" << endl;
    cout << "\t1. Задать параметры окружностей." << endl;
    cout << "\t2. Просмотр значений окружностей." << endl;
    cout << "\t3. Проверка на равенства радиусов окружностей." << endl;
    cout << "\t4. Сравнения длин двух окружностей." << endl;
    cout << "\t5. Пропорциональное изменение размеров окружности." << endl;
    cout << "\t6.   | ВыхоД |";
}

// проверка ввода int (после ввода)
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

// проверка ввода double (после ввода)
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
void       dash(int count) { for (int i = 0; i < count; i++) cout << "-"; }
void        dot(int count) { for (int i = 0; i < count; i++) cout << "  ."; }
void     dotdot(int count) { for (int i = 0; i < count; i++) cout << "."; }
void      equal(int count) { for (int i = 0; i < count; i++) cout << "="; }
void       tabs(int count) { for (int i = 0; i < count; i++) cout << "\t|"; }
void apostrophe(int count) { for (int i = 0; i < count; i++) cout << "`"; }
void underscore(int count) { for (int i = 0; i < count; i++) cout << "_"; }
void eatline(void) { while (getchar() != '\n') continue; }
*/

// 2. Создать класс (самолет).
//     С помощью перегрузки операторов реализовать:
//     - Проверка на равенство типов самолетов (операция ==);
//     - Увеличение и уменьшение пассажиров в салоне самолета
//       (операции ++ и -- в префиксной форме);
//     - Сравнение двух самолетов по максимально возможному количеству пассажиров
//       на борту (операция>).

#define buff_s 256
#include <iostream>
#include <Windows.h>

using namespace std;

// Создать класс Airplane(самолет).
// С помощью перегрузки операторов реализовать:
// - Проверка на равенство типов самолетов (операция == );
// - Увеличение и уменьшение пассажиров в салоне самолета (операции ++ и -- в префиксной форме);
// - Сравнение двух самолетов по максимально возможному количеству пассажиров на борту (операция >).

class Airplane
{
private:
    static int count;
    char *name;
    int *PassjCount;
    int *MaxPassjCount;

public:
    Airplane()
    {
        name = nullptr;
        PassjCount = nullptr;
        MaxPassjCount = nullptr;
    }
    Airplane(Airplane &source)
    {
        name = new char[strlen(source.name) + 1];
        strcpy_s(name, strlen(source.name) + 1, source.name);
        PassjCount = new int(*source.PassjCount);
        MaxPassjCount = new int(*source.MaxPassjCount);
    }
    ~Airplane()
    {
        delete[] name;
        delete PassjCount;
        delete MaxPassjCount;
    }

    // Добавить самолет
    static void add(Airplane **&airplane)
    {
        Airplane **tmp = new Airplane *[count + 1];
        for (int i = 0; i < count; i++)
            tmp[i] = airplane[i];
        delete[] airplane;
        tmp[count] = new Airplane;
        airplane = tmp;
        count++;
    }

    // Удалить самолет
    static void del(Airplane **&airplane, int del_index)
    {
        Airplane **tmp = new Airplane *[count - 1];
        for (int i = 0; i < count - 1; i++)
            tmp[i] = airplane[i == del_index - 1 ? i + 1 : i];
        delete airplane[del_index - 1];
        delete[] airplane;
        airplane = tmp;
        count--;
    }

    void init(char *name, int PassjCount, int MaxPassjCount)
    {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);

        this->PassjCount = new int;
        *this->PassjCount = PassjCount;

        this->MaxPassjCount = new int;
        *this->MaxPassjCount = MaxPassjCount;
    }

    char *Get_Name() const
    {
        return name;
    }

    int Get_PassjCount() const
    {
        return *PassjCount;
    }

    int Get_MaxPassjCount() const
    {
        return *MaxPassjCount;
    }

    // Проверка на равенство типов самолетов (операция ==)
    bool operator==(Airplane &source)
    {
        return (_stricmp(name, source.name) ? 0 : 1);
    }

    // Увеличение пассажиров в салоне самолета (операции++ )
    void operator++(int f)
    {
        (*PassjCount)++;
    }

    // Уменьшение пассажиров в салоне самолета (операции-- )
    void operator--(int f)
    {
        (*PassjCount)--;
    }

    // Сравнение двух самолетов по максимально возможному
    // количеству пассажиров на борту(операция> )
    bool operator>(Airplane &source)
    {
        return (*MaxPassjCount > *source.MaxPassjCount ? 1 : 0);
    }

    static int Get_Count()
    {
        return count;
    }
};

int Airplane::count = 0;

void print(Airplane *airplane)
{
    cout << "\tТип самолета: " << airplane->Get_Name() << endl;
    cout << "\tКоличество пассажиров: " << airplane->Get_PassjCount() << " (" << airplane->Get_MaxPassjCount() << " макс.)" << endl;
}

bool menu(Airplane **&airplane)
{
    cout << endl;
    cout << "\ta) Добавить самолет." << endl;
    cout << "\tb) Удалить самолет." << endl;
    cout << "\tc) Просмотр всех самолетов." << endl;
    cout << "\td) Сравнение двух самолетов по максимально" << endl;
    cout << "\t   возможному количеству пассажиров на борту." << endl;
    cout << "\te) Увеличение и уменьшение пассажиров в салоне самолета." << endl;
    cout << "\tf) Проверка на равенство типов самолетов." << endl;
    cout << "\tx)    | ВыхоД |" << endl
         << endl;

    char ch;

    do
    {
        cout << "\tВыбор: ";
        cin >> ch;
    } while ((ch < 'a' || ch > 'f') && ch != 'x');

    while (cin.get() != '\n')
        ;
    cout << endl;

    char name[buff_s];
    int maxcount, passjcount, index, n, n2;

    switch (ch)
    {
    case 'a':
    {
        cout << "\tВведите:" << endl;
        cout << "\tТип самолета --> ";
        gets_s(name, buff_s);
        cout << "\tМаксимальное количество пассажиров = ";
        cin >> maxcount;
        cout << "\tКоличество пассажиров = ";
        cin >> passjcount;
        Airplane::add(airplane);
        airplane[Airplane::Get_Count() - 1]->init(name, passjcount, maxcount);
    }
    break;

    case 'b':
    {
        if (!Airplane::Get_Count())
        {
            cout << "\tСамолетов нет." << endl;
            break;
        }
        do
        {
            cout << "\tНомер по списку --> ";
            cin >> index;
        } while (index < 1 || index > Airplane::Get_Count());
        Airplane::del(airplane, index);
    }
    break;

    case 'c':
    {
        if (!Airplane::Get_Count())
        {
            cout << "\tСамолетов нет." << endl;
            break;
        }
        for (int i = 0; i < Airplane::Get_Count(); i++)
        {
            cout << "\t#" << i + 1 << endl;
            print(airplane[i]);
            cout << "\t-------------------------------------" << endl;
        }
    }
    break;

    case 'd':
    {
        if (!Airplane::Get_Count())
        {
            cout << "\tСамолетов нет." << endl;
            break;
        }
        do
        {
            cout << "\tВидите Номер самолета (по списку "
                    "первый"
                    ") --> ";
            cin >> n;
        } while (n < 1 || n > Airplane::Get_Count());
        do
        {
            cout << "\tВидите Номер самолета (по списку второй) --> ";
            cin >> n2;
        } while (n2 < 1 || n2 > Airplane::Get_Count());

        if (*airplane[n - 1] > *airplane[n2 - 1])
            ch = '>';
        else if (*airplane[n2 - 1] > *airplane[n - 1])
            ch = '<';
        else
            ch = '=';

        cout << endl;
        cout << "\tТИП: " << airplane[n - 1]->Get_Name() << " (" << airplane[n - 1]->Get_MaxPassjCount() << " макс. пассажиров) " << ch << " ТИП: " << airplane[n2 - 1]->Get_Name() << " (" << airplane[n2 - 1]->Get_MaxPassjCount() << " макс. пассажиров)\n";
    }
    break;

    case 'e':
    {
        if (!Airplane::Get_Count())
        {
            cout << "\tСамолетов нет" << endl;
            break;
        }
        do
        {
            cout << "\tНомер самолета (по списку): ";
            cin >> index;
        } while (index < 1 || index > Airplane::Get_Count());

        cout << "\ta) Увеличить количество пассажиров" << endl;
        cout << "\tb) Уменьшить количество пассажиров" << endl
             << endl;
        do
        {
            cout << "\tВыбор: ";
            cin >> ch;
        } while (ch < 'a' || ch > 'b');

        switch (ch)
        {
        case 'a':
        {
            do
            {
                cout << "\tСколько пассажиров добавить?: ";
                cin >> n;
            } while (n < 1 || n > airplane[index - 1]->Get_MaxPassjCount());
            for (int i = 0; i < n; i++)
                (*airplane[index - 1])++;
        }
        break;

        case 'b':
        {
            do
            {
                cout << "\tСколько пассажиров удалить?: ";
                cin >> n;
            } while (n < 1);
            for (int i = 0; i < n; i++)
                (*airplane[index - 1])--;
        }
        break;
        }
    }
    break;

    case 'f':
    {
        if (!Airplane::Get_Count())
        {
            cout << "\tСамолетов нет" << endl;
            break;
        }
        do
        {
            cout << "\tВведите Номер самолета (по списку первый) -->";
            cin >> n;
        } while (n < 1 || n > Airplane::Get_Count());
        do
        {
            cout << "\tВведите Номер самолета (по списку первый) --> ";
            cin >> n2;
        } while (n2 < 1 || n2 > Airplane::Get_Count());

        cout << endl;
        cout << "\tТИП: " << airplane[n - 1]->Get_Name() << " " << (*airplane[n - 1] == *airplane[n2 - 1] ? "=" : "!=") << " ТИП: " << airplane[n2 - 1]->Get_Name() << endl;
    }
    break;

    case 'x':
        return 0;
    }

    cout << endl;

    return 1;
}

int main()
{
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Airplane **airplane = nullptr;

    while (menu(airplane) != 0)
        ;
    delete[] airplane;
}

