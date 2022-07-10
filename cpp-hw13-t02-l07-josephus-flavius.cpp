// Задача носит имя Иосифа Флавия - известного историка I века.
// Существует легенда, что Иосиф выжил и стал известным благодаря
// своему математическому дару. В ходе иудейской войны он,
// будучи в составе отряда из 41 иудейского война, был изгнан римлянами в пещеру.
// Отряд, в котором состоял Иосиф, обладал неимоверно сильным боевым духом и,
// не желая сдаваться в плен, войны предпочли самоубийство. Они встали в круг и
// последовательно начали убивать каждого третьего из живых до тех пор, пока не
// останется ни одного человека. Иосиф же не разделял чаяний сослуживцев.
// Чтобы не быть убитым, Иосиф вычислил "спасительные места"
// на которое поставил себя и своего товарища.
// ... и лишь поэтому мы знаем его историю.

// Решите задачу Иосифа Флавия с помощью односвязного списка.

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
int getValueInt();

///////////////////////////////////////////////////////////

using namespace std;

class Node // узел связного списка
{
public:
    int m_item;
    Node *m_next;
    Node()
    {
        m_item = 0;
        m_next = 0;
    }
    Node(int item, Node *next)
    {
        m_item = item;
        m_next = next;
    }
};

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
    cout << "\t\t     ***| Задание 2 Лекция 7 (Josephus problem) |***" << endl
         << endl;

    int squad;
    int step_kill;
    char repeat;

    //-------------------------------------------------------------------------
    do
    {
        Node *first = new Node(1, 0); // создаем первый узел, m_item содержит номер
        first->m_next = first;        // и зацикливаем его на себя
        Node *tmp = first;            // указатель с которым будем работать в дальнейшем

        cout << endl;
        dot(26);
        cout << endl;
        do
        {
            cout << endl
                 << "\tВведите количество бойцов в отряде в которой Флавий (41):";
            squad = 0;
            squad = getValueInt();

        } while (squad <= 0 || squad < 2);

        do
        {
            cout << endl
                 << "\tВведите шаг убийства (3):";
            step_kill = 0;
            step_kill = getValueInt();

        } while (step_kill <= 0 || step_kill > squad);

        // создаем циклический список
        for (int i = 2; i <= squad; ++i)
        {
            tmp->m_next = new Node(i, first);
            tmp = tmp->m_next;
        }

        // удаляем элемент через интервал
        while (tmp != tmp->m_next)
        {
            for (int i = 1; i < step_kill; ++i)
            {
                tmp = tmp->m_next;
            }
            Node *deleteNode = tmp->m_next;
            tmp->m_next = tmp->m_next->m_next;

            delete deleteNode;
        }

        cout << endl
             << "\tБезопастное место в круге для Флавия = ";
        cout << tmp->m_item << endl; // оставшейся безопасное место

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
