// Задание 1.
// Реализовать базу данных ГАИ по штрафным квитанциям с помощью бинарного дерева.
// Ключом будет служить номер автомашины, значением узла –
// список правонарушений. Если квитанция добавляется в первый раз,
// то в дереве появляется новый узел, а в списке - данные по правонарушению;
// если нет, то данные заносятся в существующий список.
// Необходимо также реализовать следующие операции:
// - Полная распечатка базы данных (по номерам машин и списку правонарушений,
//   числящихся за ними).
// - Распечатка данных по заданному номеру.

#include <windows.h>
#include <iostream>

const int size_ = 255;

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

//=========================================================
struct Fine
{
    char *offense;
    Fine *next;
};
class List
{
    Fine *head;
    Fine *tail;

public:
    List()
    {
        head = tail = NULL;
    }
    List(const List &obj)
    {
    }
    ~List()
    {
        delList();
    }
    void addList(char *key);
    void show();
    void delList();
};

void List::addList(char *key)
{
    Fine *temp = new Fine;
    temp->offense = new char[strlen(key) + 1];
    strcpy(temp->offense, key);
    temp->next = NULL;
    if (head != NULL)
    {
        tail->next = temp;
        tail = temp;
    }
    else
    {
        head = tail = temp;
    }
}
void List::show()
{
    cout << "\tНарушения:" << endl;
    Fine *temp = head;
    while (temp)
    {
        cout << "\t\t"
             << "  " << temp->offense << endl;
        temp = temp->next;
    }
    cout << endl;
}
void List::delList()
{
    Fine *del;
    while (head)
    {
        del = head->next;
        delete head;
        head = del;
    }
}
//=========================================================

struct TrafficPolice
{
    char *vehicleNumber;
    TrafficPolice *left_;
    TrafficPolice *right_;
    List temp;
};
class TreeTPolice
{
    TrafficPolice *root;

public:
    TreeTPolice()
    {
        root = NULL;
    }
    TreeTPolice(const TreeTPolice &obj)
    {
    }
    ~TreeTPolice()
    {
        del(root);
    }
    void addTree(char *vehicleNumber, char *fine, TrafficPolice *&root);
    TrafficPolice *&getRoot();
    void show(TrafficPolice *root);
    void del(TrafficPolice *&root);
    void search(TrafficPolice *root, char *number);
};

void TreeTPolice::search(TrafficPolice *root, char *vehicleNumber)
{
    if (strcmp(root->vehicleNumber, vehicleNumber) == 0)
    {
        cout << "\tНомер транспорта: " << root->vehicleNumber << endl;
        root->temp.show();
    }
    if (strcmp(root->vehicleNumber, vehicleNumber) < 0)
    {
        if (root->left_ == NULL)
            cout << "\tТранспорт отсутствует в базе данных." << endl;
        else
            search(root->left_, vehicleNumber);
    }
    if (strcmp(root->vehicleNumber, vehicleNumber) > 0)
    {
        if (root->right_ == NULL)
            cout << "\tТранспорт отсутствует в базе данных." << endl;
        else
            search(root->right_, vehicleNumber);
    }
}
void TreeTPolice::del(TrafficPolice *&root)
{
    if (root != NULL)
    {
        del(root->left_);
        del(root->right_);
        delete root;
        root = NULL;
    }
}
void TreeTPolice::show(TrafficPolice *root)
{
    if (root != NULL)
    {
        show(root->left_);
        cout << endl;
        dot(26);
        cout << endl
             << endl;
        cout << "\tНомер транспорта: " << root->vehicleNumber << endl;
        root->temp.show();
        show(root->right_);
    }
}
void TreeTPolice::addTree(char *vehicleNumber, char *fine, TrafficPolice *&root)
{
    if (root == NULL)
    {
        root = new TrafficPolice;
        root->vehicleNumber = new char[strlen(vehicleNumber) + 1];
        strcpy(root->vehicleNumber, vehicleNumber);
        root->temp.addList(fine);
        root->left_ = NULL;
        root->right_ = NULL;
    }
    else
    {
        if (strcmp(root->vehicleNumber, vehicleNumber) < 0)
            addTree(vehicleNumber, fine, root->left_);
        if (strcmp(root->vehicleNumber, vehicleNumber) > 0)
            addTree(vehicleNumber, fine, root->right_);
        if (strcmp(root->vehicleNumber, vehicleNumber) == 0)
            root->temp.addList(fine);
    }
}

TrafficPolice *&TreeTPolice::getRoot()
{
    return root;
}

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TreeTPolice obj;

    char vehicleNumber[size_];
    char fine[size_];

    int menu;
    int option;
    char repeat;

    bool baseON = false;
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
        cout << "\t\t***| База данных ГАИ по штрафным квитанциям |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню для работы:" << endl;
        cout << "\t1) Внести данные о правонарушении." << endl;
        cout << "\t2) Вывод на экран полную базу данных о правонарушениях." << endl;
        cout << "\t3) Вывод данных о правонарушениях по заданному номеру транспорта." << endl;
        cout << "\t4)  | ВыхоД |";

        menu = getValueInt();
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
            cout << "\t   Добавить данные о правонарушении?" << endl;
            cout << "\t1. ДА." << endl;
            cout << "\t2. НЕТ.";

            do
            {
                option = 0;
                option = getValueInt();

                if (option != 1 && option != 2)
                {
                    cout << endl
                         << "\tНекорректный ввод (Ответ = 2 -нет).";
                    cout << endl
                         << "\tПожалуйста правильно ответьте на вопрос.";
                }
            } while (option != 1 && option != 2);

            if (option == 1)
            {
                do
                {
                    cout << endl;
                    dot(26);
                    cout << endl;

                    do
                    {
                        cout << endl
                             << "\tВведите номер транспорта:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin.getline(vehicleNumber, size_);
                    } while (vehicleNumber[0] == '\0' || (int)strlen(vehicleNumber) > 20);

                    do
                    {
                        cout << endl
                             << "\tВведите правонарушение:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin.getline(fine, size_);
                    } while (fine[0] == '\0' || (int)strlen(fine) > 60);

                    obj.addTree(vehicleNumber, fine, obj.getRoot());
                    baseON = true;

                    cout << "\t";
                    dotdot(25);
                    cout << endl
                         << "\tY - Добавить еще данные.";
                    cout << endl
                         << "     |  Q - Выход в Главное меню.";
                    cout << endl
                         << "     '->";
                    repeat = cin.get();
                    eatline();
                } while (repeat == 'y' || repeat == 'Y');
            }
            if (option == 2)
            {
                break;
            }
        }
        break;

        case 2:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl;

            if (baseON)
            {
                cout << "\tБаза данных ГАИ по штрафным квитанциям:" << endl;
                obj.show(obj.getRoot());
            }
            else
            {
                cout << "\tБаза данных ГАИ по штрафным квитанциям не создана (1 пункт меню)." << endl;
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

        case 3:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (baseON)
            {
                cout << "\t   Произвести поиск в базе данных по номеру транспорта?" << endl;
                cout << "\t1. ДА." << endl;
                cout << "\t2. НЕТ.";
                do
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Ответ = 2 -нет).";
                        cout << endl
                             << "\tПожалуйста правильно ответьте на вопрос.";
                    }
                } while (option != 1 && option != 2);

                if (option == 1)
                {
                    do
                    {
                        cout << endl;
                        dot(26);
                        cout << endl;

                        do
                        {
                            cout << endl
                                 << "\tВведите номер транспорта для поиска в базе данных:" << endl;
                            cout << "     |" << endl;
                            cout << "     '->";
                            cin.getline(vehicleNumber, size_);
                        } while (vehicleNumber[0] == '\0' || (int)strlen(vehicleNumber) > 20);

                        cout << endl;
                        obj.search(obj.getRoot(), vehicleNumber);

                        cout << "\t";
                        dotdot(40);
                        cout << endl
                             << "\tY - Продолжить поиск другого номера.";
                        cout << endl
                             << "     |  Q - Выход в Главное меню.";
                        cout << endl
                             << "     '->";
                        repeat = cin.get();
                        eatline();
                    } while (repeat == 'y' || repeat == 'Y');
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
            {
                cout << "\tБаза данных ГАИ по штрафным квитанциям не создана (1 пункт меню)." << endl;

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
        }
        break;

        case 4:
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
