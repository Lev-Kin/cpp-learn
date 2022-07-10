/*
// 1. Создайте класс Date, который будет содержать информацию о дате (день,
//     месяц, год). С помощью механизма перегрузки операторов, определите операцию
//     разности двух дат (результат в виде количества дней между датами), а также
//     операцию увеличения даты на определённое количество дней.

#include <Windows.h>
#include <iostream>
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

int getValue();

///////////////////////////////////////////////////////////

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date(); //конструктор по умолчанию
    Date(int day, int month, int year); //конструктор параметры
    void set(int day, int month, int year);
    void show(char symb = '.'); //печать
    int daysAm();
    void intToDate(int days);
    int operator - (const Date& Obj);
    Date operator + (const int days);
    operator int();
};

//--------- ввод/вывод данных -----------------------------
Date::Date()
{
    day = 0;
    month = 0;
    year = 0;
}
Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}
void Date::set(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}
void Date::show(char symb)
{
    if (day < 10)
        cout << 0;
    cout << day;
    cout << symb;
    if (month < 10)
        cout << 0;
    cout << month;
    cout << symb << year << '\n';
}

//-------------- перегрузка минуса ------------------------
int Date::operator - (const Date& Obj)
{
    Date temp = Obj;
    int res = int(*this) - int(temp) - 1;
    return res;
}

//-------------- перегрузка плюса -------------------------
Date Date::operator+ (const int days)
{
    int dayCount = daysAm() + days;
    intToDate(dayCount);
    return *this;
}

Date::operator int()
{
    return daysAm();
}

void Date::intToDate(int dayCount)
{
    year = 0;
    int daysinyear = 365;
    for (dayCount; dayCount > daysinyear; )
    {
        dayCount -= daysinyear;
        year++;
        if ((year + 1) % 4 == 0 || ((year + 1) % 100 == 0 && (year + 1) % 400 == 0))
            daysinyear = 366;
        else daysinyear = 365;
    }
    year++;
    month = 1;
    int daysinmonth = 31;
    while (dayCount > daysinmonth)
    {
        dayCount -= daysinmonth;
        month++;
        if (month == 1)
            daysinmonth = 31;
        else
            if (month == 2)
            {
                if ((year) % 4 == 0 || ((year) % 100 == 0 && (year) % 400 == 0))
                    daysinmonth = 29;
                else
                    daysinmonth = 28;
            }
            else
                if (month == 3)
                    daysinmonth = 31;
                else
                    if (month == 4)
                        daysinmonth = 30;
                    else
                        if (month == 5)
                            daysinmonth = 31;
                        else
                            if (month == 6)
                                daysinmonth = 30;
                            else
                                if (month == 7)
                                    daysinmonth = 31;
                                else
                                    if (month == 8)
                                        daysinmonth = 31;
                                    else
                                        if (month == 9)
                                            daysinmonth = 30;
                                        else
                                            if (month == 10)
                                                daysinmonth = 31;
                                            else
                                                if (month == 11)
                                                    daysinmonth = 30;
                                                else
                                                    if (month == 12)
                                                        daysinmonth = 31;

    }
    if (dayCount == 0)
        day = 1;
    else
        day = dayCount;
}

int Date::daysAm()
{
    bool visokosniy = false;

    if (year % 4 == 0 || (year % 100 == 0 && year % 400 == 0))
        visokosniy = true;
    int amDays = (year - 1) * 365 + (year - 1) / 4 - ((year - 1) % 400 != 0 && (year - 1) % 100 == 0) + day;
    for (int i = 2; i <= month; i++)
    {
        if (i == 2)
            amDays += 31;
        else
            if (i == 3)
            {
                if (visokosniy)
                    amDays += 29;
                else
                {
                    amDays += 28;
                }
            }
            else
                if (i == 4)
                    amDays += 31;
                else
                    if (i == 5)
                        amDays += 30;
                    else
                        if (i == 6)
                            amDays += 31;
                        else
                            if (i == 7)
                                amDays += 30;
                            else
                                if (i == 8)
                                    amDays += 31;
                                else
                                    if (i == 9)
                                        amDays += 31;
                                    else
                                        if (i == 10)
                                            amDays += 30;
                                        else
                                            if (i == 11)
                                                amDays += 31;
                                            else
                                                if (i == 12)
                                                    amDays += 30;
    }
    return amDays;
}


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
    cout << "\t\t   ***| Программа работы с датами |***" << endl << endl << endl;

    int day1, month1, year1;
    int day2, month2, year2;

    Date someday;

    cout << "\t\t=== I. Определение разности двух дат ===" << endl << endl;
    cout << "\tПервая дата:" << endl;
    cout << "\t";
    dash(42);
    cout << endl;

    // защита ввода первая дата
    while (true)
    {
        cout << "\tВведите день, месяц и год (18 11 2019)" << endl;
        cout << "     |  через пробел или через ENTER первой даты:" << endl;
        cout << "     '->";
        cin >> day1 >> month1 >> year1;

        if (day1 > 0 && day1 < 32 && month1 > 0 && month1 < 13) break;

        cout << endl;
        cout << "\tДата введена некорректно!"<< endl<<endl;
    }
    someday.set(day1, month1, year1);

    cout << endl;
    cout << "\tПервая дата следушая --> ";
    someday.show();

    cout << endl;
    dot(26);
    cout << endl << endl;

    Date someDays;

    cout << "\tВторая дата:" << endl;
    cout << "\t";
    dash(42);
    cout << endl;

    // защита ввода вторая дата
    while (true)
    {
        cout << "\tВведите день, месяц и год (02 02 2020)" << endl;
        cout << "     |  через пробел или через ENTER первой даты:" << endl;
        cout << "     '->";
        cin >> day2 >> month2 >> year2;

        if (day2 > 0 && day2 < 32 && month2 > 0 && month2 < 13) break;

        cout << endl;
        cout << "\tДата введена некорректно!" << endl << endl;
    }
    someDays.set(day2, month2, year2);

    cout << endl;
    cout << "\tВторая дата следушая --> ";
    someDays.show();

    cout << endl;
    dash(80);
    cout << endl << endl;

    cout << "\tРезультат I:" << endl;
    cout << "\t";
    dash(42);
    cout << endl;

    if (year1 > year2)
    {
        int res = someday - someDays;
        cout << "\tРазница между датами составила " << res << " дня." << endl;
    }
    else
    {
        int res = someDays - someday;
        cout << "\tРазница между датами составила " << res << " дня." << endl;
    }

    cout << endl;
    dash(80);
    cout << endl << endl;

    cout << "\t\t=== II. Определение даты при добавлении дней ===" << endl << endl;
    cout << "\tПеравая дата: ";
    someday.show();
    cout << "\tВторая  дата: ";
    someDays.show();
    cout << endl;

    int days;
    int keys;

    cout << "\tК какой дате прибавить дни:" << endl;
    cout << "\t1 - к первой дате." << endl;
    cout << "\t2 - ко второй дате." << endl;
    cout << "\t3 - выход";
    do// защита ввода
    {
        keys = 0;
        keys = getValue();

        if (keys != 1 && keys != 2 && keys != 3)
        {
            cout << endl << "\tНекорректный ввод (Действие = 3 -выход).";
            cout << endl << "\tПожалуйста сделайте выбор.";
        }
    } while (keys != 1 && keys != 2 && keys != 3);

    if (keys == 1)
    {
        cout << endl;
        cout << "\tСколько прибавить к дате:";

        // защита ввода дни
        do
        {
            days = 0;
            days = getValue();

        } while (days <= 0);

        someday = someday + days;

        cout << endl;
        dash(80);
        cout << endl << endl;

        cout << "\tРезультат II:" << endl;
        cout << "\t";
        dash(42);
        cout << endl << "\t";
        someday.show('.');
    }
    if (keys == 2)
    {
        cout << endl;
        cout << "\tСколько прибавить к дате:";

        // защита ввода дни
        do
        {
            days = 0;
            days = getValue();

        } while (days <= 0);

        someday = someDays + days;

        cout << endl;
        dash(80);
        cout << endl << endl;

        cout << "\tРезультат II:" << endl;
        cout << "\t";
        dash(42);
        cout << endl << "\t";
        someday.show('.');
    }

    cout << endl << endl;
    dotdot(80);
    cout << endl;
    tabs(9);
    cout << endl;
    equal(80);

    SetConsoleCP(i1);
    SetConsoleOutputCP(i1);

    return 0;
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

// проверка ввода int (после ввода)
int getValue()
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
*/

// 2. Добавить в строковый класс функцию, которая создаёт строку, содержащую
//     пересечение двух строк, то есть общие символы для двух строк. Например,
//     результатом пересечения строк "sdqcg" "rgfas34" будет строка "sg". Для
//     реализации функции перегрузить оператор * (бинарное умножение).

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>

using namespace std;

//////////////////////////////////////////////////////

void dash(int);
void dot(int);
void dotdot(int);
void equal(int);
void tabs(int);
void apostrophe(int);
void underscore(int);
void eatline(void);

//////////////////////////////////////////////////////

class String
{
    char str[81];
    char result[81];

public:
    void input();
    void show();
    String operator*(String op2);
};

void String::input()
{
    gets_s(str, 80);
}
void String::show()
{
    cout << result << endl;
}

String String::operator*(String op2)
{
    String temp;
    int position = 0;
    int size1, size2;
    size1 = (int)strlen(str);
    size2 = (int)strlen(op2.str);

    // Производим сравнение двух строк
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2; j++)
        {
            // Проверяем что этот символ уже не встречался ранее
            if (str[i] == op2.str[j])
            {
                int symbol = 0;
                for (int k = 0; k < position; k++)
                {
                    if (op2.str[j] == result[k])
                    {
                        symbol++;
                        break;
                    }
                }
                if (symbol == 0)
                {
                    temp.result[position] = op2.str[j];
                    position++;
                }
            }
        }
    }
    temp.result[position] = '\0';
    return temp;
}

int main(void)
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
    cout << "\t   ***| Программа нахождения общих символов двух строк |***" << endl
         << endl
         << endl;

    String a, b, c;

    cout << "\tВведите первую строку:" << endl;
    cout << " [str]  ";
    a.input();

    cout << "\n\tВведите вторую строку:" << endl;
    cout << " [str]  ";
    b.input();

    cout << endl;
    dash(80);
    cout << endl;

    c = a * b;

    cout << endl;
    cout << "\tРезультат из двух введенных строк:" << endl;
    cout << " [str]  ";
    c.show();

    cout << endl
         << endl;
    dotdot(80);
    cout << endl;
    tabs(9);
    cout << endl;
    equal(80);

    SetConsoleCP(i1);
    SetConsoleOutputCP(i1);

    return 0;
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
