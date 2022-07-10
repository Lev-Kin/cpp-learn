// 1. Создайте класс Array .
// Класс Array - это класс динамического массива.
// Размер массива может быть передан в качестве параметра или задан с помощью вызова функции-члена.
// Класс должен позволять заполнять массив значениями, отображать содержимое массива, изменять
// размер массива, сортировать массив, определять минимальное и максимальное значение.
// Класс должен содержать набор конструкторов (конструктор копирования обязателен), деструктор.
// В созданный класс Array добавьте перегрузку [], (), преобразования типов к int и char*:
// [ ] – возвращает элемент по указанному индексу;
// ( ) – увеличивает все элементы массива на указанную величину.
// Преобразование к int возвращает сумму элементов массива.
// Преобразование к char* возвращает значения элементов массива в виде строки.

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
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
    char *array_ch;
    double *array;
    string str;
    Array()
    {
        size = 0;
        array = new double[size];
        size = 0;
        array_ch = new char[size];
    }
    Array(const Array &obj)
    {
        size = obj.size;
        array = new double[size];
        for (int i = 0; i < size; i++)
        {
            array[i] = obj.array[i];
        }
        array_ch = new char[size];
        for (int i = 0; i < size; i++)
        {
            array_ch[i] = obj.array_ch[i];
        }
    }
    ~Array()
    {
        delete[] array;
        array = nullptr;
        delete[] array_ch;
        array_ch = nullptr;
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
    double operator[](int i);
    void operator()(int size, double add_value);
    string convertArrayToString();
    int convertStringToArray();
};

double Array::operator[](int i)
{
    return array[i];
}

void Array::operator()(int size, double add_value)
{
    double *array_new = new double[size];
    for (int i = 0; i < size; i++)
    {
        array_new[i] = array[i] + add_value;
    }
    delete[] array;
    array = array_new;
}

string Array::convertArrayToString()
{
    str = "";
    for (int i = 0; i < size; i++)
    {
        array_ch[i] = (int)array[i] + '0';
    }
    array_ch[size] = '\0';

    for (int i = 0; i < size; i++)
    {
        str = str + array_ch[i];
        str += "| ";
    }

    return str;
}

int Array::convertStringToArray()
{
    // получаем длину строки str
    int str_length = str.length();

    // создаем массив с размером в виде строки
    int *array_tmp = new int[str_length];
    int sum = 0;
    int j = 0;
    int i;

    // обход строки
    for (i = 0; str[i] != '\0'; i++)
    {

        // разделитель
        if (str[i] == '|')
            continue;
        // увеличиваем j, чтобы указывать на следующее
        // расположение массива
        if (str[i] == ' ')
            j++;
        else
        {
            // преобразовываем в int
            array_tmp[j] = (str[i] - 48);
        }
    }

    cout << "\tarray[" << j - 1 << "] = ";
    for (i = 0; i <= j - 1; i++)
    {
        cout << array_tmp[i] << "| ";
        sum += array_tmp[i]; // сумма массива
    }

    cout << endl
         << "\tСумма массива = " << sum << endl;

    delete[] array_tmp;
    return sum;
}

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

    int k; // искомый индекс пользователя
    int size;
    int resize;
    double add_value; // добавить число во все элементы массива

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
        cout << "\t6. Возвращение элемента по указанному индексу." << endl;
        cout << "\t7. Увеличение всех элементов массива на указанную величину." << endl;
        cout << "\t8. Преобразование типов." << endl;
        cout << "\t9.   | ВыхоД |";
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

            if (option == 3)
                break;

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

                if (option == 3)
                    break;

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
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Показать элемент массива по указаному индексу." << endl;
                cout << "\t2.   | Отмена |"; // оставить как есть

                do // защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Действие = 2 -отмена).";
                        cout << endl
                             << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2);

                if (option == 2)
                    break;

                cout << endl;
                dot(26);
                cout << endl;

                if (option == 1)
                {
                    do
                    {
                        cout << endl
                             << "\tВведите индекс массива который показать (0 - " << size - 1 << "):";
                        k = 0;
                        k = getValueInt();
                        if (k < 0 || k > size - 1)
                        {
                            cout << endl
                                 << "\tИндекс выходит за пределы массива (0 - " << size - 1 << "):" << endl;
                        }

                    } while (k < 0 || k > size - 1);

                    for (int i = 0; i < size; i++)
                    {
                        if (i == k)
                        {
                            cout << endl
                                 << "\tЗначение искомого индекса в массиве следующее:" << endl;
                            cout << "\t[" << i << "] = " << setprecision(2) << array[i] << endl;
                            // возвращаем с помощью перегрузки и отображаем
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

        case 7:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 7 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Увеличить все элементы массива." << endl;
                cout << "\t2.   | Отмена |"; // оставить как есть

                do // защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Действие = 2 -отмена).";
                        cout << endl
                             << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2);

                if (option == 2)
                    break;

                cout << endl;
                dot(26);
                cout << endl;

                if (option == 1)
                {
                    do
                    {
                        cout << endl
                             << "\tВведите значение на которое хотите увеличить (-10 - 10):";
                        add_value = 0;
                        add_value = getValueDouble();

                    } while (add_value < -10 || add_value > 10);
                    array(size, add_value);

                    cout << endl
                         << "\tВсе элементы массива были увеличены на " << add_value << "." << endl;
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
            break;

        case 8:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 8 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Выполнить преобразование типов данных." << endl;
                cout << "\t2.   | Отмена |"; // оставить как есть

                do // защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Действие = 2 -отмена).";
                        cout << endl
                             << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2);

                if (option == 2)
                    break;

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (option == 1)
                {
                    cout << "\tПреобразование к char* возвращает значения элементов массива" << endl;
                    cout << "\tв виде строки:" << endl;
                    cout << "\t[str] = " << array.convertArrayToString() << endl
                         << endl;
                    cout << "\tПреобразование к int возвращает сумму элементов массива:" << endl;
                    array.convertStringToArray();
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


/*
// 2. Реализовать класс var - ≪Универсальная переменная≫.
// Объекты экземпляры этого класса способны хранить в себе
// значения следующих типов: int, double, String_ (строка – уже готовый класс).
// Например:
// void main()
// {
//  var a = 15;
//  var b = “Hello”;
//  var c = 7.8;
//  var d = “50”;
//  b = a + d;
//  b.Show(); // Выведет 65
//  if (a == b)
//   cout << “Equal\n”;
//  else
//   cout << “Not Equal\n”;
// }
// Для класса var необходимо:
// - перегрузить арифметические операторы: -,+,  *, /, +=, -=, *=, /=
// - операторы сравнения: <, >, <=, >=, ==, !=
// Вся перегрузка осуществляется как функции-члены класса var.
// В переменной типа var в любой момент времени может храниться
//  только одно значение (или int, или double, или String).
// При перегрузке операторов учитывать следующее: если в операции типы
// значений двух операндов типа var разные, то необходимо приводить (конвертировать)
// значение из второго операнда к типу значения первого операнда и только
// после этого выполнять операцию. При этом значение (и тип)
// второго операнда в самом объекте var не меняется.
// Например:
// var a = 10, b = “120”, c;
// c = a + b;
// c.Show(); //Выведет 130
// c = b + a;
// c.Show(); //Выведет “12010”
// Для типа Строка операция * должна возвращать новую строку,
// состоящую только из символов первой строки, которые есть во второй строке, например:
// var a = “Microsoft”, b = “Windows”, c;
// c = a * b;
// c.Show(); //Выведет “ioso”
// Для типа Строка операция / должна возвращать новую строку,
// состоящую из символов первой строки, которых нет во второй строке, например:
// var a = “Microsoft”, b = “Windows”, c;
// c = a / b;
// c.Show(); //Выведет “Mcrft”
// Аналогично для Строки *=  и /=.
// Добавить в класс var преобразования к типам: int, double, char*.

#include <iostream>
#include <windows.h>
using namespace std;
class Var
{
private:
    int num;
    double real;
    char *str;

public:
    Var()
    {
        num = NULL;
        real = NULL;
        str = NULL;
    }
    Var(int temp)
    {
        num = temp;
        real = NULL;
        str = NULL;
    }
    Var(double temp)
    {
        num = NULL;
        real = temp;
        str = NULL;
    }
    Var(char *temp)
    {
        num = NULL;
        real = NULL;
        str = new char[strlen(temp) + 1];
        strcpy(str, temp);
    }
    void Show()
    {
        if (num != NULL)
        {
            cout << num << endl;
        }
        if (real != NULL)
        {
            cout << real << endl;
        }
        if (str != NULL)
        {
            cout << str << endl;
        }
    }

    const Var operator+(Var &temp)
    {
        //Если правая переменая типа INT
        if (temp.num)
        {
            if (num != NULL)
            {
                real = NULL;
                str = NULL;
                return num + temp.num;
            }
            if (real != NULL)
            {
                num = NULL;
                str = NULL;
                return real + (double)temp.num;
            }
            if (str != NULL)
            {
                num = NULL;
                real = NULL;
                char t[10];
                itoa(temp.num, t, 10);
                char *tmp = new char[strlen(str) + strlen(t) + 1];
                strcpy(tmp, str);
                strcat(tmp, t);
                cout << tmp << endl;
                return tmp;
            }
        }
        //Если правая переменая типа DOUBLE
        if (temp.real)
        {
            if (real != NULL)
            {
                num = NULL;
                str = NULL;
                return real + temp.real;
            }
            if (num != NULL)
            {
                real = NULL;
                str = NULL;
                return num + (int)temp.real;
            }
            if (str != NULL)
            {
                real = NULL;
                num = NULL;
                char t[10];
                sprintf(t, "%.2f", temp.real);
                char *tmp = new char[strlen(str) + strlen(t)];
                strcpy(tmp, str);
                strcat(tmp, t);
                return tmp;
            }
        }
        //Если правая переменая типа char*
        if (temp.str)
        {
            if (real != NULL)
            {
                num = NULL;
                str = NULL;
                return real + atof(temp.str);
            }
            if (num != NULL)
            {
                real = NULL;
                str = NULL;
                return num + atoi(temp.str);
            }
            if (str != NULL)
            {
                real = NULL;
                num = NULL;
                char *tmp = new char[strlen(str) + strlen(temp.str) + 1];
                strcpy(tmp, str);
                return tmp;
            }
        }
    }

    Var(const Var &obj)
    {
        str = new char[strlen(obj.str) + 1];
        strcpy(str, obj.str);
    }

    ~Var()
    {
        delete[] str;
    }
    const Var operator=(const Var &temp) // перегрузка оператора
    {
        if (temp.num)
        {
            num = temp.num;
            real = NULL;
            str = NULL;
            return num;
        }
        else if (temp.real)
        {
            num = NULL;
            str = NULL;
            real = temp.real;
            return real;
        }
        else if (temp.str)
        {
            real = NULL;
            num = NULL;
            str = new char[strlen(temp.str) + 1];
            strcpy(str, temp.str);
            return str;
        }
        else
            exit(0);
    }
    const Var operator*(const Var &str_fun)
    {
        Var temp;
        char buff[80];
        unsigned int pos1 = 0, pos2 = 0, pos_povt1 = 0, pos_povt2 = 0;
        char simvol_povt1[80];
        char simvol_povt2[80];

        simvol_povt1[pos_povt1++] = str[pos1];
        simvol_povt1[pos_povt1] = '\0';

        while (pos1 < strlen(str))
        {
            if (!strchr(simvol_povt1, str[pos1]))
            {
                simvol_povt1[pos_povt1++] = str[pos1];
                simvol_povt1[pos_povt1] = '\0';
            }
            pos1++;
        }

        pos1 = 0;
        simvol_povt2[pos_povt2++] = str_fun.str[pos1];
        simvol_povt2[pos_povt2] = '\0';

        while (pos1 < strlen(str_fun.str))
        {
            if (!strchr(simvol_povt2, str_fun.str[pos1]))
            {
                simvol_povt2[pos_povt2++] = str_fun.str[pos1];
                simvol_povt2[pos_povt2] = '\0';
            }
            pos1++;
        }
        // cout << simvol_povt1 << "\n";
        // cout << simvol_povt2 << "\n";
        pos1 = 0;
        while (pos1 < strlen(simvol_povt1))
        {
            if (strchr(simvol_povt2, simvol_povt1[pos1]))
            {
                buff[pos2] = simvol_povt1[pos1];
                pos2++;
            }
            pos1++;
        }
        buff[pos2] = '\0';
        temp = buff;
        return temp;
    }
};

void main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Var a = 15;
    a.Show();
    Var b = (char *)"Hello";
    b.Show();
    Var c = 7.8;
    c.Show();
    Var d = (char *)"50";
    d.Show();
    cout << "Привет" << endl;
    b = a + d;
    b.Show();
    cout << "Привет_1" << endl;
    b = b + a;
    b.Show();
    cout << "Привет_2" << endl;
    b = b + c;
    b.Show();
    cout << "Привет_3" << endl;
    a = 10;
    a.Show();
    b = (char *)"120";
    b.Show();
    a.Show();
    c = a + b;
    c.Show(); //Выведет 130
    b.Show();
    a.Show();
    c = b + a;
    c.Show(); //Выведет "12010"
}
*/
