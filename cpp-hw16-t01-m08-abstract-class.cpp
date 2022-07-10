// Задание №1.
// Создать абстрактный базовый класс Employer (служащий) с чисто виртуальной функцией Print().
// Создайте три производных класса: President, Manager, Worker. Переопределите функцию Print()
// для вывода информации, соответствующей каждому типу служащего. Отладить на реально работающей
// программе с реальными данными. Учесть то, что президент один,
// менеджеров может быть несколько и рабочих также несколько.

#include <windows.h>
#include <iostream>
#include <string>

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
double valueTypeD();

///////////////////////////////////////////////////////////////////////////////

class Employee
{

public:
    Employee()
    {
        name_ = '\0';
        surname_ = '\0';
        salary_ = 0;
    }
    void getData(string name, string surname, double salary)
    {
        name_ = name;
        surname_ = surname;
        salary_ = salary;
    }
    virtual void print() = 0;

protected:
    string name_;
    string surname_;
    double salary_;
};

class President : public Employee
{

public:
    void print()
    {
        cout << "\tИмя:\t\t" << name_ << endl;
        cout << "\t\tФамилия:\t" << surname_ << endl;
        cout << "\t\tЗарплата:\t" << salary_ << endl;
    }
};

class Manager : public Employee
{

public:
    void print()
    {
        cout << "\tИмя:\t\t" << name_ << endl;
        cout << "\t\tФамилия:\t" << surname_ << endl;
        cout << "\t\tЗарплата:\t" << salary_ << endl;
    }
};

class Worker : public Employee
{
public:
    void print()
    {
        cout << "\tИмя:\t\t" << name_ << endl;
        cout << "\t\tФамилия:\t" << surname_ << endl;
        cout << "\t\tЗарплата:\t" << salary_ << endl;
    }
};

int main()
{
    system("cls");
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string name;
    string surname;
    double salary;

    int quantity_m;
    int quantity_w;

    President *president;
    Manager *manager;
    Worker *worker;

    system("cls");
    equal(80);
    cout << endl;
    tabs(9);
    cout << endl;
    apostrophe(80);
    cout << endl;
    cout << "\t\t  ***| Абстрактный базовый класс Employee |***" << endl
         << endl
         << endl;
    cout << "\tШтат предприятия состоит из небольшого количества сотрудников." << endl;
    cout << "\tОдин директор, несколько менеджеров и рабочих." << endl;
    do
    {
        cout << endl
             << "\t1) Введите количество менеджеров (1-5):";
        quantity_m = valueTypeI();
    } while (quantity_m <= 0 || quantity_m > 5);

    do
    {
        cout << endl
             << "\t2) Введите количество рабочих (1-10):";
        quantity_w = valueTypeI();
    } while (quantity_w <= 0 || quantity_w > 10);

    president = new President;
    manager = new Manager[quantity_m];
    worker = new Worker[quantity_w];

    cout << endl;
    dash(80);
    cout << endl
         << endl;

    cout << "\tКоличeства сотрудников на предприятии " << 1 + quantity_m + quantity_w << " человек." << endl
         << endl;

    cout << "\t=== Введите данные директора ===";
    do
    {
        cout << endl
             << "\tВведите имя" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        getline(cin, name);
    } while (name.size() == 0 || name.size() > 20);
    do
    {
        cout << endl
             << "\tВведите фамилию" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        getline(cin, surname);
    } while (surname.size() == 0 || surname.size() > 20);
    do
    {
        cout << endl
             << "\tВведите зарплату" << endl;
        salary = valueTypeD();
    } while (salary <= 0);

    president->getData(name, surname, salary);

    cout << endl;
    dot(26);
    cout << endl
         << endl;

    for (int i = 0; i < quantity_m; i++)
    {
        cout << "\t=== Введите данные " << i + 1 << " менеджера ===";
        do
        {
            cout << endl
                 << "\tВведите имя" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            getline(cin, name);
        } while (name.size() == 0 || name.size() > 20);
        do
        {
            cout << endl
                 << "\tВведите фамилию" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            getline(cin, surname);
        } while (surname.size() == 0 || surname.size() > 20);
        do
        {
            cout << endl
                 << "\tВведите зарплату" << endl;
            salary = valueTypeD();
        } while (salary <= 0);

        manager[i].getData(name, surname, salary);

        if (i != quantity_m - 1)
        {
            cout << endl
                 << "\t";
            dotdot(35);
            cout << endl;
        }
    }

    cout << endl;
    dot(26);
    cout << endl
         << endl;

    for (int i = 0; i < quantity_w; i++)
    {
        cout << "\t=== Введите данные " << i + 1 << " рабочего ===";
        do
        {
            cout << endl
                 << "\tВведите имя" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            getline(cin, name);
        } while (name.size() == 0 || name.size() > 20);
        do
        {
            cout << endl
                 << "\tВведите фамилию" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            getline(cin, surname);
        } while (surname.size() == 0 || surname.size() > 20);
        do
        {
            cout << endl
                 << "\tВведите зарплату" << endl;
            salary = valueTypeD();
        } while (salary <= 0);

        worker[i].getData(name, surname, salary);

        if (i != quantity_w - 1)
        {
            cout << endl
                 << "\t";
            dotdot(35);
            cout << endl;
        }
    }

    cout << endl;
    dash(80);
    cout << endl
         << endl;

    cout << "\tВывод данных о сотрудниках на предприятии:" << endl
         << "\t";
    underscore(42);
    cout << endl;
    cout << "\tДиректор:" << endl
         << endl;
    cout << "\t1)";
    president->print();

    cout << "\t";
    underscore(42);
    cout << endl;
    cout << "\tМенеджеры:" << endl
         << endl;
    for (int i = 0; i < quantity_m; i++)
    {
        cout << "\t" << i + 1 << ")";
        manager[i].print();

        if (i != quantity_m - 1)
        {
            cout << endl
                 << "\t";
            dotdot(42);
            cout << endl
                 << endl;
        }
    }

    cout << "\t";
    underscore(42);
    cout << endl;
    cout << "\tРабочие:" << endl
         << endl;
    for (int i = 0; i < quantity_w; i++)
    {
        cout << "\t" << i + 1 << ")";
        worker[i].print();

        if (i != quantity_w - 1)
        {
            cout << endl
                 << "\t";
            dotdot(42);
            cout << endl
                 << endl;
        }
    }
    cout << endl
         << "\t";
    underscore(42);
    cout << endl
         << endl;

    delete president;
    delete[] manager;
    delete[] worker;

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

// Tип данных double
double valueTypeD()
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
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }
}

/*
// Задание №2.
// Создать абстрактный базовый класс с виртуальной функцией – площадь.
// Создать производные классы: прямоугольник, круг, прямоугольный треугольник,
// трапеция со своими функциями площади.
// Для проверки определить массив ссылок на абстрактный класс,
// которым присваиваются адреса различных объектов.

#include <windows.h>
#include <iostream>

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
double valueTypeD();

///////////////////////////////////////////////////////////////////////////////

using namespace std;

class Shape
{
public:
    Shape()
    {
        a_ = 0;
        b_ = 0;
        h_ = 0;
    }
    void getValue(double a, double b, double h)
    {
        a_ = a;
        b_ = b;
        h_ = h;
    }
    virtual double area() = 0;

protected:
    double a_;
    double b_;
    double h_;
};

class Rectangle_ : public Shape
{
public:
    double area() { return (a_ * b_); }
};

class Circle : public Shape
{
public:
    double area() { return (3.14 * a_ * a_); }
};

class RightTriangle : public Shape
{
public:
    double area() { return (a_ * b_ * 1 / 2); }
};

class Trapeze : public Shape
{
public:
    double area() { return (h_ * (a_ + b_) * 1 / 2); }
};

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Rectangle_ rectangle;        // Прямоугольник
    Circle circle;               // Круг
    RightTriangle rightTriangle; // Прямоугольный треугольник
    Trapeze trapeze;             // Tрапеция

    // Mассив ссылок на абстрактный класс, которым присваиваются адреса различных объектов
    Shape *shape[4] = {&rectangle, &circle, &rightTriangle, &trapeze};

    double a;
    double b;
    double h;

    int menu;
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
        cout << "\t    ***| Абстрактный базовый класс с виртуальной функцией |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню для работы:" << endl;
        cout << "\t1) Вычислить площадь прямоугольника." << endl;
        cout << "\t2) Вычислить площадь круга." << endl;
        cout << "\t3) Вычислить площадь прямоугольного треугольника." << endl;
        cout << "\t4) Вычислить площадь трапеции." << endl;
        cout << "\t5)  | ВыхоД |";

        menu = valueTypeI();
        cout << endl;

        switch (menu)
        {
        case 1:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
                 << endl;
            do
            {
                cout << endl
                     << "\tВведите длину прямоугольника:";
                a = valueTypeD();
            } while (a <= 0);

            cout << endl
                 << "\t";
            dotdot(40);
            cout << endl;

            do
            {
                cout << endl
                     << "\tВведите ширину прямоугольника:";
                b = valueTypeD();
            } while (b <= 0);

            shape[0]->getValue(a, b, 0);

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            cout << "\tПлощадь прямоугольника = " << shape[0]->area() << endl;

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

        case 2:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl;
            do
            {
                cout << endl
                     << "\tВведите радиус круга:";
                a = valueTypeD();
            } while (a <= 0);

            shape[1]->getValue(a, 0, 0);

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            cout << "\tПлощадь круга = " << shape[1]->area() << endl;

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
            do
            {
                cout << endl
                     << "\tВведите длину первого катета:";
                a = valueTypeD();
            } while (a <= 0);

            cout << endl
                 << "\t";
            dotdot(40);
            cout << endl;

            do
            {
                cout << endl
                     << "\tВведите длину второго катета:";
                b = valueTypeD();
            } while (b <= 0);

            shape[2]->getValue(a, b, 0);

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            cout << "\tПлощадь прямоугольного треугольника = " << shape[2]->area() << endl;

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
            do
            {
                cout << endl
                     << "\tВведите длину первого основания:";
                a = valueTypeD();
            } while (a <= 0);

            cout << endl
                 << "\t";
            dotdot(40);
            cout << endl;

            do
            {
                cout << endl
                     << "\tВведите длину второго основания:";
                b = valueTypeD();
            } while (b <= 0);

            cout << endl
                 << "\t";
            dotdot(40);
            cout << endl;

            do
            {
                cout << endl
                     << "\tВведите высоту:";
                h = valueTypeD();
            } while (h <= 0);

            shape[3]->getValue(a, b, h);

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            cout << "\tПлощадь трапеции = " << shape[3]->area() << endl;

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
         << "\t\t\t    |     Всего хорошего     |";
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

// Tип данных double
double valueTypeD()
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
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }
}
*/
