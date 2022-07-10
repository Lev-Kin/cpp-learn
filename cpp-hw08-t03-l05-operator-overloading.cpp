/*
// 1. Создайте класс Date, который будет содержать информацию о дате (день, месяц, год).
// С помощью механизма перегрузки операторов, определите
// операцию разности двух дат (результат в виде количества дней между датами), а также операцию увеличения даты на определенное количество дней.
// В классе должна быть функция-член, которая увеличивает день на 1.
// Напишите соответствующие конструкторы и функции-члены.
// В классе по необходимости должны быть перегружены операции ++, -- ,
// !=, ==, >, <, >>, <<, =, +=, -=, ().
// Используйте обычную и дружественную перегрузку.


#include <windows.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

class date_
{
    int day;
    int month;
    int year;
public:
    date_()
    {
        day = 1;
        month = 1;
        year = 1;
    };
    date_(const date_& d)
    {
        day = d.day;
        month = d.month;
        year = d.year;
    }
    int Day() const
    {
        return day;
    }
    int Month() const
    {
        return month;
    }
    int Year() const
    {
        return year;
    }
    void setDate();																//ввод значения даты с клавиатуры
    date_ nextDay();															//функция член для увеличения даты на 1 день
    void showDate()																//вывод даты на экран
    {
        cout << day << "." << month << "." << year << endl;
    }
    void getSysDate();															//получение системной даты
    int operator - (const date_& D);											//перегрузка оператора "-" для подсчета разницы между датами в днях
    friend date_ operator + (date_ D, int days);								//дружественная перегрузка оператора "+" для увеличения даты на заданное количество дней
};

void date_::getSysDate()
{
    SYSTEMTIME sd;																//получение системной даты
    GetSystemTime(&sd);
    day = sd.wDay;
    month = sd.wMonth;
    year = sd.wYear;
}

void date_::setDate()															//ввод значения даты с клавиатуры
{
    cout << "\nВведите через enter число, месяц, год\n";
    cin >> day;
    while (getchar() != '\n');
    if (day < 1 || day > 31)
        do
        {
            cout << "\nЧисло должно быть положительным и не больше 31!\nПопробуйте еще раз:\n";
            cin >> day;
        } while (day < 1 || day > 31);
        cin >> month;
        while (getchar() != '\n');
        if (month < 1 || month > 12)
            do
            {
                cout << "\nНомер месяца - число от 1 до 12!\nПопробуйте еще раз:\n";
                cin >> month;
            } while (month < 1 || month > 12);
            cin >> year;
            while (getchar() != '\n');
            if (year < 1)
                do
                {
                    cout << "\nГод - число положительное!\nПопробуйте еще раз:\n";
                    cin >> year;
                } while (year < 1);
                if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2 && day > 29)
                {
                    cout << "В феврале " << year << " года было всего 29 дней" << endl;
                    day = 29;
                }
                else if ((year % 4 != 0) && month == 2 && day > 28)
                {
                    cout << "В феврале " << year << " года было всего 28 дней" << endl;
                    day = 28;
                }
                else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
                {
                    cout << "В месяце, который вы ввели было всего 30 дней" << endl;
                    day = 30;
                }
}

int date_::operator - (const date_& D)											//перегрузка оператора "-" для подсчета разницы между датами в днях
{
    int i = 0;
    int days = 0;
    int days_in_month1[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//количество дней по месяцам 1 даты
    int days_in_month2[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//количество дней по месяцам 2 даты

    if ((D.year % 4 == 0 && D.year % 100 != 0) || D.year % 400 == 0)			//если год високосный
        days_in_month2[1] = 29;													//то в феврале 29 дней
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)					//если год високосный
        days_in_month1[1] = 29;													//то в феврале 29 дней

    for (i = D.year + 1; i < year; i++)
    {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
            days += 366;														//если год високосный, то количество дней
        else																	//в разнице дат увеличиваем на 366 дней,
            days += 365;														//иначе, если не високосный - на 365
    }
    if (D.year != year)
    {
        for (i = D.month + 1; i <= 12; i++)										//добавляем к сумме количество дней в месяцах
            days += days_in_month2[i - 1];										//до конца года первой даты
        for (i = 1; i < month; i++)												//добавляем к сумме количество дней в месяцах
            days += days_in_month1[i - 1];										//от начала года второй даты
    }
    if (D.year == year)															//если один год
    {
        for (i = D.month + 1; i < month; i++)									//добавляем к сумме количество дней в месяцах
            days += days_in_month2[i - 1];										//между месяцами дат
    }
    if (D.month != month)														//если месяцы дат не равны, добавляем количество
        days += days_in_month1[D.month - 1] - D.day + day;						//дней до конца месяца 1-й даты и от начала месяца 2-й даты
    else if (D.month == month)													//если месяц один,
        days += abs(day - D.day);												//добавляем разницу дней
    return days;
}

date_ operator + (date_ D, int days)
{
    int i = 0;
    int j = 0;
    int k = 0;
    date_ temp;
    temp.year = D.year;
    temp.month = D.month;
    temp.day = D.day;
    int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //количество дней по месяцам
    if ((temp.year % 4 == 0 && temp.year % 100 != 0) || temp.year % 400 == 0)	//если год високосный
        days_in_month[1] = 29;													//то в феврале 29 дней

    if (days_in_month[temp.month - 1] - temp.day < days)						//если прибавляем больше дней, чем осталось до конца месяца
        do
        {
            if ((temp.year % 4 == 0 && temp.year % 100 != 0) || temp.year % 400 == 0)//проверяем год на високосность в цикле
                days_in_month[1] = 29;
            else if (temp.year % 4 != 0)
                days_in_month[1] = 28;
            days -= days_in_month[temp.month - 1] - temp.day;
            temp.day = 0;
            temp.month++;
            if (temp.month == 13)
            {
                temp.month = 1;
                temp.year++;
            }
        } while (days_in_month[temp.month - 1] - temp.day < days);
        if (days_in_month[temp.month - 1] - temp.day >= days)						//если прибавляем меньше дней, чем осталось
            temp.day += days;														//до конца месяца
        return temp;
}
date_ date_::nextDay()
{
    *this = (*this + 1);
    return *this;
}

int main(void)
{
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    date_ A;
    date_ B;
    B.getSysDate();
    int var1;
    int var2;
    int d = 0;
    cout << "\nЭта программа позволяет работать с датами.";
    cout << "\nПо умолчанию 1-я дата - 1.1.1;\n2-я дата получена от системы.\n";
    cout << "\nдля продолжения - enter\n";
    while (getchar() != '\n');
    do
    {
        var1 = 0;
        system("cls");
        cout << "\nВыберите вариант:";
        cout << "\n1 - вывести на экран последние сохраненные даты.";
        cout << "\n2 - изменить сохраненные даты.";
        cout << "\n3 - вычислить разность двух дат в днях.";
        cout << "\n4 - увеличить дату на заданное количество дней.";
        cout << "\n5 - увеличить дату на один день.";
        cout << "\n6 - завершить и выйти.\n";
        while (var1 < 1 || var1 > 6)
        {
            cin >> var1;
            while (getchar() != '\n');
            if (var1 < 1 || var1 > 6)
                cout << "\nВыберите один из 6 вариантов!\n";
        }
        switch (var1)
        {
        case 1:
            system("cls");
            cout << "\nВот сохраненные даты:\n\n";
            A.showDate();
            B.showDate();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n');
            break;
        case 2:
            system("cls");
            var2 = 0;
            cout << "\nВыберите вариант:";
            cout << "\n1 - поменять 1-ю дату.";
            cout << "\n2 - поменять 2-ю дату.";
            cout << "\n3 - поменять обе даты.";
            cout << "\n4 - ничего не менять.\n";
            while (var2 < 1 || var2 > 4)
            {
                cin >> var2;
                while (getchar() != '\n');
                if (var2 < 1 || var2 > 4)
                    cout << "\n1, 2, 3, 4 - Внимательнее!\n";
            }
            switch (var2)
            {
            case 1:
                A.setDate();
                cout << "\n1 - я дата перезаписана\n";
                cout << "\nдля продолжения - enter\n";
                while (getchar() != '\n');
                break;
            case 2:
                B.setDate();
                cout << "\n2 - я дата перезаписана\n";
                cout << "\nдля продолжения - enter\n";
                while (getchar() != '\n');
                break;
            case 3:
                cout << "\n1-я дата.";
                A.setDate();
                cout << "\n2-я дата.";
                B.setDate();
                cout << "\nОбе даты перезаписаны\n";
                cout << "\nдля продолжения - enter\n";
                while (getchar() != '\n');
                break;
            default:
                break;
            }
            break;
        case 3:
            system("cls");
            cout << "\nВот сохраненные даты:\n\n";
            A.showDate();
            B.showDate();
            if (B.Year() > A.Year() || (B.Year() == A.Year()) && (B.Month() > A.Month()) || (B.Year() == A.Year()) && (B.Month() == A.Month()) && (B.Day() >= A.Day()))
                cout << "\nРазница между датами в днях составляет " << B - A << endl;
            else
                cout << "\nРазница между датами в днях составляет " << A - B << endl;
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n');
            break;
        case 4:
            system("cls");
            A.setDate();
            cout << "\nНа какое количество дней увеличить введенную дату?\n";
            cin >> d;
            while (getchar() != '\n');
            system("cls");
            cout << "\nВот введенная дата:\n";
            A.showDate();
            cout << "\nЧерез " << d << " дня(дней) будет:\n";
            (A + d).showDate();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n');
            break;
        case 5:
            system("cls");
            cout << "\nТекущее значение даты:\n";
            A.showDate();
            cout << "Нажимайте enter для увеличения даты на 1 день.\n";
            cout << "Для возврата в предыдущее мню - любую другую клавишу и enter.\n";
            while (getchar() == '\n')
            {
                cout << "Следующий день за текущей датой:\n";
                A.nextDay();
                A.showDate();
            }
            break;
        default:
            break;
        }
    } while (var1 != 6);
    system("pause");
    return 0;
}
*/

// 2. Создайте класс с именем Time для хранения времени: часы, минуты, секунды.
// В классе должны быть методы для изменения времени (увеличения, уменьшения),
// получения времени, вывода на экран времени, а также функция-член, которая
// даёт приращение времени, хранящегося в объекте Time, равное 1 секунде.
// Напишите соответствующие конструкторы и функции-члены.
// В классе предусмотреть при необходимости перегрузку операций
// ++ , -- , != , == , > , < , >> , << , = ,  += , -= ,  ().
// Используйте обычную и дружественную перегрузку.

#include <windows.h>
#include <iostream>
#include <time.h>

using namespace std;

class time_
{
private:
    int hour;
    int min;
    int sec;

public:
    time_()
    {
        SYSTEMTIME st; //+++		//получение системного времени
        GetLocalTime(&st);
        hour = st.wHour;
        min = st.wMinute;
        sec = st.wSecond;
    };
    time_(const time_ &d)
    {
        hour = d.hour;
        min = d.min;
        sec = d.sec;
    }
    int Hour() const
    {
        return hour;
    }
    int Min() const
    {
        return min;
    }
    int Sec() const
    {
        return sec;
    }
    void setTime(); //ввод значения времени с клавиатуры
    void showTime() //вывод времени на экран
    {
        cout << hour << ":" << min << ":" << sec << endl;
    }
    void getSysTime();                            //получение системного времени
    time_ operator-(time_ &T);                    //перегрузка оператора "-" для уменьшения времени
    time_ operator++(int sec);                    //перегрузка оператора "++" для приращения времени на 1 с
    friend time_ operator+(time_ &T1, time_ &T2); //++  //дружественная перегрузка оператора "+" для увеличения времени
    friend time_ setDifTime(time_ &T);            //++  //дружественная функция для ввода приращения времени
};

void time_::getSysTime()
{
    SYSTEMTIME st; //+++			    //получение системного времени
    GetLocalTime(&st);
    hour = st.wHour;
    min = st.wMinute;
    sec = st.wSecond;
}

void time_::setTime() //ввод значения времени с клавиатуры
{
    cout << "\nДля установки времени с клавиатуры необходимо ввести часы, минуты, секунды.\n";
    cout << "Установить часы:\n";
    cin >> hour;
    while (getchar() != '\n')
        ;
    if (hour < 0 || hour > 24)
        do
        {
            cout << "\nВ сутках 24 часа! Попробуйте еще раз:\n";
            cin >> hour;
            while (getchar() != '\n')
                ;
        } while (hour < 0 || hour > 24);
    cout << "Установить минуты:\n";
    cin >> min;
    while (getchar() != '\n')
        ;
    if (min < 0 || min > 59)
        do
        {
            cout << "\nот 0 до 59! Попробуйте еще раз:\n";
            cin >> min;
            while (getchar() != '\n')
                ;
        } while (min < 0 || min > 59);
    cout << "Установить секунды:\n";
    cin >> sec;
    while (getchar() != '\n')
        ;
    if (sec < 0 || sec > 59)
        do
        {
            cout << "\nот 0 до 59! Попробуйте еще раз:\n";
            cin >> sec;
            while (getchar() != '\n')
                ;
        } while (sec < 0 || sec > 59);
    cout << "\nВремя перезаписано.\n";
}

time_ time_::operator-(time_ &T) //перегрузка оператора "-" для уменьшения времени
{
    if (sec >= T.sec)
        sec = sec - T.sec;
    else
    {
        sec = 60 - (T.sec - sec);
        min--;
        if (min == -1)
        {
            min = 59;
            hour--;
            if (hour == -1)
                hour = 23;
        }
    }
    if (min >= T.min)
        min = min - T.min;
    else
    {
        min = 60 - (T.min - min);
        hour--;
        if (hour == -1)
            hour = 23;
    }
    int i;
    for (i = 0; 24 * i - (T.hour - hour) < 0; i++)
        ;
    hour = 24 * i - (T.hour - hour);
    return *this;
}

time_ time_::operator++(int sec) //перегрузка оператора "++" для приращения времени на 1 с
{
    this->sec++;
    if (this->sec == 60)
    {
        this->sec = 0;
        min++;
        if (min == 60)
        {
            min = 0;
            hour++;
            if (hour == 24)
                hour = 0;
        }
    }
    return *this;
}

time_ operator+(time_ &T1, time_ &T2) //+++ //дружественная перегрузка оператора "+" для увеличения времени
{
    if (T2.min == 60)
    {
        T2.min = 0;
        T2.hour++;
    }
    if (T2.sec == 60)
    {
        T2.sec = 0;
        T2.min++;
        if (T2.min == 60)
        {
            T2.min = 0;
            T2.hour++;
        }
    }
    if (T1.sec + T2.sec <= 59)
        T1.sec = T1.sec + T2.sec;
    else if (T1.sec + T2.sec == 60)
    {
        T1.sec = 0;
        T1.min++;
        if (T1.min == 60)
        {
            T1.min = 0;
            T1.hour++;
            if (T1.hour == 24)
                T1.hour = 0;
        }
    }
    else
    {
        T1.sec = 120 - (T1.sec + T2.sec);
        T1.min++;
        if (T1.min == 60)
        {
            T1.min = 0;
            T1.hour++;
            if (T1.hour == 24)
                T1.hour = 0;
        }
    }
    if (T1.min + T2.min <= 59)
        T1.min = T1.min + T2.min;
    else if (T1.min + T2.min == 60)
    {
        T1.min = 0;
        T1.hour++;
        if (T1.hour == 24)
            T1.hour = 0;
    }
    else
    {
        T1.min = 120 - (T1.min + T2.min);
        T1.hour++;
        if (T1.hour == 24)
            T1.hour = 0;
    }
    T2.hour = (T2.hour > 24 ? (T2.hour % 24) : T2.hour);
    if (T1.hour + T2.hour <= 23)
        T1.hour = T1.hour + T2.hour;
    else if (T1.hour + T2.hour == 24)
        T1.hour = 0;
    else
        // T1.hour = 48 - (T1.hour + T2.hour);??
        T1.hour = (T1.hour + T2.hour) - 24;
    return T1;
}

time_ setDifTime(time_ &T) //++		//дружественная функция для ввода приращения времени
{
    cout << "\nВведите необходимое значение для изменения времени чч:мм:сс\n";
    cout << "Введите часы:\n";
    cin >> T.hour;
    while (getchar() != '\n')
        ;
    if (T.hour < 0)
        do
        {
            cout << "\nВведите неотрицательное значение:\n";
            cin >> T.hour;
            while (getchar() != '\n')
                ;
        } while (T.hour < 0);
    cout << "Введите минуты:\n";
    cin >> T.min;
    while (getchar() != '\n')
        ;
    if (T.min < 0 || T.min > 60)
        do
        {
            cout << "\n1 час = 60 минут! Попробуйте еще раз:\n";
            cin >> T.min;
            while (getchar() != '\n')
                ;
        } while (T.min < 0 || T.min > 60);
    cout << "Введите секунды:\n";
    cin >> T.sec;
    while (getchar() != '\n')
        ;
    if (T.sec < 0 || T.sec > 60)
        do
        {
            cout << "\n1 минута = 60 секунд! Попробуйте еще раз:\n";
            cin >> T.sec;
            while (getchar() != '\n')
                ;
        } while (T.sec < 0 || T.sec > 60);
    return T;
}

int main(void)
{
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    time_ T1;
    time_ T2;
    int var;
    cout << "\nЭта программа позволяет работать со временем.";
    cout << "\nПо умолчанию сохранено системное время на момент запуска программы.\n";
    cout << "\nдля продолжения - enter\n";
    while (getchar() != '\n')
        ;
    do
    {
        var = 0;
        system("cls");
        cout << "\nВыберите вариант:";
        cout << "\n1 - вывести последнее сохраненное время на экран.";
        cout << "\n2 - перезаписать время заданным с клавиатуры.";
        cout << "\n3 - увеличить время на заданную величину.";
        cout << "\n4 - уменьшить время на заданную величину.";
        cout << "\n5 - увеличить время на 1 секунду.";
        cout << "\n6 - завершить и выйти.\n";
        while (var < 1 || var > 6)
        {
            cin >> var;
            while (getchar() != '\n')
                ;
            if (var < 1 || var > 6)
                cout << "\nВыберите один из 6 вариантов!\n";
        }
        switch (var)
        {
        case 1:
            system("cls");
            cout << "\nВот последнее сохраненное время:\n\n";
            T1.showTime();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n')
                ;
            break;
        case 2:
            system("cls");
            T1.setTime();
            cout << "\nВот последнее сохраненное время:\n\n";
            T1.showTime();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n')
                ;
            break;
        case 3:
            system("cls");
            setDifTime(T2);
            T1 + T2;
            cout << "\nВот последнее сохраненное время после приращения:\n\n";
            T1.showTime();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n')
                ;
            break;
        case 4:
            system("cls");
            setDifTime(T2);
            T1 - T2;
            cout << "\nВот последнее сохраненное время после уменьшения:\n\n";
            T1.showTime();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n')
                ;
            break;
        case 5:
            system("cls");
            cout << "\nДля увеличения текущего сохраненного времени на 1 секунду\n";
            cout << "нажимайте enter, для продолжения - любую другую клавишу и enter\n";
            while (getchar() == '\n')
            {
                T1++;
                cout << "Вот время увеличенное на 1 секунду:\n\n";
                T1.showTime();
            }
            while (getchar() != '\n')
                ;
            system("cls");
            cout << "\nВот последнее сохраненное время:\n\n";
            T1.showTime();
            cout << "\nдля продолжения - enter\n";
            while (getchar() != '\n')
                ;
            break;
        default:
            break;
        }
    } while (var != 6);
    system("pause");
    return 0;
}
