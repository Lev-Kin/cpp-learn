// Задание 1.
// Реализуйте класс Дробь.
// Необходимо хранить числитель и знаменатель в качестве переменных-членов.
// Реализуйте функции-члены:
// - для ввода данных в переменные-члены;
// - для выполнения арифметических операций (сложение, вычитание, умножение,
//   деление).

#include <windows.h>
#include <iostream>
#define N 11

using namespace std;

///////////////////////////////////////////////////////////

void dash(int);
void dot(int);
void dotdot(int);
void equal(int);
void tabs(int);
void apostrophe(int);
void underscore(int);

///////////////////////////////////////////////////////////

class Fraction
{
private:
    int ch, zn, ch_1, zn_1, ch_2, zn_2, whole;

public:
    Fraction(int chisl_1, int znam_1, int chisl_2, int znam_2);
    void optimization();
    void sum();
    void difference();
    void multiply();
    void divide();
    int get_ch() // функция получения значения числителя
    {
        return ch;
    }
    int get_zn() // функция получения значения знаменателя
    {
        return zn;
    }
    int get_whole() // функция получения значения целого
    {
        return whole;
    }
};

// конструктор (ввод данных в переменные-члены)
Fraction::Fraction(int chisl_1, int znam_1, int chisl_2, int znam_2)
{
    ch_1 = chisl_1;
    zn_1 = znam_1;
    ch_2 = chisl_2;
    zn_2 = znam_2;
    whole = 0;
}

// функция оптимизации
void Fraction::optimization()
{
    if (ch % zn == 0)
    {
        whole = ch / zn;
        zn = 0; // выставляем флаг что у нас только целое число
    }
    else if ((ch / zn) != 0)
    {
        whole = ch / zn;
        ch %= zn;
        ch = abs(ch); // убираем минус у числителя если отрицательное значение
    }

    if (ch < zn)
    {
        for (int i = 10; i > 1; i--) //перебираем возможные варианты общего делителя числителя и знаменателя
        {
            if (ch % i == 0 && zn % i == 0)
            {
                ch /= i;
                zn /= i;
                i = 10;
            }
        }
    }
}

// функция сложения
void Fraction::sum()
{
    if (zn_1 == zn_2)
    {
        zn = zn_1;
        ch = ch_1 + ch_2;
    }
    else if (zn_1 % zn_2 == 0)
    {
        zn = zn_1;
        ch = ch_2 * (zn_1 / zn_2) + ch_1;
    }
    else if (zn_2 % zn_1 == 0)
    {
        zn = zn_2;
        ch = ch_1 * (zn_2 / zn_1) + ch_2;
    }
    else
    {
        zn = zn_1 * zn_2;
        ch = ch_1 * zn_2 + ch_2 * zn_1;
    }
}

// функция вычитания
void Fraction::difference()
{
    if (zn_1 == zn_2)
    {
        zn = zn_1;
        ch = ch_1 - ch_2;
    }
    else if (zn_1 % zn_2 == 0)
    {
        zn = zn_1;
        ch = ch_2 * (zn_1 / zn_2) - ch_1;
    }
    else if (zn_2 % zn_1 == 0)
    {
        zn = zn_2;
        ch = ch_1 * (zn_2 / zn_1) - ch_2;
    }
    else
    {
        zn = zn_1 * zn_2;
        ch = ch_1 * zn_2 - ch_2 * zn_1;
    }
}

// функция умножения
void Fraction::multiply()
{
    ch = ch_1 * ch_2;
    zn = zn_1 * zn_2;
}

// функция деления
void Fraction::divide()
{
    ch = ch_1 * zn_2;
    zn = zn_1 * ch_2;
}

void parsing(char *buffer, int &chisl, int &znam);
void print(Fraction f, char *str1, char *str2, char *op, int choice);

int main()
{
    system("cls");
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    equal(80);
    cout << endl;
    tabs(9);
    cout << endl;
    apostrophe(80);
    cout << endl;
    cout << "\t     ***| Задание 1. Лекция 1. Реализация класса дробь |***" << endl
         << endl
         << endl;

    int ch_1, zn_1, ch_2, zn_2, choice, n = 0;
    char str1[N], str2[N], op[4] = {'+', '-', '*', '/'};

    cout << "\tПример ввода чисел: 1/2, 2/6, 3/4 и т.д." << endl;
    do
    {
        n++;
        int work = 1;
        cout << endl;
        cout << "\t=========================================" << endl;
        cout << "\t|\t\tРасчет № " << n << "\t\t|" << endl;
        cout << "\t=========================================" << endl;
        cout << "\tВведите 1 число: ";
        cin >> str1;
        cout << "\tВведите 2 число: ";
        cin >> str2;
        parsing(str1, ch_1, zn_1);
        parsing(str2, ch_2, zn_2);
        Fraction f(ch_1, zn_1, ch_2, zn_2);
        cout << endl;
        cout << "\tВыберите арифметическую операцию:" << endl;
        cout << "\t1 - сложение:\t" << str1 << " " << op[0] << " " << str2 << endl;
        cout << "\t2 - вычитание:\t" << str1 << " " << op[1] << " " << str2 << endl;
        cout << "\t3 - умножение:\t" << str1 << " " << op[2] << " " << str2 << endl;
        cout << "     |  4 - деление:\t" << str1 << " " << op[3] << " " << str2 << endl;
        cout << "     '->";
        cin >> choice;
        switch (choice)
        {
        case 1:
            f.sum();
            f.optimization();
            print(f, str1, str2, op, choice);
            break;
        case 2:
            f.difference();
            f.optimization();
            print(f, str1, str2, op, choice);
            break;
        case 3:
            f.multiply();
            f.optimization();
            print(f, str1, str2, op, choice);
            break;
        case 4:
            f.divide();
            f.optimization();
            print(f, str1, str2, op, choice);
            break;

        default:
            cout << endl;
            cout << "\tОшибка! Неправильный ввод!" << endl;
            work = 0;
            choice = 0;
        }

        if (work == 1)
        {
            cout << endl;
            cout << "\tЖелаете продолжить вычисления?" << endl;
            cout << "\t1 - Да." << endl;
            cout << "     |  0 - Нет" << endl;
            cout << "     '->";
            cin >> choice;
        }

    } while (choice);

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

// функция парсинга строки (формируем числитель и знаменатель) - для целей удобочитаемости ввода (например 1/2, 2/6 и т.д)
void parsing(char *buffer, int &chisl, int &znam)
{
    char *word, *next;
    char tmp[N];
    strcpy_s(tmp, buffer);
    word = strtok_s(tmp, "/\n", &next);
    chisl = atoi(word);
    if (*next == '\0')
    {
        znam = 1;
    }
    else
    {
        word = strtok_s(NULL, "\n", &next);
        znam = atoi(word);
    }
}

// функция печати
void print(Fraction f, char *str1, char *str2, char *op, int choice)
{
    cout << "\n\tОтвет: "
         << "\t" << str1 << " " << op[choice - 1] << " " << str2 << " = ";
    if (f.get_whole() && f.get_zn())
    {
        cout << f.get_whole() << " " << f.get_ch() << "/" << f.get_zn() << endl;
    }
    else if (f.get_zn() == 0)
    {
        cout << f.get_whole() << endl;
    }
    else
    {
        cout << f.get_ch() << "/" << f.get_zn() << endl;
    }
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
