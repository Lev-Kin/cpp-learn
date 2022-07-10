// Задание.
// Есть строка символов, признаком конца которой является ;.
// В строке могут быть фигурные, круглые, квадратные скобки.
// Скобки могут быть открывающими и закрывающими.
// Строку поместить в стек. Ввод строки предусмотреть с клавиатуры.
//  	Необходимо проверить корректность расстановки скобок.
//  	При этом необходимо, чтобы выполнились следующие правила:
// 1. Каждая открывающая скобка должна иметь справа такую же закрывающую.
//     Обратное также должно быть верно.
// 2. Открывающие и закрывающие пары скобок разных типов должны быть
//     правильно расположены по отношению друг к другу.
// 3. Пример правильной строки: ({x-y-z}*[x+2y]-(z+4x));
// 4. Пример неправильной строки: ([x-y-z}*[x+2y)-{z+4x)].
//  	Если все правила соблюдены выведите информационное сообщение
// о корректности строки, иначе покажите строку до места возникновения первой ошибки.

#include <windows.h>
#include <iostream>
#include <conio.h>

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

using namespace std;

struct Block
{
    char cell;
    Block *next;
};

class Stack
{

public:
    Block *str;
    Block *st;
    Stack()
    {
        st = NULL;
        str = NULL;
    }
    ~Stack()
    {
        clearStack(st);
        clearStack(str);
    }
    void addStack(char сh, Block *&head);
    char getCellOfStack(Block *&head);
    void stock(Block *&head);
    void parsing();
    void clearStack(Block *&head);
};

void Stack::addStack(char ch, Block *&head)
{
    Block *tmp = new Block;
    tmp->cell = ch;
    tmp->next = head;
    head = tmp;
}

char Stack::getCellOfStack(Block *&head)
{
    char ch = head->cell;
    Block *tmp = head;
    head = head->next;
    delete tmp;
    return ch;
}

void Stack::stock(Block *&head)
{
    Block *tmp = NULL;
    while (head)
    {
        addStack(head->cell, tmp);
        head = head->next;
    }
    head = tmp;
}

void Stack::parsing()
{
    stock(str);
    int count = 0;
    bool flag = false;
    bool flag1 = false;
    Block *tmp = str;
    while (tmp)
    {
        if (tmp->cell == '(' || tmp->cell == '{' || tmp->cell == '[')
        {
            flag = true;
            addStack(tmp->cell, st);
        }
        if (tmp->cell == ')')
        {
            if (st == NULL && flag == false)
                break;
            if (st == NULL && flag == true)
            {
                flag1 = true;
                break;
            }
            else
            {
                if (st->cell == '(')
                    getCellOfStack(st);
                else
                    break;
            }
        }
        if (tmp->cell == ']')
        {
            if (st == NULL && flag == false)
                break;
            if (st == NULL && flag == true)
            {
                flag1 = true;
                break;
            }
            else
            {
                if (st->cell == '[')
                    getCellOfStack(st);
                else
                    break;
            }
        }
        if (tmp->cell == '}')
        {
            if (st == NULL && flag == false)
                break;
            if (st == NULL && flag == true)
            {
                flag1 = true;
                break;
            }
            else
            {
                if (st->cell == '{')
                    getCellOfStack(st);
                else
                    break;
            }
        }
        tmp = tmp->next;
        count++;
    }

    if (!st && flag == true && flag1 == false)
    {
        cout << "\tСкобки расставлены верно." << endl;
    }
    else
    {
        int i = 0;

        cout << "\tСкобки расставлены неверно:" << endl;
        cout << " [str]  ";
        while (str && i < count)
        {
            cout << str->cell;
            str = str->next;
            i++;
        }
        cout << endl;
    }
}

void Stack::clearStack(Block *&head)
{
    Block *tmp = NULL;
    while (tmp)
    {
        tmp = head->next;
        delete head;
        head = tmp;
    }
    head = NULL;
}

int main()
{
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
    cout << "\t\t     ***| Задание 1 Лекция 7 (brackets) |***" << endl
         << endl
         << endl;
    char repeat;
    cout << "\tПример ввода ({x-y-z}*[x+2y]-(z+4x)) или ([x-y-z}*[x+2y)-{z+4x)]." << endl;

    //-------------------------------------------------------------------------
    do
    {
        char ch = '\0';
        Stack stack_;
        cout << endl;
        dot(26);
        cout << endl
             << endl;
        cout << "\tВведите строку:" << endl;
        cout << " [str]  ";
        while (ch != '\n')
        {
            ch = getchar();
            stack_.addStack(ch, stack_.str);
        }
        cout << endl;
        stack_.parsing();
        cout << endl
             << "\tY - Повторить.";
        cout << endl
             << "     |  Q - Выход из программы.";
        cout << endl
             << "     '->";
        repeat = getch();
    } while (repeat == 'y' || repeat == 'Y');
    //-------------------------------------------------------------------------

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
