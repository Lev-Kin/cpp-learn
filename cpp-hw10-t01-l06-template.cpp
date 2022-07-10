
// Реализуйте шаблонные функции для поиска максимума, минимума, сортировки массива
// (любым алгоритмом сортировки), двоичного поиска в массиве, замены элемента массива
// на переданное значение. Рассмотреть одномерный и двумерный массив.
// Шаблонные функции реализовать на конкретных примерах работающих программ.

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
//==== одномерный массив =====================================================
template <class X>
class Array
{
public:
    int size;
    X *array;
    Array()
    {
        size = 0;
        array = new X[size];
    }
    Array(const Array &obj)
    {
        size = obj.size;
        array = new X[size];
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
    X getValue();
    X maxElement();
    X minElement();
    void inputElement(int index1, X value);
    int binarySearch(X value);
};

template <class X>
void Array<X>::initialize(int n)
{
    size = n;
    array = new X[size];
}

template <class X>
void Array<X>::inputArray()
{
    for (int i = 0; i < size; i++)
    {
        do
        {
            cout << endl
                 << "\tВведите [" << i << "] элемент массива:";
            array[i] = getValue();

        } while (array[i] < -10 || array[i] > 10);
    }
}

template <class X>
void Array<X>::inputArrayRandom()
{
    for (int i = 0; i < size; i++)
    {
        //заполнение массива случайными числами с масштабированием от -10 до 10
        array[i] = (rand() % 21 - 10) / X((rand() % 10 + 1));
    }
}

template <class X>
void Array<X>::outputArray()
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

template <class X>
void Array<X>::sortArray()
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j])
            {
                X temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

template <class X>
void Array<X>::reinitialize(int resize, int select)
{
    if (resize <= size)
    {
        X *array_new = new X[resize];
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
        X *array_new = new X[resize];
        for (int i = 0; i < resize; i++)
        {
            array_new[i] = array[i];
        }
        for (int i = size; i < resize; i++)
        {
            //заполнение массива случайными числами с масштабированием от -10 до 10
            array_new[i] = (rand() % 21 - 10) / X((rand() % 10 + 1));
        }
        delete[] array;
        array = array_new;
        size = resize;
    }
    else
    {
        X *array_new = new X[resize];
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
                array_new[i] = getValue();

            } while (array_new[i] < -10 || array_new[i] > 10);
        }
        delete[] array;
        array = array_new;
        size = resize;
    }
}

template <class X>
int Array<X>::maxIndex()
{
    int j = 0;
    X max = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
            j = i;
    }
    return j;
}
template <class X>
int Array<X>::minIndex()
{
    int j = 0;
    X min = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] < min)
            j = i;
    }
    return j;
}
template <class X>
X Array<X>::maxElement()
{
    X max = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}
template <class X>
X Array<X>::minElement()
{
    X min = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
    }
    return min;
}

// ввод нового элемента в пазицию
template <class X>
void Array<X>::inputElement(int index1, X value)
{
    for (int i = 0; i < size; i++)
    {
        if (i == (index1))
        {
            array[i] = value;
        }
    }
}

template <class X>
int Array<X>::binarySearch(X value)
{
    int left = 0;         // левая  граница начало
    int right = size - 1; // правая граница size -1? variable

    while (left <= right) // Если L > R поиск прекращается как неудачный.
    {
        int middle = left + (right - left) / 2; // положение среднего элемента floor
        if (value == array[middle])
            return middle;
        if (value < array[middle])
            right = middle - 1; // Если array меньше, игнорировать правую границу
        if (value > array[middle])
            left = middle + 1; // Если array больше, игнорировать левую  границу
    }
    return -1;
}

template <class X>
X Array<X>::getValue()
{
    X a;
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
    void reinitialize2D(int resize, int select);
    int maxIndex2D_1();
    int maxIndex2D_2();
    int minIndex2D_1();
    int minIndex2D_2();
    XX getValue2D();
    XX maxElement2D();
    XX minElement2D();
    void inputElement2D(int index1, int index2, XX value);
    int Search2D(XX value);
    void binarySearch2D(XX value);
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
void Array2D<XX>::outputArray2D()
{
    cout << "\tМассив данных:" << endl
         << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << " [" << setw(2) << i << "][" << setw(2) << j << "]=" << setprecision(2) << setw(6) << left << array2D[i][j];

            if ((j + 1) % 5 == 0)
                cout << endl;
        }
        cout << endl
             << endl;
    }
}

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

template <class XX>
void Array2D<XX>::reinitialize2D(int resize, int select)
{
    if (resize <= size)
    {
        XX **array_new = new XX *[resize];
        for (int i = 0; i < resize; i++)
        {
            array_new[i] = new XX[resize];
        }

        for (int i = 0; i < resize; i++)
        {
            for (int j = 0; j < resize; j++)
            {
                array_new[i][j] = array2D[i][j];
            }
        }

        for (int i = 0; i < size; i++)
        {
            delete[] array2D[i];
        }
        delete[] array2D;
        array2D = nullptr;

        for (int i = 0; i < resize; i++)
        {
            for (int j = 0; j < resize; j++)
            {
                array2D = array_new;
            }
        }

        size = resize;
    }
    if (resize > size && select == 1)
    {
        XX **array_new = new XX *[resize];
        for (int i = 0; i < resize; i++)
        {
            array_new[i] = new XX[resize];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                array_new[i][j] = array2D[i][j];
            }
        }

        for (int i = size; i < resize; i++)
        {
            for (int j = size; j < resize; j++)
            {
                //заполнение массива случайными числами с масштабированием от -10 до 10
                array_new[i][j] = (rand() % 21 - 10) / XX((rand() % 10 + 1));
            }
        }

        for (int i = 0; i < size; i++)
        {
            delete[] array2D[i];
        }
        delete[] array2D;
        array2D = nullptr;

        for (int i = 0; i < resize; i++)
        {
            for (int j = 0; j < resize; j++)
            {
                array2D = array_new;
            }
        }

        size = resize;
    }
    else
    {
        XX **array_new = new XX *[resize];
        for (int i = 0; i < resize; i++)
        {
            array_new[i] = new XX[resize];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                array_new[i][j] = array2D[i][j];
            }
        }

        for (int i = size; i < resize; i++)
        {
            for (int j = size; j < resize; j++)
            {
                do
                {
                    cout << endl
                         << "\tВведите [" << i << "][" << j << "] элемент массива:";
                    array_new[i][j] = getValue2D();

                } while (array_new[i][j] < -10 || array_new[i][j] > 10);
            }
        }

        for (int i = 0; i < size; i++)
        {
            delete[] array2D[i];
        }
        delete[] array2D;
        array2D = nullptr;

        for (int i = 0; i < resize; i++)
        {
            for (int j = 0; j < resize; j++)
            {
                array2D = array_new;
            }
        }

        size = resize;
    }
}

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

// ввод нового элемента в позицию
template <class XX>
void Array2D<XX>::inputElement2D(int index1, int index2, XX value)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == (index1) && j == (index2))
            {
                array2D[i][j] = value;
            }
        }
    }
}

template <class XX>
int Array2D<XX>::Search2D(XX value)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (array2D[i][j] == value)
                return 1;

    return 0;
}

template <class XX>
void Array2D<XX>::binarySearch2D(XX value)
{
    int a = 0;
    int b = 0;
    int start_i = 0;
    int start_j = 0;
    int index1 = 0;
    int index2 = 0;
    bool key_i = false;
    bool key_j = false;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array2D[i][j] == value)
            {
                a = i;
                b = j;
                if (key_i == false)
                {
                    start_i = i;
                    key_i = true;
                }
                if (key_j == false)
                {
                    start_j = j;
                    key_j = true;
                }
            }
        }
    }
    index1 = (start_i + a) / 2;
    index2 = (start_j + b) / 2;

    cout << "\t[" << index1 << "][" << index2 << "]" << endl
         << endl;
}
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

///////////////////////////////////////////////////////////////////////////////
//=============================================================================
int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(nullptr));

    Array<int> array_int;
    Array<double> array_double;
    Array2D<int> array2D_int;
    Array2D<double> array2D_double;

    int size; // размер массива
    int resize;
    int index1; // для изменения индекса в массиве
    int index2;
    int value1; // значение для замены в исходном индексе массива
    double value2;

    int menu;
    int option;
    int choice;
    int select = 0;
    char enter;

    bool array_INT = false;
    bool array_DOUBLE = false;
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
        cout << "\t\t\t   ***| Задание 1 Лекция 6 |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню:" << endl;
        cout << "\t1. Выбор Размера массива и типа данных." << endl;
        cout << "\t2. Задать параметры массива." << endl;
        cout << "\t3. Просмотр значений массива." << endl;
        cout << "\t4. Редактирование массива." << endl;
        cout << "\t5. Сортировка массива." << endl;
        cout << "\t6. Нахождение min и max значения массива." << endl;
        cout << "\t7. Замена элемента в массиве." << endl;
        cout << "\t8. Двоичный поиск в массиве." << endl;
        cout << "\t9.   | ВыхоД |";
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
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
                cout << "\tРазмерость массива и тип данных уже задан." << endl;
                cout << "\tЖелаете изменить размерность массива и тип данных?." << endl;
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
                    cout << "\t1. Одномерный массив тип данных int." << endl;
                    cout << "\t2. Одномерный массив тип данных double." << endl;
                    cout << "\t3. Двумерный  массив тип данных int." << endl;
                    cout << "\t4. Двумерный  массив тип данных double." << endl;
                    cout << "\t5.   | Отмена |"; // оставить как есть

                    do // защита ввода
                    {
                        option = 0;
                        option = getValueInt();

                        if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5)
                        {
                            cout << endl
                                 << "\tНекорректный ввод (Действие = 5 -отмена).";
                            cout << endl
                                 << "\tПожалуйста сделайте выбор.";
                        }
                    } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5);
                }
                if (choice == 2)
                {
                    break;
                }
            }
            else
            {
                cout << "\t   Выберите ПУНКТ меню в котором будет работать программа:" << endl;
                cout << "\t1. Одномерный массив тип данных int." << endl;
                cout << "\t2. Одномерный массив тип данных double." << endl;
                cout << "\t3. Двумерный  массив тип данных int." << endl;
                cout << "\t4. Двумерный  массив тип данных double." << endl;
                cout << "\t5.   | Отмена |"; // оставить как есть

                do // защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Действие = 5 -отмена).";
                        cout << endl
                             << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5);
            }

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            if (option == 1)
            {
                cout << "\tЗадан режим работы программы:" << endl;
                cout << "\tОдномерный массив." << endl;
                cout << "\tТип данных массива int." << endl;
                array_INT = true;
                array_DOUBLE = false;
                array2D_INT = false;
                array2D_DOUBLE = false;
                install = false;
                operate = false;
            }
            if (option == 2)
            {
                cout << "\tЗадан режим работы программы:" << endl;
                cout << "\tОдномерный массив." << endl;
                cout << "\tТип данных массива double." << endl;
                array_INT = false;
                array_DOUBLE = true;
                array2D_INT = false;
                array2D_DOUBLE = false;
                install = false;
                operate = false;
            }
            if (option == 3)
            {
                cout << "\tЗадан режим работы программы:" << endl;
                cout << "\tДвумерный массив." << endl;
                cout << "\tТип данных массива int." << endl;
                array_INT = false;
                array_DOUBLE = false;
                array2D_INT = true;
                array2D_DOUBLE = false;
                install = false;
                operate = false;
            }
            if (option == 4)
            {
                cout << "\tЗадан режим работы программы:" << endl;
                cout << "\tДвумерный массив." << endl;
                cout << "\tТип данных массива double." << endl;
                array_INT = false;
                array_DOUBLE = false;
                array2D_INT = false;
                array2D_DOUBLE = true;
                install = false;
                operate = false;
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

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
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
                        if (array_INT)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array_int.initialize(size);
                            array_int.inputArrayRandom();
                        }
                        if (array_DOUBLE)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array_double.initialize(size);
                            array_double.inputArrayRandom();
                        }
                        if (array2D_INT) ////////////////////////////////////////////////
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array2D_int.initialize2D(size);
                            array2D_int.inputArray2DRandom();
                        }
                        if (array2D_DOUBLE)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array2D_double.initialize2D(size);
                            array2D_double.inputArray2DRandom();
                        }

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
                }
                if (option == 2)
                {
                    if (install == false)
                    {
                        if (array_INT)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array_int.initialize(size);
                            array_int.inputArray();
                        }
                        if (array_DOUBLE)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array_double.initialize(size);
                            array_double.inputArray();
                        }
                        /////////////////////////////////////////////////////////////
                        if (array2D_INT)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array2D_int.initialize2D(size);
                            array2D_int.inputArray2D();
                        }
                        if (array2D_DOUBLE)
                        {
                            cout << "\tВведите размер массива (2 - 100): ";
                            do
                            {
                                size = getValueInt();

                            } while (size < 2 || size > 100);

                            array2D_double.initialize2D(size);
                            array2D_double.inputArray2D();
                        }
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

        case 3:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array_INT)
                    {
                        array_int.outputArray();
                    }
                    if (array_DOUBLE)
                    {
                        array_double.outputArray();
                    }
                    if (array2D_INT)
                    {
                        array2D_int.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        array2D_double.outputArray2D();
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

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
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
                            if (array_INT)
                            {
                                array_int.initialize(resize);
                                array_int.inputArrayRandom();
                            }
                            if (array_DOUBLE)
                            {
                                array_double.initialize(resize);
                                array_double.inputArrayRandom();
                            }
                            ////////////////////////////////////
                            if (array2D_INT)
                            {
                                array2D_int.initialize2D(resize);
                                array2D_int.inputArray2DRandom();
                            }
                            if (array2D_DOUBLE)
                            {
                                array2D_double.initialize2D(resize);
                                array2D_double.inputArray2DRandom();
                            }

                            cout << endl
                                 << "\tМассив создан заново." << endl;
                        }
                        if (select == 2)
                        {
                            if (array_INT)
                            {
                                array_int.initialize(resize);
                                array_int.inputArray();
                            }
                            if (array_DOUBLE)
                            {
                                array_double.initialize(resize);
                                array_double.inputArray();
                            }
                            ///////////////////////////////////////////////////
                            if (array2D_INT)
                            {
                                array2D_int.initialize2D(resize);
                                array2D_int.inputArray2D();
                            }
                            if (array2D_DOUBLE)
                            {
                                array2D_double.initialize2D(resize);
                                array2D_double.inputArray2D();
                            }
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
                            if (array_INT)
                            {
                                array_int.reinitialize(resize, select);
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
                            if (array_DOUBLE)
                            {
                                array_double.reinitialize(resize, select);
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
                            ////////////////////////////////////////////////////
                            if (array2D_INT)
                            {
                                array2D_int.reinitialize2D(resize, select);
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
                            if (array2D_DOUBLE)
                            {
                                array2D_double.reinitialize2D(resize, select);
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
                        if (select == 2)
                        {
                            if (array_INT)
                            {
                                array_int.reinitialize(resize, select);
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
                            if (array_DOUBLE)
                            {
                                array_double.reinitialize(resize, select);
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
                            //////////////////////////////////////////
                            if (array2D_INT)
                            {
                                array2D_int.reinitialize2D(resize, select);
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
                            if (array2D_DOUBLE)
                            {
                                array2D_double.reinitialize2D(resize, select);
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
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array_INT)
                    {
                        array_int.sortArray();
                    }
                    if (array_DOUBLE)
                    {
                        array_double.sortArray();
                    }
                    if (array2D_INT) ////////////////////////////////////
                    {
                        array2D_int.sortArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        array2D_double.sortArray2D();
                    }

                    cout << "\tЭлементы массива отсортированы по возрастанию." << endl;
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

        case 6:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array_INT)
                    {
                        cout << "\tМинимальный  элемент массива:" << endl;
                        cout << "\t[" << array_int.minIndex() << "] = " << array_int.minElement() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива:" << endl;
                        cout << "\t[" << array_int.maxIndex() << "] = " << array_int.maxElement() << endl;
                    }
                    if (array_DOUBLE)
                    {
                        cout << "\tМинимальный  элемент массива:" << endl;
                        cout << "\t[" << array_double.minIndex() << "] = " << array_double.minElement() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива:" << endl;
                        cout << "\t[" << array_double.maxIndex() << "] = " << array_double.maxElement() << endl;
                    }
                    if (array2D_INT)
                    {
                        cout << "\tМинимальный  элемент массива:" << endl;
                        cout << "\t[" << array2D_int.minIndex2D_1() << "][" << array2D_int.minIndex2D_2() << "] = " << array2D_int.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива:" << endl;
                        cout << "\t[" << array2D_int.maxIndex2D_1() << "][" << array2D_int.maxIndex2D_2() << "] = " << array2D_int.maxElement2D() << endl;
                    }
                    if (array2D_DOUBLE)
                    {
                        cout << "\tМинимальный  элемент массива:" << endl;
                        cout << "\t[" << array2D_double.minIndex2D_1() << "][" << array2D_double.minIndex2D_2() << "] = " << array2D_double.minElement2D() << endl
                             << endl;
                        cout << "\tМаксимальный элемент массива:" << endl;
                        cout << "\t[" << array2D_double.maxIndex2D_1() << "][" << array2D_double.maxIndex2D_2() << "] = " << array2D_double.maxElement2D() << endl;
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

        case 7:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 7 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array_INT)
                    {
                        array_int.outputArray();
                        cout << endl;
                        dot(26);
                        cout << endl;
                        do
                        {
                            cout << endl
                                 << "\tВведите позицию элемента в которую хотите внести изменения:";
                            index1 = getValueInt();

                            if (index1 < 0 || index1 > array_int.size)
                            {
                                cout << "\tИндекс выходит за пределы массива." << endl;
                                cout << "\tБудьте внимательны !!!" << endl;
                            }

                        } while (index1 < 0 || index1 >= array_int.size);

                        do
                        {
                            cout << endl
                                 << "\tВведите значение которое хотите вставить в позицию:";
                            value1 = getValueInt();

                        } while (value1 < -10 || value1 > 10);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tВ позицию элемента были внесены изменения: [" << index1 << "] = " << value1 << endl
                             << endl;

                        array_int.inputElement(index1, value1);
                        array_int.outputArray();
                    }
                    if (array_DOUBLE)
                    {
                        array_double.outputArray();
                        cout << endl;
                        dot(26);
                        cout << endl;
                        do
                        {
                            cout << endl
                                 << "\tВведите позицию элемента в которую хотите внести изменения:";
                            index1 = getValueInt();

                            if (index1 < 0 || index1 > array_double.size)
                            {
                                cout << "\tИндекс выходит за пределы массива." << endl;
                                cout << "\tБудьте внимательны !!!" << endl;
                            }

                        } while (index1 < 0 || index1 >= array_double.size);

                        do
                        {
                            cout << endl
                                 << "\tВведите значение которое хотите вставить в позицию:";
                            value2 = getValueDouble();

                        } while (value2 < -10 || value2 > 10);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tВ позицию элемента были внесены изменения: [" << index1 << "] = " << value2 << endl
                             << endl;

                        array_double.inputElement(index1, value2);
                        array_double.outputArray();
                    }
                    if (array2D_INT) ////////////////////////////////////////////////////
                    {
                        array2D_int.outputArray2D();
                        cout << endl;
                        dot(26);
                        cout << endl;
                        do
                        {
                            cout << endl
                                 << "\tВведите [позицию 1][] элемента в которую хотите внести изменения:";
                            index1 = getValueInt();

                            if (index1 < 0 || index1 > array2D_int.size)
                            {
                                cout << "\tИндекс выходит за пределы массива." << endl;
                                cout << "\tБудьте внимательны !!!" << endl;
                            }

                        } while (index1 < 0 || index1 >= array2D_int.size);
                        do
                        {
                            cout << endl
                                 << "\tВведите [][позицию 2] элемента в которую хотите внести изменения:";
                            index2 = getValueInt();

                            if (index2 < 0 || index2 > array2D_int.size)
                            {
                                cout << "\tИндекс выходит за пределы массива." << endl;
                                cout << "\tБудьте внимательны !!!" << endl;
                            }

                        } while (index2 < 0 || index2 >= array2D_int.size);
                        do
                        {
                            cout << endl
                                 << "\tВведите значение которое хотите вставить в позицию:";
                            value1 = getValueInt();

                        } while (value1 < -10 || value1 > 10);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tВ позицию элемента были внесены изменения: [" << index1 << "][" << index2 << "] = " << value1 << endl
                             << endl;

                        array2D_int.inputElement2D(index1, index2, value1);
                        array2D_int.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        array2D_double.outputArray2D();
                        cout << endl;
                        dot(26);
                        cout << endl;
                        do
                        {
                            cout << endl
                                 << "\tВведите [позицию 1][] элемента в которую хотите внести изменения:";
                            index1 = getValueInt();

                            if (index1 < 0 || index1 > array2D_double.size)
                            {
                                cout << "\tИндекс выходит за пределы массива." << endl;
                                cout << "\tБудьте внимательны !!!" << endl;
                            }

                        } while (index1 < 0 || index1 >= array2D_double.size);
                        do
                        {
                            cout << endl
                                 << "\tВведите [][позицию 2] элемента в которую хотите внести изменения:";
                            index2 = getValueInt();

                            if (index2 < 0 || index2 > array2D_double.size)
                            {
                                cout << "\tИндекс выходит за пределы массива." << endl;
                                cout << "\tБудьте внимательны !!!" << endl;
                            }

                        } while (index2 < 0 || index2 >= array2D_double.size);

                        do
                        {
                            cout << endl
                                 << "\tВведите значение которое хотите вставить в позицию:";
                            value2 = getValueDouble();

                        } while (value2 < -10 || value2 > 10);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tВ позицию элемента были внесены изменения: [" << index1 << "][" << index2 << "] = " << value2 << endl
                             << endl;

                        array2D_double.inputElement2D(index1, index2, value2);
                        array2D_double.outputArray2D();
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

        case 8:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 8 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (array_INT || array_DOUBLE || array2D_INT || array2D_DOUBLE)
            {
                if (operate)
                {
                    if (array_INT)
                    {
                        do
                        {
                            cout << "\tВведите числовое значения для поиска в элементах массива (-10...10):" << endl;
                            value1 = getValueInt();

                        } while (value1 < -10 || value1 > 10);
                        array_int.sortArray();

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        index1 = array_int.binarySearch(value1);
                        if (index1 != -1)
                        {
                            cout << "\tЧисловое значение " << value1 << " найдено в массиве." << endl;
                            cout << "\tЭлемент находиться на позиции: " << index1 << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "\tЧисловое значение " << value1 << " в массиве не найдено." << endl
                                 << endl;
                        }
                        array_int.outputArray();
                    }
                    if (array_DOUBLE)
                    {
                        do
                        {
                            cout << "\tВведите числовое значения для поиска в элементах массива (-10...10):" << endl;
                            value2 = getValueDouble();

                        } while (value2 < -10 || value2 > 10);
                        array_double.sortArray();

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        index1 = array_double.binarySearch(value2);
                        if (index1 != -1)
                        {
                            cout << "\tЧисловое значение " << value2 << " найдено в массиве." << endl;
                            cout << "\tЭлемент находиться на позиции: " << index1 << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "\tЧисловое значение " << value2 << " в массиве не найдено." << endl
                                 << endl;
                        }
                        array_double.outputArray();
                    }
                    if (array2D_INT)
                    {
                        do
                        {
                            cout << "\tВведите числовое значения для поиска в элементах массива (-10...10):" << endl;
                            value1 = getValueInt();

                        } while (value1 < -10 || value1 > 10);
                        array2D_int.sortArray2D();

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        index1 = array2D_int.Search2D(value1);
                        if (index1 == 1)
                        {
                            cout << "\tЧисловое значение " << value1 << " найдено в массиве." << endl;
                            cout << "\tЭлемент находиться на позиции:" << endl;
                            array2D_int.binarySearch2D(value1);
                        }
                        else
                        {
                            cout << "\tЧисловое значение " << value1 << " в массиве не найдено." << endl
                                 << endl;
                        }
                        array2D_int.outputArray2D();
                    }
                    if (array2D_DOUBLE)
                    {
                        do
                        {
                            cout << "\tВведите числовое значения для поиска в элементах массива (-10...10):" << endl;
                            value2 = getValueDouble();

                        } while (value2 < -10 || value2 > 10);
                        array2D_double.sortArray2D();

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        index1 = array2D_double.Search2D(value2);
                        if (index1 == 1)
                        {
                            cout << "\tЧисловое значение " << value2 << " найдено в массиве." << endl;
                            cout << "\tЭлемент находиться на позиции:" << endl;
                            array2D_double.binarySearch2D(value2);
                        }
                        else
                        {
                            cout << "\tЧисловое значение " << value2 << " в массиве не найдено." << endl
                                 << endl;
                        }
                        array2D_double.outputArray2D();
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

        case 9:
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

