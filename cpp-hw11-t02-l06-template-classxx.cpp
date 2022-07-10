/*
// Задание 1.
// Создать класс для работы с матрицами. Предусмотреть следующие функции
// для работы с матрицами:
// - сложения матриц;
// - умножения матриц;
// - транспонирования матриц;
// - присваивания матриц друг другу;
// - установка и получение произвольного элемента матрицы.
// Необходимо перегрузить соответствующие операторы.

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iostream>
#include <ctime>   // time()
#include <iomanip> //setprecision(), setw()

///////////////////////////////////////////////////////////

void dash(int);
void dot(int);
void dotdot(int);
void equal(int);
void tabs(int);
void apostrophe(int);
void underscore(int);
void eatline(void);

///////////////////////////////////////////////////////////////////////////////

int getValueInt();
double getValueDouble();

///////////////////////////////////////////////////////////////////////////////

using namespace std;

class Array2D
{
private:
    double** array2D;
    int  row;// строк
    int  col;// столбцов

public:
    Array2D()
    {
        row = 0;
        col = 0;

        array2D = new double* [row];
        for (int i = 0; i < row; i++)
        {
            array2D[i] = new double[col];
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array2D[i][j] = 0;
            }
        }
    }
    Array2D(int col, int row)
    {
        this->row = row;
        this->col = col;
        array2D = new double* [row];
        for (int i = 0; i < row; i++)
        {
            array2D[i] = new double[col];
        }
    }
    ~Array2D()
    {
        for (int i = 0; i < col; i++)
        {
            delete[]array2D[i];
        }
        delete[]array2D;
        array2D = nullptr;
    }
    void initialize2D(int n, int m);
    void inputArray2D();
    void inputArray2DRandom();
    void outputArray2D();
    double getValue2D();
    Array2D(const Array2D& obj);
    Array2D operator + (const  Array2D ob);
    Array2D operator = (Array2D op);
    Array2D operator * (const Array2D m);
    void Transpose();
    double getRandomElement2D(const int row, int col);
    void inputRandomElement2D(const int index1, int index2, double value);
};

void Array2D::initialize2D(int n, int m)
{
    row = n;
    col = m;

    array2D = new double* [row];
    for (int i = 0; i < row; i++)
    {
        array2D[i] = new double[col];
    }
}

void Array2D::inputArray2D()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            do
            {
                cout << endl << "\tВведите [" << i << "][" << j << "] элемент массива:";
                array2D[i][j] = getValue2D();

            } while (array2D[i][j] < -10 || array2D[i][j] > 10);
        }
    }
}

void Array2D::inputArray2DRandom()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //заполнение массива случайными числами с масштабированием от -10 до 10
            array2D[i][j] = (rand() % 21 - 10) /float((rand() % 10 + 1));
        }
    }
}

void Array2D::outputArray2D()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << " [" << setw(2) << i << "][" << setw(2) << j << "]=" << setprecision(2) << setw(6) << left << array2D[i][j];

            if ((j + 1) % 5 == 0)
                cout << endl;
        }
        cout << endl;
    }
}

double Array2D::getValue2D()
{
    double a;
    cout << endl;
    cout << "     |" << endl;
    cout << "     '->";
    cin >> a;
    eatline();

    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();

    return a;
}

//===============================================
Array2D::Array2D(const Array2D& obj)
{
    col = obj.col;
    row = obj.row;
    array2D = new double* [row];
    for (int i = 0; i < row; i++)
    {
        array2D[i] = new double[col];
    }
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            array2D[i][j] = obj.array2D[i][j];
}

Array2D Array2D::operator = (Array2D op)
{
    if (row > 0)
    {

        for (int i = 0; i < row; i++)
            delete[] array2D[i];
    }

    if (col > 0)
    {
        delete[] array2D;
    }
    col = op.col;
    row = op.row;
    array2D = new double* [row];
    for (int i = 0; i < row; i++)
    {
        array2D[i] = new double[col];
    }

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            array2D[i][j] = op.array2D[i][j];
    return *this;
}

Array2D Array2D::operator + (const Array2D ob)
{
    Array2D temp(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            temp.array2D[i][j] = array2D[i][j] + ob.array2D[i][j];
    return temp;
}

Array2D Array2D::operator * (const Array2D m)
{
    Array2D temp(row, m.col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            for (int k = 0; k < col; k++)
                temp.array2D[i][j] += array2D[i][k] * m.array2D[i][j];
    return temp;
}

//Транспонирование массива (результат записывается в аргумент)
void Array2D::Transpose()
{
    double temp;
    for (int i = 0 ; i < row; i++)
        for (int j = i + 1; j < col; j++)
        {
            temp = array2D[i][j];
            array2D[i][j] = array2D[j][i];
            array2D[j][i] = temp;
        }
}

double Array2D::getRandomElement2D(const int row, int col)
{
    return array2D[row][col];
}

// ввод нового элемента в позицию
void Array2D::inputRandomElement2D(int index1, int index2, double value)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == (index1) && j == (index2))
            {
                array2D[i][j] = value;
            }
        }
    }
}


int main()
{
    system("cls");
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(nullptr));

    Array2D A;
    Array2D B;
    Array2D C;

    int row;
    int col;

    int index1;
    int index2;
    double value2;

    int menu;
    int option;
    int choice;
    char enter;
    char repeat;

    bool show_exemple = false;
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
        cout << "\t\t\t   ***| Задание 2.1 Лекция 6 (шаблоны классов) |***" << endl << endl << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню:" << endl;
        cout << "\t1. Задать параметры массивов." << endl;
        cout << "\t2. Просмотр значений массивов." << endl;
        cout << "\t3. Сложение массивов." << endl;
        cout << "\t4. Умножение массивов." << endl;
        cout << "\t5. Транспонирования массивов." << endl;
        cout << "\t6. Присваивание массивов." << endl;
        cout << "\t7. Установка и получение произвольного элемента A[][]." << endl;
        cout << "\t8.   | ВыхоД |";
        do
        {
            menu = 0;
            menu = getValueInt();

        } while (menu <= 0);

        cout << endl;

        switch (menu)
        {
        case 1:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl << endl << endl;

            if (install)
            {
                cout << "\tМассивы инциализированы." << endl;
                cout << "\tЖелаете изменить размеры массивов и вариант заполнения?" << endl;
                cout << "\t1 - ДА." << endl;
                cout << "\t2 - НЕТ.";
                do// защита ввода
                {
                    choice = 0;
                    choice = getValueInt();

                    if (choice != 1 && choice != 2)
                    {
                        cout << endl << "\tНекорректный ввод.";
                        cout << endl << "\tПожалуйста сделайте выбор.";
                    }
                } while (choice != 1 && choice != 2);

                cout << endl;
                dot(26);
                cout << endl << endl;

                if (choice == 1)
                {
                    cout << "\t1. Заполнить массивы случайными числами." << endl;
                    cout << "\t2. Заполнить массивы вручную." << endl;
                    cout << "\t3.   | Отмена |"; // оставить как есть

                    do// защита ввода
                    {
                        option = 0;
                        option = getValueInt();

                        if (option != 1 && option != 2 && option != 3)
                        {
                            cout << endl << "\tНекорректный ввод (Действие = 3 -отмена).";
                            cout << endl << "\tПожалуйста сделайте выбор.";
                        }
                    } while (option != 1 && option != 2 && option != 3);
                }
                if (choice == 2)
                {
                    break;
                }
            }
            else
            {
                cout << "\t1. Заполнить массивы случайными числами." << endl;
                cout << "\t2. Заполнить массивы вручную." << endl;
                cout << "\t3.   | Отмена |"; // оставить как есть

                do// защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2 && option != 3)
                    {
                        cout << endl << "\tНекорректный ввод (Действие = 3 -отмена).";
                        cout << endl << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2 && option != 3);
            }

            cout << endl;
            dot(26);
            cout << endl;

            if (option == 1)
            {
                do
                {
                    cout << endl << "\tВведите размер массивов (2 - 10): ";
                    row = getValueInt();

                } while (row < 2 || row > 10);
                col = row;

                A.initialize2D(row, col);
                B.initialize2D(row, col);

                cout << endl;
                cout << "\tМассив А[" << row << "][" << col << "] заполняем значениями:" << endl;;
                A.inputArray2DRandom();
                cout << "\tМассив B[" << row << "][" << col << "] заполняем значениями:" << endl;;
                B.inputArray2DRandom();

                cout << endl << "\tМассивы инициализированы." << endl;
                operate = true;
                install = true;
            }
            if (option == 2)
            {
                do
                {
                    cout << endl << "\tВведите размер массивов (2 - 10): ";
                    row = getValueInt();

                } while (row < 2 || row > 10);
                col = row;

                A.initialize2D(row, col);
                B.initialize2D(row, col);

                cout << endl;
                cout << "\tМассив А[" << row << "][" << col << "] заполняем значениями:" << endl;;
                A.inputArray2D();
                cout << "\tМассив B[" << row << "][" << col << "] заполняем значениями:" << endl;;
                B.inputArray2D();

                cout << endl << "\tМассивы инициализированы." << endl;
                operate = true;
                install = true;
            }
            if (option == 3)
            {
                break;
            }

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();
        }break;

        case 2:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl << endl << endl;

            if (operate)
            {
                cout << "\tМассив А[" << row << "][" << col << "]:" << endl << endl;
                A.outputArray2D();
                dot(26);
                cout << endl << endl;
                cout << "\tМассив B[" << row << "][" << col << "]:" << endl << endl;
                B.outputArray2D();

                cout << endl;
                dash(80);
                cout << endl << endl;
                cout << "\tМассив C[" << row << "][" << col << "]:" << endl << endl;
                C.outputArray2D();
            }
            else
                cout << "\tПараметры массива не заданы (1 пункт меню)." << endl;;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();

        }break;

        case 3:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl << endl << endl;
            if (operate)
            {
                cout << "\tМассив А[" << row << "][" << col << "]:" << endl << endl;
                A.outputArray2D();
                dot(26);
                cout << endl << endl;
                cout << "\tМассив B[" << row << "][" << col << "]:" << endl << endl;
                B.outputArray2D();

                cout << endl;
                cout << "\tСлаживаем данные массивов --> A[" << row << "][" << col << "] + B[" << row << "][" << col << "]" << endl << endl;
                C = A + B;

                cout << endl;
                dash(80);
                cout << endl << endl;
                cout << "\tРезультат 3 пункта меню:" << endl;
                cout << "\tМассив C[" << row << "][" << col << "]:" << endl << endl;
                C.outputArray2D();
            }
            else
                cout << "\tПараметры массива не заданы (1 пункт меню)." << endl;;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();

        }break;

        case 4:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl << endl << endl;
            if (operate)
            {
                cout << "\tМассив А[" << row << "][" << col << "]:" << endl << endl;
                A.outputArray2D();
                dot(26);
                cout << endl << endl;
                cout << "\tМассив B[" << row << "][" << col << "]:" << endl << endl;
                B.outputArray2D();

                cout << endl;
                cout << "\tУмножаем данные массивов --> A[" << row << "][" << col << "] * B[" << row << "][" << col << "]" << endl << endl;
                C = A * B;

                cout << endl;
                dash(80);
                cout << endl << endl;
                cout << "\tРезультат 4 пункта меню:" << endl;
                cout << "\tМассив C[" << row << "][" << col << "]:" << endl << endl;
                C.outputArray2D();
            }
            else
                cout << "\tПараметры массива не заданы (1 пункт меню)." << endl;;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();

        }break;

        case 5:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl << endl << endl;
            if (operate)
            {
                cout << "\tМассив А[" << row << "][" << col << "]:" << endl << endl;
                A.outputArray2D();
                cout << endl;
                cout << "\tМассив B[" << row << "][" << col << "]:" << endl << endl;
                B.outputArray2D();

                cout << endl;
                dot(26);
                cout << endl << endl;
                cout << "\tТранспонируем массив  --> A[" << row << "][" << col << "]." << endl;
                A.Transpose();
                cout << "\tТранспонируем массив  --> B[" << row << "][" << col << "]." << endl;
                B.Transpose();
                cout << endl;
                dash(80);
                cout << endl << endl;
                cout << "\tРезультат 5 пункта меню:" << endl;
                cout << "\tПолучаем из исходной матрицы A заменой строк на столбцы." << endl;
                cout << "\tМассив A[" << row << "][" << col << "]:" << endl << endl;
                A.outputArray2D();

                cout << endl;
                cout << "\tПолучаем из исходной матрицы B заменой строк на столбцы." << endl;
                cout << "\tМассив B[" << row << "][" << col << "]:" << endl << endl;
                B.outputArray2D();
            }
            else
                cout << "\tПараметры массива не заданы (1 пункт меню)." << endl;;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();

        }break;

        case 6:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl << endl << endl;
            if (operate)
            {
                C = B = A;
                cout << "\tМассивы были присвоены друг другу." << endl;
                cout << "\tПросмотр массивов выберете 2 пункт главного меню." << endl;
            }
            else
                cout << "\tПараметры массива не заданы (1 пункт меню)." << endl;;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
            enter = getche();

        }break;

        case 7:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 7 пункт меню |_______" << endl << endl << endl;
            if (operate)
            {
                show_exemple = true;
            }
            else
                cout << "\tПараметры массива не заданы (1 пункт меню)." << endl;;

            if (show_exemple)
            {
                do
                {
                    cout << endl;
                    equal(80);
                    cout << endl;
                    //установка и получение произвольного элемента матрицы.
                    cout << "\tМассив А[" << row << "][" << col << "]:" << endl << endl;
                    A.outputArray2D();
                    index1 = rand() % row;
                    index2 = rand() % col;
                    value2 = (rand() % 21 - 10) / float((rand() % 10 + 1));

                    cout << endl;
                    dot(26);
                    cout << endl << endl;
                    cout << "\tРезультат 7 пункта меню:" << endl << endl;
                    cout << "\t1) Произвольный элемнт массива определен:" << endl;
                    cout << "\t   Элемент массива под индесками А[" << index1 << "][" << index2 << "] = " << A.getRandomElement2D(index1, index2) << endl;

                    cout << endl << "\t";
                    dotdot(50);
                    cout << endl << endl;

                    cout << "\t2) Устанавливаем произвольное занчение в А[" << index1 << "][" << index2 << "]:" << endl;
                    A.inputRandomElement2D(index1, index2, value2);
                    cout << "\t   Числовое значение установлено --> в А[" << index1 << "][" << index2 << "] = " << value2 << endl;
                    cout << endl;
                    dot(26);
                    cout << endl << endl;
                    cout << "\tМассив А[" << row << "][" << col << "]:" << endl << endl;
                    A.outputArray2D();

                    cout << endl << "\t";
                    dotdot(32);
                    cout << endl << "\tY - Повторить 7 пункт меню.";
                    cout << endl << "     |  Q - Выход в Главное меню.";
                    cout << endl << "     '->";
                    repeat = getche();
                } while (repeat == 'y' || repeat == 'Y');
            }
            else
            {
                cout << endl;
                dotdot(80);
                cout << endl;
                tabs(9);
                cout << endl;
                equal(80);
                cout << endl << "\tВернутся в главное меню нажмите-<ENTER>";
                enter = getche();
            }

        }break;

        case 8:
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

    cout << endl << "\t\t\t    ..........................";
    cout << endl << "\t\t\t    |                        |";
    cout << endl << "\t\t\t    |     Всего хорошего     |";
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
void       dash(int count) { for (int i = 0; i < count; i++) cout << "-"; }
void        dot(int count) { for (int i = 0; i < count; i++) cout << "  ."; }
void     dotdot(int count) { for (int i = 0; i < count; i++) cout << "."; }
void      equal(int count) { for (int i = 0; i < count; i++) cout << "="; }
void       tabs(int count) { for (int i = 0; i < count; i++) cout << "\t|"; }
void apostrophe(int count) { for (int i = 0; i < count; i++) cout << "`"; }
void underscore(int count) { for (int i = 0; i < count; i++) cout << "_"; }
void eatline(void) { while (getchar() != '\n') continue; }
*/

// Задание 2.
// Создайте шаблонный класс матрица. Необходимо реализовать:
// - динамическое выделение памяти;
// - очистку памяти;
// - заполнение матрицы с клавиатуры;
// - заполнение случайными значениями;
// - отображение матрицы;
// - арифметические операции с помощью перегруженных операторов (+, –, *,  /),
// - поиск максимального и минимального элемента.

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

///////////////////////////////////////////////////////////////////////////////

int getValueInt();
double getValueDouble();

///////////////////////////////////////////////////////////////////////////////
//============= двумерный массив ==============================================
template <class XX>
class Array2D
{
public:
    int size;
    XX **array2D;
    Array2D()
    {
        size = 1;
        array2D = new XX *[size];
        for (int i = 0; i < size; i++)
        {
            array2D[i] = new XX[size];
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                array2D[i][j] = 0;
            }
        }
    }
    Array2D(const Array2D &obj)
    {
        size = obj.size;
        array2D = new XX *[size];
        for (int i = 0; i < size; i++)
        {
            array2D[i] = new XX[size];
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                array2D[i][j] = obj.array2D[i][j];
            }
        }
    }
    ~Array2D()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] array2D[i];
        }
        delete[] array2D;
        array2D = nullptr;
    }
    void initialize2D(int n);
    void inputArray2D();
    void inputArray2DRandom();
    void outputArray2D();
    void sortArray2D();
    int maxIndex2D_1();
    int maxIndex2D_2();
    int minIndex2D_1();
    int minIndex2D_2();
    XX getValue2D();
    XX maxElement2D();
    XX minElement2D();
    Array2D operator+(const Array2D &obj);
    Array2D operator-(const Array2D &obj);
    Array2D operator*(const Array2D &obj);
    Array2D operator/(const Array2D &obj);
};

template <class XX>
void Array2D<XX>::initialize2D(int n)
{
    size = n;
    array2D = new XX *[size];
    for (int i = 0; i < size; i++)
    {
        array2D[i] = new XX[size];
    }
}

template <class XX>
void Array2D<XX>::inputArray2DRandom()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            //заполнение массива случайными числами с масштабированием от -10 до 10
            array2D[i][j] = (rand() % 21 - 10) / XX((rand() % 10 + 1));
        }
    }
}

template <class XX>
void Array2D<XX>::inputArray2D()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            do
            {
                cout << endl
                     << "\tВведите [" << i << "][" << j << "] элемент массива:";
                array2D[i][j] = getValue2D();

            } while (array2D[i][j] < -10 || array2D[i][j] > 10);
        }
    }
}

template <class XX>
void Array2D<XX>::outputArray2D()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << " [" << setw(2) << i << "][" << setw(2) << j << "]=" << setprecision(2) << setw(6) << left << array2D[i][j];

            if ((j + 1) % 5 == 0)
                cout << endl;
        }
        cout << endl;
    }
}

// проверка ввода
template <class XX>
XX Array2D<XX>::getValue2D()
{
    XX a;
    cout << endl;
    cout << "     |" << endl;
    cout << "     '->";
    cin >> a;
    eatline();

    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();

    return a;
}

// сортировка массива
template <class XX>
void Array2D<XX>::sortArray2D()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int a = 0; a < size; a++)
            {
                for (int b = 0; b < size; b++)
                {
                    if (array2D[a][b] > array2D[i][j])
                    {
                        XX temp = array2D[a][b];
                        array2D[a][b] = array2D[i][j];
                        array2D[i][j] = temp;
                    }
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
// Нахождение минимальных и максимальных элементов и из значений
template <class XX>
int Array2D<XX>::maxIndex2D_1()
{
    int k = 0;
    XX max = array2D[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] > max)
                k = i;
        }
    }
    return k;
}
template <class XX>
int Array2D<XX>::maxIndex2D_2()
{
    int k = 0;
    XX max = array2D[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] > max)
                k = j;
        }
    }
    return k;
}
template <class XX>
int Array2D<XX>::minIndex2D_1()
{
    int k = 0;
    XX min = array2D[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] < min)
                k = i;
        }
    }
    return k;
}
template <class XX>
int Array2D<XX>::minIndex2D_2()
{
    int k = 0;
    XX min = array2D[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] < min)
                k = j;
        }
    }
    return k;
}
template <class XX>
XX Array2D<XX>::maxElement2D()
{
    XX max = array2D[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] > max)
                max = array2D[i][j];
        }
    }
    return max;
}
template <class XX>
XX Array2D<XX>::minElement2D()
{
    XX min = array2D[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] < min)
                min = array2D[i][j];
        }
    }
    return min;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Перегрузки операторов: +, -, *, /.
template <class XX>
Array2D<XX> Array2D<XX>::operator+(const Array2D &obj)
{
    size = obj.size;
    Array2D temp(*this);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp.array2D[i][j] = array2D[i][j] + obj.array2D[i][j];
        }
    }

    return temp;
}
template <class XX>
Array2D<XX> Array2D<XX>::operator-(const Array2D &obj)
{
    size = obj.size;
    Array2D temp(*this);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp.array2D[i][j] = array2D[i][j] - obj.array2D[i][j];
        }
    }
    return temp;
}
template <class XX>
Array2D<XX> Array2D<XX>::operator*(const Array2D &obj)
{
    size = obj.size;
    Array2D temp(*this);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp.array2D[i][j] = 0;
            for (int k = 0; k < size; k++)
                temp.array2D[i][j] += array2D[i][k] * obj.array2D[k][j];
        }
    }
    return temp;
}
template <class XX>
Array2D<XX> Array2D<XX>::operator/(const Array2D &obj)
{
    size = obj.size;
    Array2D temp(*this);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp.array2D[i][j] = 0;
            for (int k = 0; k < obj.size; k++)
            {
                if (array2D[i][k] == 0 && obj.array2D[k][j] != 0)
                {
                    temp.array2D[i][j] += array2D[i][k];
                }
                else if (array2D[i][k] != 0 && obj.array2D[k][j] == 0)
                {
                    temp.array2D[i][j] += obj.array2D[k][j];
                }
                else if (array2D[i][k] != 0 && obj.array2D[k][j] != 0)
                    temp.array2D[i][j] += array2D[i][k] * (1 / obj.array2D[k][j]);
            }
        }
    }
    return temp;
}
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
//=============================================================================
int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(nullptr));

    Array2D<int> array2D_int_A;
    Array2D<int> array2D_int_B;
    Array2D<int> array2D_int_C;
    Array2D<double> array2D_double_A;
    Array2D<double> array2D_double_B;
    Array2D<double> array2D_double_C;

    int size; // размер массивов

    int menu;
    int option;
    int choice;
    int select = 0;
    char enter;

    bool array2D_INT = false;
    bool array2D_DOUBLE = false;
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
        cout << "\t       ***| Задание 2.2 Лекция 6 (template <class XX>) |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню:" << endl;
        cout << "\t1. Выбор тип данных массивов." << endl;
        cout << "\t2. Задать параметры массивов." << endl;
        cout << "\t3. Просмотр значений массивов." << endl;
        cout << "\t4. Сортировка массивов." << endl;
        cout << "\t5. Сложение массивов." << endl;
        cout << "\t6. Вычитание массивов." << endl;
        cout << "\t7. Умножение массивов." << endl;
        cout << "\t8. Деление массивов." << endl;
        cout << "\t9. Нахождение min и max значения массивов." << endl;
        cout << "\t10.  | ВыхоД |";
        do
        {
            menu = 0;
            menu = getValueInt();

        } while (menu <= 0);

        cout << endl;

        switch (menu)
        {
        case 1: // тип данных
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array2D_INT || array2D_DOUBLE)
            {
                cout << "\tТип данных массивов уже задан." << endl;
                cout << "\tЖелаете изменить тип данных?." << endl;
                cout << "\t1 - ДА." << endl;
                cout << "\t2 - НЕТ.";
                do // защита ввода
                {
                    choice = 0;
                    choice = getValueInt();

                    if (choice != 1 && choice != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод.";
                        cout << endl
                             << "\tПожалуйста сделайте выбор.";
                    }
                } while (choice != 1 && choice != 2);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (choice == 1)
                {
                    cout << "\t   Выберите ПУНКТ меню в котором будет работать программа:" << endl;
                    cout << "\t1. Двумерные массивы тип данных int." << endl;
                    cout << "\t2. Двумерные массивы тип данных double." << endl;
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
                }
                if (choice == 2)
                {
                    break;
                }
            }
            else
            {
                cout << "\t   Выберите ПУНКТ меню в котором будет работать программа:" << endl;
                cout << "\t1. Двумерные массивы тип данных int." << endl;
                cout << "\t2. Двумерные массивы тип данных double." << endl;
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
            }

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            if (option == 1)
            {
                cout << "\tЗадан режим работы программы:" << endl;
                cout << "\tДвумерные массивы." << endl;
                cout << "\tТип данных массивов int." << endl;
                array2D_INT = true;
                array2D_DOUBLE = false;
                install = false;
                operate = false;
            }
            if (option == 2)
            {
                cout << "\tЗадан режим работы программы:" << endl;
                cout << "\tДвумерные массивы." << endl;
                cout << "\tТип данных массивов double." << endl;
                array2D_INT = false;
                array2D_DOUBLE = true;
                install = false;
                operate = false;
            }
            if (option == 3)
            {
                break;
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
        break;

        case 2: // инсталляция
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array2D_INT || array2D_DOUBLE)
            {
                if (install)
                {
                    cout << "\tМассивы уже инициализированы." << endl;
                    cout << "\tЖелаете переинициализировать массивы." << endl;
                    cout << "\t1 - ДА." << endl;
                    cout << "\t2 - НЕТ.";
                    do // защита ввода
                    {
                        choice = 0;
                        choice = getValueInt();

                        if (choice != 1 && choice != 2)
                        {
                            cout << endl
                                 << "\tНекорректный ввод.";
                            cout << endl
                                 << "\tПожалуйста сделайте выбор.";
                        }
                    } while (choice != 1 && choice != 2);

                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (choice == 1)
                    {
                        cout << "\t1. Заполнить массивы случайными числами." << endl;
                        cout << "\t2. Заполнить массивы вручную." << endl;
                        cout << "\t3.   | Отмена |"; // оставить как есть
                        do                           // защита ввода
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
                            if (array2D_INT)
                            {
                                cout << "\tВведите размеры массивов (2 - 10): ";
                                do
                                {
                                    size = getValueInt();

                                } while (size < 2 || size > 10);

                                cout << endl;
                                cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_int_A.initialize2D(size);
                                array2D_int_A.inputArray2DRandom();
                                cout << endl;
                                cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_int_B.initialize2D(size);
                                array2D_int_B.inputArray2DRandom();
                            }
                            if (array2D_DOUBLE)
                            {
                                cout << "\tВведите размеры массивов (2 - 10): ";
                                do
                                {
                                    size = getValueInt();

                                } while (size < 2 || size > 100);

                                cout << endl;
                                cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_double_A.initialize2D(size);
                                array2D_double_A.inputArray2DRandom();
                                cout << endl;
                                cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_double_B.initialize2D(size);
                                array2D_double_B.inputArray2DRandom();
                            }
                            cout << endl
                                 << "\tМассивы инициализированы." << endl;
                            operate = true;
                            install = true;
                        }
                        if (option == 2)
                        {
                            if (array2D_INT)
                            {
                                cout << "\tВведите размеры массивов (2 - 10): ";
                                do
                                {
                                    size = getValueInt();

                                } while (size < 2 || size > 10);

                                cout << endl;
                                cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_int_A.initialize2D(size);
                                array2D_int_A.inputArray2D();
                                cout << endl;
                                cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_int_B.initialize2D(size);
                                array2D_int_B.inputArray2D();
                            }
                            if (array2D_DOUBLE)
                            {
                                cout << "\tВведите размер массива (2 - 10): ";
                                do
                                {
                                    size = getValueInt();

                                } while (size < 2 || size > 100);

                                cout << endl;
                                cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_double_A.initialize2D(size);
                                array2D_double_A.inputArray2D();
                                cout << endl;
                                cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                                array2D_double_B.initialize2D(size);
                                array2D_double_B.inputArray2D();
                            }
                            cout << endl
                                 << "\tМассивы инициализированы." << endl;
                            operate = true;
                            install = true;
                        }
                    }
                    if (choice == 2)
                    {
                        break;
                    }
                }
                else
                {
                    cout << "\t1. Заполнить массивы случайными числами." << endl;
                    cout << "\t2. Заполнить массивы вручную." << endl;
                    cout << "\t3.   | Отмена |"; // оставить как есть
                    do                           // защита ввода
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
                        if (array2D_INT)
                        {
                            cout << "\tВведите размеры массивов (2 - 10): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 10);

                            cout << endl;
                            cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_int_A.initialize2D(size);
                            array2D_int_A.inputArray2DRandom();
                            cout << endl;
                            cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_int_B.initialize2D(size);
                            array2D_int_B.inputArray2DRandom();
                        }
                        if (array2D_DOUBLE)
                        {
                            cout << "\tВведите размеры массивов (2 - 10): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            cout << endl;
                            cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_double_A.initialize2D(size);
                            array2D_double_A.inputArray2DRandom();
                            cout << endl;
                            cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_double_B.initialize2D(size);
                            array2D_double_B.inputArray2DRandom();
                        }

                        cout << endl
                             << "\tМассивы инициализированы." << endl;
                        operate = true;
                        install = true;
                    }
                    if (option == 2)
                    {
                        if (array2D_INT)
                        {
                            cout << "\tВведите размеры массивов (2 - 10):";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 10);

                            cout << endl;
                            cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_int_A.initialize2D(size);
                            array2D_int_A.inputArray2D();
                            cout << endl;
                            cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_int_B.initialize2D(size);
                            array2D_int_B.inputArray2D();
                        }
                        if (array2D_DOUBLE)
                        {
                            cout << "\tВведите размер массива (2 - 10): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            cout << endl;
                            cout << "\tМассив А[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_double_A.initialize2D(size);
                            array2D_double_A.inputArray2D();
                            cout << endl;
                            cout << "\tМассив B[" << size << "][" << size << "] заполняем значениями:" << endl;
                            array2D_double_B.initialize2D(size);
                            array2D_double_B.inputArray2D();
                        }
                        cout << endl
                             << "\tМассивы инициализированы." << endl;
                        operate = true;
                        install = true;
                    }
                }
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 3: // вывод на экран заначений массивов
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_B.outputArray2D();

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_C.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_B.outputArray2D();

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_C.outputArray2D();
                    }
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
                ;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        array2D_int_A.sortArray2D();
                        array2D_int_B.sortArray2D();
                        array2D_int_C.sortArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        array2D_double_A.sortArray2D();
                        array2D_double_B.sortArray2D();
                        array2D_double_C.sortArray2D();
                    }

                    cout << "\tЭлементы массивов отсортированы по возрастанию." << endl;
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 5:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
                 << endl
                 << endl;
            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_B.outputArray2D();

                        cout << endl;
                        cout << "\tСлаживаем данные массивов --> A[" << size << "][" << size << "] + B[" << size << "][" << size << "]" << endl;
                        array2D_int_C = array2D_int_A + array2D_int_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 5 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_C.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_B.outputArray2D();

                        cout << endl;
                        cout << "\tСлаживаем данные массива --> A[" << size << "][" << size << "] + B[" << size << "][" << size << "]" << endl;
                        array2D_double_C = array2D_double_A + array2D_double_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 5 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_C.outputArray2D();
                    }
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 6:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
                 << endl
                 << endl;
            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_B.outputArray2D();

                        cout << endl;
                        cout << "\tВычитаем данные из массива --> A[" << size << "][" << size << "] - B[" << size << "][" << size << "]" << endl;
                        array2D_int_C = array2D_int_A - array2D_int_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 6 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_C.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_B.outputArray2D();

                        cout << endl;
                        cout << "\tВычитаем данные из массива --> A[" << size << "][" << size << "] - B[" << size << "][" << size << "]" << endl;
                        array2D_double_C = array2D_double_A - array2D_double_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 6 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_C.outputArray2D();
                    }
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 7:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 7 пункт меню |_______" << endl
                 << endl
                 << endl;
            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_B.outputArray2D();

                        cout << endl;
                        cout << "\tУмножаем данные из массива --> A[" << size << "][" << size << "] * B[" << size << "][" << size << "]" << endl;
                        array2D_int_C = array2D_int_A * array2D_int_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 7 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_C.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_B.outputArray2D();

                        cout << endl;
                        cout << "\tУмножаем данные из массива --> A[" << size << "][" << size << "] * B[" << size << "][" << size << "]" << endl;
                        array2D_double_C = array2D_double_A - array2D_double_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 7 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_C.outputArray2D();
                    }
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 8:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 8 пункт меню |_______" << endl
                 << endl
                 << endl;
            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_B.outputArray2D();

                        cout << endl;
                        cout << "\tДелим данные из массива --> A[" << size << "][" << size << "] / B[" << size << "][" << size << "]" << endl;
                        array2D_int_C = array2D_int_A / array2D_int_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 8 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_int_C.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМассив А[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_A.outputArray2D();
                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМассив B[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_B.outputArray2D();

                        cout << endl;
                        cout << "\tДелим данные из массива --> A[" << size << "][" << size << "] / B[" << size << "][" << size << "]" << endl;
                        array2D_double_C = array2D_double_A / array2D_double_B;

                        cout << endl;
                        dash(80);
                        cout << endl
                             << endl;
                        cout << "\tРезультат 8 пункта меню:" << endl;
                        cout << "\tМассив C[" << size << "][" << size << "]:" << endl
                             << endl;
                        array2D_double_C.outputArray2D();
                    }
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 9:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 9 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array2D_INT)
                    {
                        cout << "\tМинимальный  элемент массива А:" << endl;
                        cout << "\t A[" << array2D_int_A.minIndex2D_1() << "][" << array2D_int_A.minIndex2D_2() << "] = " << array2D_int_A.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива A:" << endl;
                        cout << "\t A[" << array2D_int_A.maxIndex2D_1() << "][" << array2D_int_A.maxIndex2D_2() << "] = " << array2D_int_A.maxElement2D() << endl
                             << endl;

                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМинимальный  элемент массива B:" << endl;
                        cout << "\t B[" << array2D_int_B.minIndex2D_1() << "][" << array2D_int_B.minIndex2D_2() << "] = " << array2D_int_B.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива B:" << endl;
                        cout << "\t B[" << array2D_int_B.maxIndex2D_1() << "][" << array2D_int_B.maxIndex2D_2() << "] = " << array2D_int_B.maxElement2D() << endl
                             << endl;

                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМинимальный  элемент массива C:" << endl;
                        cout << "\t C[" << array2D_int_C.minIndex2D_1() << "][" << array2D_int_C.minIndex2D_2() << "] = " << array2D_int_C.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива C:" << endl;
                        cout << "\t C[" << array2D_int_C.maxIndex2D_1() << "][" << array2D_int_C.maxIndex2D_2() << "] = " << array2D_int_C.maxElement2D() << endl
                             << endl;
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМинимальный  элемент массива A:" << endl;
                        cout << "\t A[" << array2D_double_A.minIndex2D_1() << "][" << array2D_double_A.minIndex2D_2() << "] = " << array2D_double_A.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива A:" << endl;
                        cout << "\t A[" << array2D_double_A.maxIndex2D_1() << "][" << array2D_double_A.maxIndex2D_2() << "] = " << array2D_double_A.maxElement2D() << endl
                             << endl;

                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМинимальный  элемент массива B:" << endl;
                        cout << "\t B[" << array2D_double_A.minIndex2D_1() << "][" << array2D_double_A.minIndex2D_2() << "] = " << array2D_double_A.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива B:" << endl;
                        cout << "\t B[" << array2D_double_A.maxIndex2D_1() << "][" << array2D_double_A.maxIndex2D_2() << "] = " << array2D_double_A.maxElement2D() << endl
                             << endl;

                        dot(26);
                        cout << endl
                             << endl;
                        cout << "\tМинимальный  элемент массива C:" << endl;
                        cout << "\t C[" << array2D_double_A.minIndex2D_1() << "][" << array2D_double_A.minIndex2D_2() << "] = " << array2D_double_A.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива C:" << endl;
                        cout << "\t C[" << array2D_double_A.maxIndex2D_1() << "][" << array2D_double_A.maxIndex2D_2() << "] = " << array2D_double_A.maxElement2D() << endl
                             << endl;
                    }
                }
                else
                    cout << "\tПараметры массива не заданы (2 пункт меню)." << endl;
            }
            else
                cout << "\tРежим работы программы не определен (1 пункт меню)." << endl;

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

        case 10:
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

