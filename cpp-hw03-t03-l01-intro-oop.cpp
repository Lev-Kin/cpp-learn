// Задание 1.
// Разработать класс String, который в дальнейшем будет использоваться для работы со строками.
// Класс должен содержать:
// - Конструктор по умолчанию, позволяющий создать строку длиной 80 символов;
// - Конструктор, позволяющий создавать строку произвольного размера;
// - Конструктор, который создаёт строку и инициализирует её строкой, полученной от
//   пользователя.
// Необходимо создать деструктор.
// Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.
// Также нужно реализовать статическую функцию-член,
// которая будет возвращать количество созданных объектов строк.

#include <iostream>
#include <string.h>
#include <windows.h>

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

class String
{
private:
    char *str;
    int len;
    static int numObjects;

public:
    String() // конструктор без параметров
    {
        len = 81; //длина строки
        str = new char[len];
        if (str)
            str[0] = '\0'; // защита буфера
    }
    String(int size) // конструктор с одним параметром
    {
        len = size + 1;
        str = new char[len];
        if (str)
            str[0] = '\0';
    }
    String(const char *string) // получение строки от пользователя
    {
        len = strlen(string);
        str = new char[len + 1];
        if (str)
        {
            strcpy(str, string);
            numObjects++; // суммируем количество строк отдельно созданных
        }
    }
    ~String() //деструктор
    {
        delete[] str; //освобождение памяти
    }

    void inputStr()
    {
        // У потока ввода есть буфер чтения, в котором он хранит символы.
        // Мы обращаемся к нему, вызывая функцию rdbuf().
        // Через функцию in_avail() узнаем количество символов этого буфера.
        // Далее игнорируем кол-во символов ignore(). (опускаем)
        cin.ignore(cin.rdbuf()->in_avail());
        // void ios::clear(iostate state = goodbit);
        // функция clear() «очищает» состояние потока, делая его вновь работоспособным.
        cin.clear();
        cin.getline(str, len);
        numObjects++; // суммируем количество строк с потока
    }

    void outputStr()
    {
        cout << str << endl;
    }

    static void showObjectsNumbr()
    {
        cout << numObjects;
    }
};

int String::numObjects = 0; // подсчет строк

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
    cout << "\t     ***| Задание 3. Лекция 1. Разработка класса String |***" << endl
         << endl
         << endl;

    int size = 0;
    char string[80];

    String str1;
    cout << "\tВведите первую строку:" << endl;
    cout << " [str]  ";
    str1.inputStr();

    cout << endl;
    dot(26);
    cout << endl
         << endl;

    cout << "\tВведите размер второй строки строки:" << endl;
    do
    {
        size = getValue();

    } while (size == 0 || size > 80);

    String str2(size);

    cout << endl;
    cout << "\tВведите вторую строку:" << endl;
    cout << " [str]  ";
    str2.inputStr();

    cout << endl;
    dot(26);
    cout << endl
         << endl;

    cout << "\tВведите третью строку:" << endl;
    cout << " [str]  ";
    cin.getline(string, 80);
    String str3(string);

    cout << endl;
    dash(80);
    cout << endl
         << endl;

    cout << "\tВывод всех введенных строк:" << endl;
    cout << " [str]  ";
    str1.outputStr();
    cout << " [str]  ";
    str2.outputStr();
    cout << " [str]  ";
    str3.outputStr();

    cout << endl;
    cout << "\tКоличество созданных объектов строк = ";
    String::showObjectsNumbr();

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

// проверка ввода int (после ввода)
int getValue()
{
    int a;

    cout << "     |" << endl;
    cout << "     '->";
    cin >> a;
    eatline();

    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();

    return a;
}
