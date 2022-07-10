/*
// 1. Создайте класс Student, который будет содержать информацию о студенте.
//     С помощью механизма наследования, реализуйте класс Aspirant, производный от
//     Student. Аспирант - это студент, который готовится к защите кандидатской
//     работы.

#include <windows.h>
#include <iostream>
#include <ctime>
#include <iomanip>

const int size_ = 81;

///////////////////////////////////////////////////////////////////////////////

void dash(int);
void dot(int);
void dotdot(int);
void equal(int);
void tabs(int);
void apostrophe(int);
void underscore(int);
void eatline(void);
int getValueInt();

///////////////////////////////////////////////////////////////////////////////

using namespace std;

//=============================================================================
class Student
{
protected:
    char* name;
    char* surname;
    char* patronymic;
    char* department;
public:
    Student()
    {
        name = new char('\0');
        surname = new char('\0');
        patronymic = new char('\0');
        department = new char('\0');
    }
    ~Student()
    {
        delete[] name;
        delete[] surname;
        delete[] patronymic;
        delete[] department;
    }
    void get(char* name, char* surname, char* patronymic, char* department);
    void show();
};

void Student::get(char* name , char* surname, char* patronymic, char* department)
{
    this->name = new char[strlen(name) + 1];
    this->surname = new char[strlen(surname) + 1];
    this->patronymic = new char[strlen(patronymic) + 1];
    this->department = new char[strlen(department) + 1];
    strcpy(this->name, name);
    strcpy(this->surname, surname);
    strcpy(this->patronymic, patronymic);
    strcpy(this->department, department);
}
void Student::show()
{
    cout << "\tИмя:\t\t" << name << endl;
    cout << "\tФамилия:\t" << surname << endl;
    cout << "\tОтчество:\t" << patronymic << endl;
    cout << "\tФакультет:\t" << department << endl;
}
//=============================================================================

class Aspirant : public Student
{
    bool exam1;
    bool exam2;
    bool exam3;
public:
    Aspirant()
    {
        exam1 = false;
        exam2 = false;
        exam3 = false;
    }
    bool getExam1()
    {
        return exam1;
    }
    bool getExam2()
    {
        return exam2;
    }
    bool getExam3()
    {
        return exam3;
    }
    void exam();
};
void Aspirant::exam()
{
    exam1 = rand() % 2;
    exam2 = rand() % 2;
    exam3 = rand() % 2;
}

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(NULL));

    Aspirant* student = nullptr;

    char name[size_];
    char surname[size_];
    char patronymic[size_];
    char department[size_]; // Факультет

    int count; // Кол-во студентов
    int count_рass;

    int menu;

    bool examFinish = false;
    bool graduate = false;
    bool grоupON = false;
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
        cout << "\t\t       ***| Из студентов в аспиранты |***" << endl << endl << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню для работы:" << endl;
        cout << "\t1) Внести данные о студентах желающие стать аспирантами." << endl;
        cout << "\t2) Вывод на экран всех студентов желающие стать аспирантами." << endl;
        cout << "\t3) Вывод на экран студентов ставшие аспирантами." << endl;
        cout << "\t4)  | ВыхоД |";

        menu = getValueInt();
        cout << endl;

        switch (menu)
        {
        case 1 :
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl << endl;
            if (grоupON)
            {
                cout << endl << "\tГруппа для сдачи экзаменов в аспирантуру сформирована." << endl;
            }
            else
            {
                do
                {
                    cout << endl << "\tВведите количество студентов желающих стать аспирантами:";
                    count = getValueInt();

                } while (count < 3 || count > 20);

                cout << endl;
                dot(26);
                cout << endl << endl;

                student = new Aspirant[count];
                for (int i = 0; i < count; i++)
                {
                    cout << "\t=== Студент №" << setw(2)<< i + 1 << "===" << endl;

                    do
                    {
                        cout << endl << "\tВведите имя:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin.getline(name, size_);
                    } while (name[0] == '\0' || (int)strlen(name) > 20);
                    do
                    {
                        cout << endl << "\tВведите фамилию:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin.getline(surname, size_);
                    } while (surname[0] == '\0' || (int)strlen(surname) > 20);
                    do
                    {
                        cout << endl << "\tВведите отчество:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin.getline(patronymic, size_);
                    } while (patronymic[0] == '\0' || (int)strlen(patronymic) > 20);
                    do
                    {
                        cout << endl << "\tВведите факультет:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin.getline(department, size_);
                    } while (department[0] == '\0' || (int)strlen(department) > 20);

                    student[i].get(name, surname, patronymic, department);

                    if (i != count - 1)
                    {
                        cout << "\t";
                        dotdot(40);
                        cout << endl;
                    }
                }

                cout << endl;
                dot(26);
                cout << endl << endl;

                cout << "\tГруппа студентов для сдачи экзаменов в аспирантуру сформирована." << endl;
                cout << "\tКоличество студентов желающие стать аспирантами " << count <<" человек."<< endl;

                grоupON = true;
            }

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();
        }
        break;

        case 2 :
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl << endl << endl;

            if (grоupON)
            {
                cout << "\tГруппа студентов желающих стать аспирантами:" << endl;
                cout << "\t";
                underscore(40);
                cout << endl;
                for (int i = 0; i < count; i++)
                {
                    student[i].show();
                    if (i != count - 1)
                    {
                        cout << "\t";
                        underscore(40);
                        cout << endl;
                    }
                }
                cout << "\t";
                underscore(40);
                cout << endl;
            }
            else
            {
                cout << "\tГруппа студентов для аспирантуры не создана (1 пункт меню)." << endl;
            }

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();
        }
        break;

        case 3 :
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl << endl << endl;

            if (grоupON)
            {
                count_рass = 0;
                if (examFinish == false)
                {
                    for (int i = 0; i < count; i++)
                    {
                        student[i].exam();
                        examFinish = true;
                    }

                    for (int i = 0; i < count; i++)
                    {
                        if (student[i].getExam1() && student[i].getExam2() && student[i].getExam3())
                        {
                            cout << "\t";
                            underscore(40);
                            cout << endl;
                            student[i].show();
                            cout << "\t";
                            underscore(40);
                            cout << endl;
                            graduate = true;
                            count_рass++;
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        if (student[i].getExam1() && student[i].getExam2() && student[i].getExam3())
                        {
                            cout << "\t";
                            underscore(40);
                            cout << endl;
                            student[i].show();
                            cout << "\t";
                            underscore(40);
                            cout << endl;
                            graduate = true;
                            count_рass++;
                        }
                    }
                }

                if (graduate)
                {
                    cout << endl;
                    cout << "\tСтуденты ставшие аспиратами "<< count_рass << " человек." << endl;
                    cout << "\tПоздравляем!!!" << endl;
                }
                else
                {
                    cout << "\tАспирантов среди студентов нет (экзамены не кто не сдал)." << endl;
                    cout << "\tВ cледующий раз обязательно пройдете, продолжайте готовится!!!" << endl;
                }
            }
            else
            {
                cout << "\tГруппа студентов для аспирантуры не создана (1 пункт меню)." << endl;
            }

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();
        }
        break;

        case 4 :
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

    cout << endl << "\t\t\t    ..........................";
    cout << endl << "\t\t\t    |                        |";
    cout << endl << "\t\t\t    |       До свидания      |";
    cout << endl << "\t\t\t    |                        |";
    cout << endl << "\t\t\t    ''''''''''''''''''''''''''" << endl;

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

// Проверка ввода int
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

//=============================================================================
void       dash(int count) { for (int i = 0; i < count; i++) cout << "-"; }
void        dot(int count) { for (int i = 0; i < count; i++) cout << "  ."; }
void     dotdot(int count) { for (int i = 0; i < count; i++) cout << "."; }
void      equal(int count) { for (int i = 0; i < count; i++) cout << "="; }
void       tabs(int count) { for (int i = 0; i < count; i++) cout << "\t|"; }
void apostrophe(int count) { for (int i = 0; i < count; i++) cout << "`"; }
void underscore(int count) { for (int i = 0; i < count; i++) cout << "_"; }
void eatline(void) { cin.clear(); while (cin.get() != '\n') { continue; } }



// 2. Используя понятие множественного наследования, разработайте класс
//     "Окружность, вписанная в квадрат".


#include <iostream>

using namespace std;

class Square
{
    float side_;
public:
    Square(float side) : side_(side) { }
    float getSide()
    {
        return side_;
    }
};

class Circle
{
    float radius_;
public:
    Circle(float radius) : radius_(radius) { }
    float getRadius()
    {
        return radius_;
    }
};

// "Окружность, вписанная в квадрат"
class CircleInSquare : public Circle, public Square
{
public:
    CircleInSquare(float side) : Square(side), Circle(side/2) { }
};

double getValue()
{
    double d;

    cout << "     |" << endl;
    cout << "     '->";
    cin >> d;

    cin.clear();
    while (cin.get() != '\n'){continue;}
    cin.ignore(cin.rdbuf()->in_avail());

    return d;
}

int main(void)
{
    system("cls");
    cout << endl;
    cout << "\t\t======  Circle in Square ======" << endl;

    string ask;
    double side;
    bool round;
    do
    {
        do
        {
            side = 0;
            cout << endl << "\tEnter side of the Square" << endl;
            side = getValue();
        } while (side <= 0);

        Square mSquare = Square(side);
        CircleInSquare mCircle = CircleInSquare(side);

        cout << "\t----------------------------------------" << endl;
        cout << "\tRadius of the inscribed circle = ";
        std::cout << mCircle.getRadius() << endl;
        cout << "\tLingth of the side square = ";
        std::cout << mSquare.getSide() << endl;
        cout << "\t.  .  .  .  .  .  .  .  .  .  .  .  .  ." << endl;
        cout << "\tRepeat? (yes/no)" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        cin >> ask;

        if (!ask.compare("yes")|| !ask.compare("Yes")|| !ask.compare("YES"))
        {
            round = true;
            cout << endl << "\t+++*******************+++" << endl;
        }
        else
        {
            round = false;
            cout << endl << "\t\t\t=== Goodbye ===" << endl;
        }

    } while (round);

    return 0;
}
*/

// 3. В вопросе 2 лекции 8 "Агрегация. Композиция. Наследование" приведен пример
//     на альянс класса "точки" и класса "фигура". Ваша задача состоит в том, чтобы
//     добавить к программе класс, который будет содержать в себе несколько объектов
//     класса фигура, создавая тем самым композицию.

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

///////////////////////////////////////////////////////////////////////////////

using namespace std;

// Kласс "точка"
class Point
{

public:
    Point()
    {
        x_ = 0;
        y_ = 0;
    }

    void setPoint(int x, int y)
    {
        x_ = x;
        y_ = y;
    }
    void showPoint()
    {
        cout << "\t------------ Координаты точки: -----------" << endl;
        cout << "\tКоордината X = " << x_ << "\tКоордината Y = " << y_ << endl;
        cout << "\t------------------------------------------" << endl;
    }

private:
    int x_;
    int y_;
};

// Класс фигура
class Shape
{

public:
    Shape()
    {
        locate_point = 0;
        quantity_point = 0;
    }
    ~Shape()
    {
        delete[] locate_point;
    }

    // Создание фигуры
    void createShape(int qpoint)
    {
        // Если точек больше двух — это фигура
        if (qpoint > 2)
        {
            quantity_point = qpoint;

            // Выделение памяти под массив точек
            locate_point = new Point[quantity_point];
            if (locate_point)
            {
                int temp_x;
                int temp_y;
                cout << "\tУстановка координат точек фигуры:";
                for (int i = 0; i < quantity_point; i++)
                {
                    cout << endl
                         << "\tКоординаты " << i + 1 << " точки:";
                    cout << endl
                         << "\t=== X ===";
                    temp_x = valueTypeI();
                    cout << endl
                         << "\t=== Y ===";
                    temp_y = valueTypeI();

                    locate_point[i].setPoint(temp_x, temp_y);
                }
            }
            else
            {
                cout << "\tНевозможно выделить память под массив точек." << endl;
                cout << "\tФигура на создана." << endl
                     << endl;
                cout << "\tДля продолжения нажмите-<ENTER>";
                cin.get();
            }
        }
        else
        {
            cout << "\tТочек меньше трёх." << endl;
            cout << "\tЭто нельзя считать фигурой." << endl;
            cout << "\tФигура на создана." << endl
                 << endl;
            cout << "\tДля продолжения нажмите-<ENTER>";
            cin.get();
        }
    }

    // Показ фигуры
    int showShape()
    {
        if (quantity_point != 0)
        {
            cout << "\tКоличество точек в фигуре = " << quantity_point << endl;
            for (int i = 0; i < quantity_point; i++)
            {
                cout << "\tТочка " << i + 1 << "-я" << endl;
                locate_point[i].showPoint();
            }
            return 1;
        }
        return -1;
    }

private:
    Point *locate_point;
    int quantity_point; // Количество точек для построения фигуры
};

class Picture
{

public:
    Picture()
    {
        shape = 0;
        quantity_shape = 0;
        quantity_point = 0;
    }
    Picture(int quantity)
    {
        quantity_point = 0;
        quantity_shape = quantity;
        shape = new Shape[quantity_shape];
    }
    ~Picture()
    {
        delete[] shape;
    }

    void create()
    {
        for (int i = 0; i < quantity_shape; i++)
        {
            cout << "\tСоздаем " << i + 1 << " фигуру на рисунке." << endl;
            cout << "\tВведите количество точек для " << i + 1 << " фигуры:";
            quantity_point = valueTypeI();

            cout << endl
                 << "\t";
            dot(14);
            cout << endl
                 << endl;

            shape[i].createShape(quantity_point);

            if (i != quantity_shape - 1)
            {
                cout << endl
                     << "\t";
                dotdot(42);
                cout << endl
                     << endl;
            }
        }
    }
    void show()
    {
        cout << "\t=== Все фигуры на картине (композиция) ===" << endl;
        cout << "\t";
        underscore(42);
        cout << endl;
        for (int i = 0; i < quantity_shape; i++)
        {
            if (shape[i].showShape() == 1)
            {
                cout << "\tФигура " << i + 1 << " построена." << endl;
                cout << "\t";
                underscore(42);
                cout << endl;
            }
        }
    }

private:
    Shape *shape;
    int quantity_shape;
    int quantity_point;
};

int main()
{
    system("cls");
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("cls");
    equal(80);
    cout << endl;
    tabs(9);
    cout << endl;
    apostrophe(80);
    cout << endl;
    cout << "\t\t    ***| Рисунок с фигурами (композиция) |***" << endl
         << endl
         << endl;

    int quantity_shape;

    cout << "\t===  Создаем рисунок из фигур  ===" << endl;
    do
    {
        cout << endl
             << "\tВведите количество фигур на рисунке:";
        quantity_shape = valueTypeI();
    } while (quantity_shape <= 1);

    Picture picture(quantity_shape);

    cout << endl;
    dot(26);
    cout << endl
         << endl;

    picture.create();

    cout << endl;
    dot(26);
    cout << endl
         << endl;

    picture.show();

    cout << endl;
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
