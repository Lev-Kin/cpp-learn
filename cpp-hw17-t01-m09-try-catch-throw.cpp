// Добавьте в решение задачи Иосифа Флавия 
// с помощью односвязного списка механизм обработки исключений.
// Генерируйте исключения в случае ошибок.
// Например, нехватка памяти, попытка удаления из пустого списка и т.д.

#include <windows.h>
#include <iostream>
#include <string>

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

struct Node
{
    Node *next;
    int warrior;
    bool work;
};

class List
{
    Node *head;
    Node *tail;
    int squad;

public:
    List()
    {
        head = 0;
        tail = 0;
        squad = 0;
    }
    ~List()
    {
        clearList();
    }

    void get(int squad);
    void createSquad();
    void addList(int i);
    int life();
    void killWarrior(int step_kill);
    void survivalPlace();
    void clearList();
};

void List::get(int squad)
{
    this->squad = squad;
}

void List::createSquad()
{
    for (int i = 1; i <= squad; i++)
    {
        addList(i);
    }
}

void List::addList(int i)
{
    Node *unit = nullptr;
    unit = new Node;
    try
    {
        if (unit)
        {
            unit->work = true;
            unit->warrior = i;
            unit->next = 0;
            if (head != 0)
            {
                tail->next = unit;
                tail = unit;
            }
            else
            {
                head = tail = unit;
            }
        }
        else
        {
            throw(char *) "Память не выделяется.";
        }
    }
    catch (const char *s)
    {
        cout << endl
             << "\t" << s << endl;
        exit(0);
    }
}

int List::life()
{
    int life = 0;
    Node *temp = head;
    while (temp)
    {
        if (temp->work)
            life++;

        temp = temp->next;
    }
    return life;
}

void List::killWarrior(int step_kill)
{
    int count = 0;
    Node *temp;
    while (life() >= step_kill)
    {
        temp = head;
        while (temp)
        {
            if (temp->work)
            {
                count++;
            }
            if (temp->work && count == step_kill)
            {
                temp->work = false;
                count = 0;
            }
            temp = temp->next;
        }
    }
}

void List::survivalPlace()
{
    int i = 0;
    cout << "\t=== Места выживания ===" << endl
         << "\t";
    Node *temp = head;
    while (temp)
    {
        if (temp->work)
        {
            cout << temp->warrior << " | ";
            i++;
            if (i % 10 == 0)
                cout << endl
                     << "\t";
        }
        temp = temp->next;
    }
}

void List::clearList()
{
    try
    {
        throw(char *) "Память освобождена.";
    }
    catch (const char *s)
    {
        cout << endl
             << "\t" << s << endl;

        Node *tmp = nullptr;
        while (head)
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
}

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List list;
    string ask;

    int squad;
    int step_kill;
    bool round = true;
    while (round)
    {
        system("cls");
        equal(80);
        cout << endl;
        tabs(9);
        cout << endl;
        apostrophe(80);
        cout << endl;
        cout << "\t      ***| Модуль 9. Обработка исключительных ситуаций |***" << endl
             << endl;

        try
        {

            cout << endl;
            dot(26);
            cout << endl;

            try
            {
                cout << endl
                     << "\t1) Введите количество бойцов в армии Флавия (41):";
                squad = 0;
                squad = valueTypeI();

                if (squad < 2)
                    throw squad;
            }
            catch (int squad)
            {
                if (squad < 2)
                {
                    cout << endl
                         << "\tКоличество бойцов должно быть больше 1." << endl;
                    dotdot(80);
                    cout << endl;
                    tabs(9);
                    cout << endl;
                    equal(80);
                    cout << endl
                         << "\tПродолжить нажмите-<ENTER>";
                    cin.get();
                    continue;
                }
            }

            cout << endl;
            dot(26);
            cout << endl;

            try
            {
                cout << endl
                     << "\t2) Введите шаг убийства (3):";
                step_kill = 0;
                step_kill = valueTypeI();

                if (step_kill < 2)
                    throw step_kill;
            }
            catch (int step_kill)
            {
                if (step_kill < 2)
                {
                    cout << endl
                         << "\tШаг убийства должен быть больше 1." << endl;
                    dotdot(80);
                    cout << endl;
                    tabs(9);
                    cout << endl;
                    equal(80);
                    cout << endl
                         << "\tПродолжить нажмите-<ENTER>";
                    cin.get();
                    continue;
                }
            }

            if (step_kill > squad)
                throw step_kill;
        }
        catch (int step_kill)
        {
            if (step_kill > squad)
            {
                cout << endl
                     << "\tШаг убийства больше количества бойцов." << endl;
                dotdot(80);
                cout << endl;
                tabs(9);
                cout << endl;
                equal(80);
                cout << endl
                     << "\tПродолжить нажмите-<ENTER>";
                cin.get();
                continue;
            }
        }

        list.get(squad);
        list.createSquad();
        list.killWarrior(step_kill);

        cout << endl;
        dash(80);
        cout << endl
             << endl;

        list.survivalPlace();

        cout << endl
             << "\t";
        dotdot(50);
        cout << endl;
        cout << "\tПродолжить?  (y/n)" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        getline(cin, ask);

        if (!ask.compare("y") || !ask.compare("Y"))
        {
            list.clearList();
            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tПродолжить нажмите-<ENTER>";
            cin.get();
        }
        else
        {
            round = false;
        }
    }

    cout << endl;
    cout << endl
         << "\t\t\t    .........................";
    cout << endl
         << "\t\t\t    |                       |";
    cout << endl
         << "\t\t\t    |      До свидания      |";
    cout << endl
         << "\t\t\t    |                       |";
    cout << endl
         << "\t\t\t    '''''''''''''''''''''''''" << endl;

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


