// Задача №1
// Создайте класс Array .
// Класс Array - это класс динамического массива.
// Размер массива может быть передан в качестве параметра или задан с помощью вызова функции-члена.
// Класс должен позволять заполнять массив значениями, отображать содержимое массива, изменять
// размер массива, сортировать массив, записывать массив в файл. Класс должен содержать
// набор конструкторов (конструктор копирования по необходимости), деструктор.
// Определить порядковые номера первого отрицательного и последнего положительного элементов (если таковые имеются).
// Значение элементов и их порядковые номера вывести или выдать соответствующее сообщение при их отсутствии.
// После записи элементов массива в файл информация должна быть сохранена, и при последующем выходе
// из программы и новой её загрузке должно произойти корректное считывание информации
// из файла и дальнейшее её использование.
// Работу программы построить в виде меню.

#include <windows.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>

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

class Array
{

public:
    Array();
    Array(int);
    Array(const Array &);
    ~Array();
    void setSize(int);
    void initializeManually();
    void initializeAutomatically();
    void show();
    void sort();
    void reinitialize(int resize, int select);
    int save();
    int load();
    int getSize();
    int firstMinIndex();
    int lastMaxIndex();
    double firstMinElement();
    double lastMaxElement();

private:
    int size;
    double *array;
};

//-----------------------------------------------------------------------------
Array::Array()
{
    size = 0;
    array = nullptr;
}

Array::Array(int size)
{
    array = new double[size];
    this->size = size;
}

Array::Array(const Array &obj)
{
    size = obj.size;
    array = new double[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = obj.array[i];
    }
}

Array::~Array()
{
    if (array)
    {
        delete[] array;
        array = nullptr;
    }
}

void Array::setSize(int size)
{
    this->size = size;
}

void Array::initializeManually()
{
    if (array)
        delete[] array;

    array = new double[size];

    cout << "\tЗаполнение массива числами с клавиатуры:" << endl;
    for (int i = 0; i < size; i++)
    {
        do
        {
            cout << "\tА[" << i << "] = ";
            cin >> array[i];
            eatline();
        } while (array[i] <= -100 || array[i] >= 100);
    }
}

void Array::initializeAutomatically()
{
    if (array)
        delete[] array;

    array = new double[size];

    srand((unsigned int)time(0));
    cout << "\tЗаполнение массива случайными числами:" << endl
         << endl;
    for (int i = 0; i < size; i++)
    {
        //заполнение массива случайными числами с масштабированием от -10.0 до 10.0
        array[i] = (rand() % 21 - 10) / float((rand() % 10 + 1));
        if (i < 10)
        {
            cout << "\tА[ " << i << "] = ";
            cout << setw(6) << setprecision(2) << array[i] << endl;
        }
        else
        {
            cout << "\tА[" << i << "] = ";
            cout << setw(6) << setprecision(2) << array[i] << endl;
        }
    }
}

void Array::show()
{
    cout << "\tЭлементы массива:" << endl
         << endl;
    for (int i = 0; i < size; i++)
    {
        if (i < 10)
        {
            cout << "\tА[ " << i << "] = ";
            cout << setw(6) << setprecision(2) << array[i] << endl;
        }
        else
        {
            cout << "\tА[" << i << "] = ";
            cout << setw(6) << setprecision(2) << array[i] << endl;
        }
    }
}

void Array::sort()
{
    double temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if (array[j - 1] > array[j])
            {
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
    }
    cout << endl
         << "\tМассив отсортирован по возрастанию." << endl;
    cout << endl
         << "\tПросмотр массива 2 пункт меню." << endl;
}

// Изменение размера массива
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
    else if (resize > size && select == 1)
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

        cout << "\tЗаполнение массива числами с клавиатуры:" << endl;
        for (int i = size; i < resize; i++)
        {
            do
            {
                cout << "\tА[" << i << "] = ";
                cin >> array_new[i];
                eatline();
            } while (array[i] <= -100 || array[i] >= 100);
        }

        delete[] array;
        array = array_new;
        size = resize;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Определение порядковых номеров
// первого отрицательного и последнего положительного элемента
int Array::firstMinIndex()
{
    int j = 0;
    bool find = false;
    for (int i = 0; i < size; i++)
    {
        if (array[i] < 0)
        {
            j = i;
            find = true;
            break;
        }
    }
    if (find)
        return j;
    else
        return -1;
}
int Array::lastMaxIndex()
{
    int j = 0;
    bool find = false;
    for (int i = size - 1; i > 0; i--)
    {
        if (array[i] > 0)
        {
            j = i;
            find = true;
            break;
        }
    }
    if (find)
        return j;
    else
        return -1;
}
double
Array::firstMinElement()
{
    double min = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] < 0)
        {
            min = array[i];
            break;
        }
    }
    return min;
}
double
Array::lastMaxElement()
{
    double max = array[0];
    for (int i = size - 1; i > 0; i--)
    {
        if (array[i] > 0)
        {
            max = array[i];
            break;
        }
    }
    return max;
}
///////////////////////////////////////////////////////////////////////////////

int Array::save()
{
    ofstream file("Array.txt", ios::out | ios::binary | ios::trunc);
    if (file)
    {
        file.write((const char *)&size, sizeof(int));
        file.write((const char *)array, (streamsize)size * sizeof(double));
        file.close();

        return 1;
    }

    return -1;
}

int Array::load()
{
    ifstream file("Array.txt", ios::in | ios::binary);
    if (file)
    {
        file.read((char *)&size, sizeof(int));
        if (array)
            delete[] array;

        array = new double[size];

        file.read((char *)array, (streamsize)size * sizeof(double));
        file.close();

        return 1;
    }

    return -1;
}

int Array::getSize()
{
    return size;
}
//-----------------------------------------------------------------------------

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Array array;

    int menu;
    bool install = false;
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
        cout << "\t\t   ***| Практическая работа №4  Задача №1 |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t    Выберите ПУНКТ меню для работы:" << endl;
        cout << "\t 1) Инициализация массива." << endl;
        cout << "\t 2) Вывод элементов массива на экран." << endl;
        cout << "\t 3) Редактирование массива (изменение размера массива)." << endl;
        cout << "\t 4) Сортировка массива." << endl;
        cout << "\t 5) Поиск номеров первого(min) и последнего(max) элементов." << endl;
        cout << "\t 6) Сохранить массив в  файл." << endl;
        cout << "\t 7) Загрузить массив из файла." << endl;
        cout << "\t 8)  | ВыхоД |";

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
            if (install)
            {
                cout << endl
                     << "\tМассив инсталирован." << endl;
                cout << endl
                     << "\tИзменение размера массива 3 пункт меню." << endl;
            }
            else
            {
                int ask;
                int size;
                do
                {
                    cout << endl
                         << "\tВведите количество элементов массива (3 - 20):";
                    size = valueTypeI();
                } while (size < 3 || size > 20);
                array.setSize(size);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                cout << "\t   Заполнить массив случайными числами?" << endl;
                cout << "\t1. ДА." << endl;
                cout << "\t2. НЕТ.";
                do
                {
                    ask = 0;
                    ask = valueTypeI();

                    if (ask != 1 && ask != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Ответ = 2 -нет).";
                        cout << endl
                             << "\tПожалуйста правильно ответьте на вопрос.";
                    }

                } while (ask != 1 && ask != 2);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (ask == 1)
                {
                    array.initializeAutomatically();
                }
                if (ask == 2)
                {
                    array.initializeManually();
                }

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                cout << "\tМассив создан." << endl;

                install = true;
            }

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

            if (install)
            {
                array.show();
            }
            else
                cout << "\tМассив не инсталлирован (1 или 7 пункт меню)." << endl;

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

            if (install)
            {
                int ask;
                int resize;
                int size;
                int select;

                cout << "\t   Будете редактировать размер массива?" << endl;
                cout << "\t1. ДА." << endl;
                cout << "\t2. НЕТ.";
                do
                {
                    ask = 0;
                    ask = valueTypeI();

                    if (ask != 1 && ask != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Ответ = 2 -нет).";
                        cout << endl
                             << "\tПожалуйста правильно ответьте на вопрос.";
                    }

                } while (ask != 1 && ask != 2);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (ask == 1)
                {
                    cout << "\tВведите новый размер включая существующий массив (3 - 40):";
                    do
                    {
                        resize = valueTypeI();

                    } while (resize < 3 || resize > 40);

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
                        select = valueTypeI();

                        if (select != 1 && select != 2 && select != 3)
                        {
                            cout << endl
                                 << "\tНекорректный ввод (Действие = 3 -отмена).";
                            cout << endl
                                 << "\tПожалуйста сделайте выбор.";
                        }
                    } while (select != 1 && select != 2 && select != 3);

                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (select == 1)
                    {
                        size = array.getSize();
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
                        size = array.getSize();
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
                                 << "\tВ массив успешно добавлены элементы." << endl;
                            size = resize;
                        }
                    }
                }
                if (ask == 2)
                {
                    break;
                }
            }
            else
                cout << "\tМассив не инсталлирован (1 или 7 пункт меню)." << endl;

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

            if (install)
            {
                array.sort();
            }
            else
                cout << "\tМассив не инсталлирован (1 или 7 пункт меню)." << endl;

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
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (install)
            {
                if (array.firstMinIndex() == -1)
                {
                    cout << "\tОтрицательные (-) элементы в массиве отсутствуют." << endl;
                }
                else
                {
                    cout << "\tПервый    отрицательный (-) элемент массива:" << endl;
                    cout << "\t[" << array.firstMinIndex() << "] = " << array.firstMinElement() << endl;
                }

                cout << endl
                     << "\t";
                dash(60);
                cout << endl
                     << endl;

                if (array.lastMaxIndex() == -1)
                {
                    cout << "\tПоложительные (+) элементы в массиве отсутствуют." << endl
                         << endl;
                }
                else
                {
                    cout << "\tПоследний положительный (+) элемент массива:" << endl;
                    cout << "\t[" << array.lastMaxIndex() << "] = " << array.lastMaxElement() << endl;
                }
            }
            else
                cout << "\tМассив не инсталлирован (1 или 7 пункт меню)." << endl;

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

        case 6:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (install)
            {
                int ask;

                cout << "\t   При имеющемся файле (Аrray.txt), файл будет перезаписан." << endl;
                cout << "\t   >>> COХРАНИТЬ <<< ?" << endl;
                cout << "\t1. ДА." << endl;
                cout << "\t2. НЕТ.";
                do
                {
                    ask = 0;
                    ask = valueTypeI();

                    if (ask != 1 && ask != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Ответ = 2 -нет).";
                        cout << endl
                             << "\tПожалуйста правильно ответьте на вопрос.";
                    }

                } while (ask != 1 && ask != 2);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (ask == 1)
                {
                    if (array.save() == 1)
                        cout << "\tМассив успешно сохранен в файл." << endl;
                    else
                        cout << "\tНе удается открыть файл для записи." << endl;
                }
                if (ask == 2)
                {
                    break;
                }
            }
            else
                cout << "\tМассив не инсталлирован (1 или 7 пункт меню)." << endl;

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

        case 7:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 7 пункт меню |_______" << endl
                 << endl
                 << endl;

            int ask;

            if (install)
            {
                cout << "\t   Имеющийся массив будет потерян. (если не был сохранен)" << endl;
                cout << "\t   >>> ЗАГРУЗИТЬ <<< ? (будет загружен массив из файла)" << endl;
                cout << "\t1. ДА." << endl;
                cout << "\t2. НЕТ.";
                do
                {
                    ask = 0;
                    ask = valueTypeI();

                    if (ask != 1 && ask != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Ответ = 2 -нет).";
                        cout << endl
                             << "\tПожалуйста правильно ответьте на вопрос.";
                    }

                } while (ask != 1 && ask != 2);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (ask == 1)
                {
                    if (array.load() == 1)
                    {
                        cout << "\tФайл считан успешно." << endl;
                        install = true;
                    }
                    else
                        cout << "\tНе удается открыть файл для чтения." << endl;
                }
                if (ask == 2)
                {
                    break;
                }
            }
            else
            {
                cout << "\t   >>> ЗАГРУЗИТЬ <<< ? (будет загружен массив из файла)" << endl;
                cout << "\t1. ДА." << endl;
                cout << "\t2. НЕТ.";
                do
                {
                    ask = 0;
                    ask = valueTypeI();

                    if (ask != 1 && ask != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Ответ = 2 -нет).";
                        cout << endl
                             << "\tПожалуйста правильно ответьте на вопрос.";
                    }

                } while (ask != 1 && ask != 2);

                cout << endl;
                dot(26);
                cout << endl
                     << endl;

                if (ask == 1)
                {
                    if (array.load() == 1)
                    {
                        cout << "\tФайл считан успешно." << endl;
                        install = true;
                    }
                    else
                        cout << "\tНе удается открыть файл для чтения." << endl;
                }
                if (ask == 2)
                {
                    break;
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
            cin.get();
        }
        break;

        case 8:
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

    cout << endl
         << "_ПРОГРАММА ЗАВЕРШЕНА";
    cout << endl
         << "_____Hажмите-<ENTER>";
    cin.get();

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
// Задача №2
// Разработать класс String, который в дальнейшем будет использоваться для работы со строками.
// Класс должен содержать:
// - Конструктор по умолчанию, позволяющий создать строку длиной 80 символов;
// - Конструктор, позволяющий создавать строку произвольного размера;
// - Конструктор, который создаёт строку и инициализирует её строкой, полученной от
//   пользователя.(использовать только тот конструктор, который необходим)
// Необходимо создать деструктор.

// Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.
// Также нужно реализовать статическую функцию-член, которая будет возвращать количество созданных объектов строк.
// Ввести текст произвольного содержания в память ПЭВМ. Вывести на экран. Записать текст в файл.
// После записи текста в файл информация должна быть сохранена,
// и при последующем выходе из программы и новой её загрузке должно произойти
// корректное считывание информации из файла и дальнейшее её использование.
// Вывести текст из файла на экран. Из текста удалить все слова заданной длины, начинающиеся с согласных букв.
// Результат вывести на экран. Работу программы построить в виде меню. Достаточно рассмотреть англоязычный вариант.

#include <windows.h>
#include <iostream>
#include <fstream>
#include <list>

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

class String
{

public:
    String(const String &);
    String(int length = 80);
    String(char *);
    ~String();
    int getLength();
    static void setCount(int);
    static int getCount();
    void seach(int);

    friend ostream &operator<<(ostream &, String);
    friend istream &operator>>(istream &, String &);

private:
    char *m_string;
    int length;
    static int count;
};

int String::count = 0;

String::String(const String &obj)
{
    length = obj.length;
    m_string = new char[length + 1];
    strcpy(m_string, obj.m_string);
    count++;
}

String::String(int length)
{
    count++;
    m_string = new char[length + 1];
    this->length = length;
}

String::String(char *str)
{
    count++;
    length = strlen(str);
    m_string = new (nothrow) char[length + 1];
    strcpy(m_string, str);
}

String::~String()
{
    if (m_string)
        delete[] m_string;

    count--;
}

int String::getLength()
{
    return strlen(m_string);
}
void String::setCount(int n)
{
    count = n;
}
int String::getCount()
{
    return count;
}

void String::seach(int n)
{
    char *temp = m_string;
    int number = 0;
    int i = 0;

    while (temp[i] != '\0')
    {
        while (temp[i] == ' ' || temp[i] == ',' || temp[i] == '.' ||
               temp[i] == '!' || temp[i] == '?' && temp[i] != '\0')
            i++;

        if (temp[i] == 'A' || temp[i] == 'a' || temp[i] == 'E' ||
            temp[i] == 'e' || temp[i] == 'I' || temp[i] == 'i' ||
            temp[i] == 'O' || temp[i] == 'o' || temp[i] == 'U' ||
            temp[i] == 'u' || temp[i] == 'Y' || temp[i] == 'y')
        {
            while (temp[i] != ' ' && temp[i] != ',' && temp[i] != '.' &&
                   temp[i] != '!' && temp[i] != '?' && temp[i] != '\0')
                i++;
        }
        else
        {
            while (temp[i] != ' ' && temp[i] != ',' && temp[i] != '.' &&
                   temp[i] != '!' && temp[i] != '?' && temp[i] != '\0')
            {
                number++;
                i++;
            }
            if (number == n)
            {
                i -= number;
                for (int j = 0; j < number; j++)
                    for (int k = i; k < length; k++)
                        temp[k] = temp[k + 1];
            }
            number = 0;
        }
        i++;
    }
}

void save(list<String *>);
int load(list<String *> &);

ostream &operator<<(ostream &out, const String obj)
{
    out << obj.m_string;
    return out;
}
istream &operator>>(istream &in, String &obj)
{
    in.getline(obj.m_string, obj.length);
    return in;
}

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    list<String *> list;

    int menu;
    bool install = false;
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
        cout << "\t\t   ***| Практическая работа №4  Задача №2 |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t    Выберите ПУНКТ меню для работы:" << endl;
        cout << "\t 1) Ввод строк." << endl;
        cout << "\t 2) Вывод всех имеющихся строк с указанием из количества." << endl;
        cout << "\t 3) Удаление из текста слов заданной длины," << endl;
        cout << "\t    начинающихся с согласной буквы." << endl;
        cout << "\t 4) Сохранение строк в  файл." << endl;
        cout << "\t 5) Считывание строк из файла." << endl;
        cout << "\t 6)  | ВыхоД |";

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

            cout << "\tВведите строки (для прекращенния ввода в пустой строке нажмите \"ENTER\")" << endl
                 << endl;
            do
            {
                String *str = new String();
                cin >> *str;
                if (!str->getLength())
                {
                    delete str;
                    break;
                }
                list.push_back(str);
            } while (true);
        }
        break;

        case 2:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl;

            cout << "\tВывод имеющихся строк:" << endl
                 << endl;
            auto iter = list.begin();
            for (; iter != list.end(); iter++)
                cout << **iter << endl;

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            cout << "\tКоличество строк: " << String::getCount() << endl
                 << endl;

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
            int length_string;

            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl;

            cout << "Введите длину слова: ";
            cin >> length_string;
            eatline();

            cout << "Вывод строк до обработки:" << endl
                 << endl;
            auto iter = list.begin();
            for (; iter != list.end(); iter++)
                cout << **iter << endl;

            cout << endl;
            dot(26);
            cout << endl
                 << endl;

            cout << "Вывод строк после обработки:" << endl
                 << endl;
            iter = list.begin();
            for (; iter != list.end(); iter++)
            {
                (*iter)->seach(length_string);
                cout << **iter << endl;
            }

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

            save(list);

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
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
                 << endl;

            String::setCount(load(list));

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

        case 6:
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

    // out << endl << "_ПРОГРАММА ЗАВЕРШЕНА";
    // cout << endl << "_____Hажмите-<ENTER>";
    // cin.get();

    SetConsoleCP(i1);
    SetConsoleOutputCP(i1);

    return 0;
}

void save(list<String *> list)
{
    int count_string = list.size();
    ofstream file("Strings.txt", ios::out | ios::binary | ios::trunc);
    file.write((const char *)&count_string, sizeof(int));
    auto iter = list.begin();
    for (; iter != list.end(); iter++)
        file << **iter << endl;
    file.close();
    cout << "\tСтроки успешно сохранены в файл." << endl;
}
int load(list<String *> &list)
{
    int count_string;
    list.clear();
    ifstream file("Strings.txt", ios::in | ios::binary);
    file.read((char *)&count_string, sizeof(int));
    for (int i = 0; i < count_string; i++)
    {
        String *str = new String(80);
        file >> *str;
        list.push_back(str);
    }
    cout << "\tФайл считан успешно." << endl;
    file.close();
    return count_string;
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
*/
