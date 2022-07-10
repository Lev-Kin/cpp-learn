// Создайте класс односвязного списка для работы с целыми значениями.
// Требуется создать реализации методов для следующих операций над элементами:
// 1. Add_To_Head() - добавление элемента в голову;
// 2. Add_To_Tail() - добавление элемента в хвост;
// 3. Delete_From_Head() - удаление элемента из головы;
// 4. Delete_From_Tail() - удаление элемента из хвоста;
// 5. Delete_All() - удаление всех элементов;
// 6. Show_All () - отображение всех элементов списка на экран.
// 7. Insert_Pos() - вставка элемента в заданную позицию,
// 8. Delete_Pos() - удаление элемента по заданной позиции,
// 9. Seach_Elem() - поиск заданного элемента (функция возвращает позицию
//    найденного элемента в случае успеха или NULL в случае неудачи),
// 10. Seach_Change_Elem() - поиск и замена заданного элемента (функция
//     возвращает количество заменённых элементов в случае успеха или -1 в случае
//     неудачи),
// 11. Revers_List() - переворот списка.

#include <windows.h>
#include <iostream>
#include <ctime>
#include <iomanip>

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

struct Element
{
    int data;
    Element *next;
};

class List
{

public:
    List();
    ~List();
    void Add_To_Head(int data);
    void Add_To_Tail(int data);
    int Delete_From_Head();
    int Delete_From_Tail();
    int Delete_All();
    int Show_All();
    void Insert_Pos(int position, int data);
    void Delete_Pos(int position);
    int Seach_Elem(int data);
    int Search_Change_Elem(int data, int change);
    void Revers_List();
    int amountIndex();

private:
    Element *_head;
    int _count;
};

List::List()
{
    _head = nullptr;
    _count = 0;
}

List::~List()
{
    if (Delete_All())
    {
        cout << endl
             << "\tDestructor worked." << endl;
    }
}

void List::Add_To_Head(int data)
{
    Element *temp = new Element;
    temp->data = data;
    temp->next = _head;
    _head = temp;
    cout << "\tДобавлен элемент [" << setw(2) << _count << "] = " << setw(3) << data << " в ГОЛОВУ списка." << endl;
    _count++;
}

void List::Add_To_Tail(int data)
{
    if (_head == nullptr)
    {
        Element *temp = new Element;
        temp->data = data;
        temp->next = _head;
        _head = temp;
        cout << "\tДобавлен элемент [" << setw(2) << _count << "] = " << setw(3) << data << " в ХВОСТ списка." << endl;
        _count++;
    }
    else
    {
        Element *current = _head;
        for (int i = 0; i < _count - 1; i++)
            current = current->next;

        Element *temp = new Element;
        temp->data = data;
        temp->next = nullptr;
        current->next = temp;
        cout << "\tДобавлен элемент [" << setw(2) << _count << "] = " << setw(3) << data << " в ХВОСТ списка." << endl;
        _count++;
    }
}

int List::Delete_From_Head()
{
    if (_head)
    {
        Element *temp = _head;
        _head = temp->next;
        delete temp;
        _count--;
        return 1;
    }
    else
        return 0;
}

int List::Delete_From_Tail()
{
    Element *current = _head;
    Element *temp = nullptr;
    int i = 0;

    if (_head)
    {
        if (_count > 1)
        {
            while (current->next)
            {
                if (i++ == _count - 2)
                {
                    temp = current->next;
                    current->next = nullptr;
                    break;
                }
                current = current->next;
            }
            delete temp;
            _count--;
        }
        else
        {
            delete _head;
            _head = nullptr;
        }
        return 1;
    }
    else
        return 0;
}

int List::Delete_All()
{
    if (_head)
    {
        while (_head != 0)
            Delete_From_Head();
        return 1;
    }
    else
        return NULL;
}

int List::Show_All()
{
    Element *temp = _head;
    int i = 0;
    if (_head)
    {
        cout << "[ГОЛОВА]";
        for (i = 0; temp != 0; i++)
        {
            cout << setw(2) << "[" << setw(2) << i << "] = " << setw(3) << temp->data << " ";
            temp = temp->next;
            if ((i + 1) % 5 == 0)
                cout << endl
                     << "\t";

            if (_count == i + 1)
                cout << " [ХВОСТ]" << endl;
        }
        return 1;
    }
    else
        return 0;
}

int List::amountIndex()
{
    return _count;
}

void List::Insert_Pos(int position, int data)
{
    Element *tmp = _head;
    Element *next = tmp->next;

    if (position == 0)
        Add_To_Head(data);
    else
        for (int i = 0; i < _count; i++)
        {
            if (i == position - 1)
            {
                Element *in = new Element;
                in->data = data;
                tmp->next = in;
                in->next = next;
                _count++;
                break;
            }
            tmp = tmp->next;
            next = next->next;
        }
}

void List::Delete_Pos(int position)
{
    Element *tmp = _head;
    Element *next = tmp->next;

    if (position == 0)
        Delete_From_Head();
    else
        for (int i = 0; i < _count; i++)
        {
            if (i == position - 1)
            {
                delete tmp->next;
                tmp->next = next->next;
                _count--;
                break;
            }
            tmp = tmp->next;
            next = next->next;
        }
}

int List::Seach_Elem(int data)
{
    int position = 0;
    Element *temp = _head;

    if (_head)
    {
        while (temp)
        {
            if (temp->data == data)
                return position;
            temp = temp->next;
            position++;
        }
        return NULL;
    }
    else
        return -1;
}

int List::Search_Change_Elem(int data, int change)
{
    int number = 0;
    Element *temp = _head;

    if (_head)
    {
        while (temp)
        {
            if (temp->data == data)
            {
                temp->data = change;
                number++;
            }
            temp = temp->next;
        }
        if (number > 0)
            return number;
        else
            return -1;
    }
    else
        return NULL;
}

void List::Revers_List()
{
    Element *temp = _head;
    int *array = new int[_count];

    for (int i = 0; i < _count; i++)
    {
        array[i] = temp->data;
        temp = temp->next;
    }
    temp = _head;
    for (int i = _count - 1; i >= 0; i--)
    {
        temp->data = array[i];
        temp = temp->next;
    }
    delete[] array;
}

int main(void)
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(nullptr));

    List list;

    int menu;
    int option;
    char repeat;

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
        cout << "\t       ***| Практическая работа №2 (singlyLinkedList) |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t    Выберите ПУНКТ меню для работы:" << endl;
        cout << "\t 1) Добавить элемент в голову списка (+rand)." << endl;
        cout << "\t 2) Добавить элемент в хвост списка." << endl;
        cout << "\t 3) Удаление элемента из головы списка." << endl;
        cout << "\t 4) Удаление элемента из хвоста списка." << endl;
        cout << "\t 5) Удаление всех элементов из списка." << endl;
        cout << "\t 6) Отображение всех элементов списка на экране." << endl;
        cout << "\t 7) Вставка элемента в заданную позицию списка." << endl;
        cout << "\t 8) Удаление элемента из заданной позиции списка." << endl;
        cout << "\t 9) Поиск заданного значения элемента в списке." << endl;
        cout << "\t10) Поиск и замена заданного элемента в списке." << endl;
        cout << "\t11) Реверс списка." << endl;
        cout << "\t12) Выход.";
        do
        {
            menu = 0;
            menu = getValueInt();

            if (menu < 0)
            {
                cout << endl
                     << "\tОшибка! Введено отрицательное значение." << endl;
                cout << "\tПожалуйста повторите ввод." << endl;
            }

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
            cout << "\t1. Добавить элемент в голову." << endl;
            cout << "\t2. Будет добавлено 42 элемента в голову." << endl;
            cout << "\t3.   | Отмена |";

            do
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

            if (option == 1)
            {
                int data;
                do
                {
                    cout << endl;
                    dot(26);
                    cout << endl;
                    do
                    {
                        cout << endl
                             << "\tВведите значение элемента:";
                        data = 0;
                        data = getValueInt();

                    } while (data < -99 || data > 99);
                    cout << endl;
                    list.Add_To_Head(data);
                    operate = true;

                    cout << "\t";
                    dotdot(45);
                    cout << endl
                         << "\tY - Добавить еще элемент в ГОЛОВУ.";
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
                int data;
                cout << endl;
                dot(26);
                cout << endl
                     << endl;
                for (int i = 0; i < 42; i++)
                {
                    data = rand() % 198 - 99;
                    list.Add_To_Head(data);
                }
                operate = true;

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
            if (option == 3)
            {
                break;
            }

            break;
        }

        case 2:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl
                 << endl;
            cout << "\t1. Добавить элемент в хвост." << endl;
            cout << "\t2.   | Отмена |";

            do
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

            if (option == 1)
            {
                int data;
                do
                {
                    cout << endl;
                    dot(26);
                    cout << endl;
                    do
                    {
                        cout << endl
                             << "\tВведите значение элемента:";
                        data = 0;
                        data = getValueInt();

                    } while (data < -99 || data > 99);
                    cout << endl;
                    list.Add_To_Tail(data);
                    operate = true;

                    cout << "\t";
                    dotdot(45);
                    cout << endl
                         << "\tY - Добавить еще элемент в ХВОСТ.";
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

            break;
        }

        case 3:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Удалить элемент из головы списка." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;
                    if (list.Show_All())
                    {
                        cout << endl
                             << endl;
                    }
                    if (list.Delete_From_Head())
                    {
                        cout << "\tЭлемент был удален из ГОЛОВЫ списка." << endl;
                        cout << "\tНовый измененный список:" << endl
                             << endl;
                        list.Show_All();
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 4:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Удалить элемент с хвоста списка." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;
                    if (list.Show_All())
                    {
                        cout << endl
                             << endl;
                    }
                    if (list.Delete_From_Tail())
                    {
                        cout << "\tЭлемент был удален c ХВОСТА списка." << endl;
                        cout << "\tНовый измененный список:" << endl
                             << endl;
                        list.Show_All();
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 5:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 5 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Удалить все элементы со списка." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;
                    cout << "\tВсе элементы из списка были удалены." << endl;
                    list.Delete_All();
                    operate = false;
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 6:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                if (list.Show_All())
                {
                    cout << endl;
                    cout << "\tВыше представлены все элементы списка." << endl;
                }
                else
                {
                    cout << "\tСписок пуст!" << endl;
                    operate = false;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 7:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 7 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Вставить элемент в указанную позицию списка." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    int position;
                    int data;
                    int index = list.amountIndex();

                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (list.Show_All())
                    {
                        cout << endl;
                        cout << "\tВыше представлен список до вставки элемента." << endl;
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }

                    if (operate)
                    {
                        cout << endl
                             << endl;

                        cout << "\tПозиции для вставки элемента (0 - " << index << "):";
                        do
                        {
                            position = 0;
                            cout << endl
                                 << "\tВведите позицию на которую хотите вставить элемент:";
                            position = getValueInt();

                            if (position < 0)
                            {
                                cout << endl
                                     << "\tОшибка! ВВедено отрицательное значение позиции." << endl;
                                cout << "\tПожалуйста повторите ввод." << endl;
                            }
                            if (position > index)
                            {
                                cout << endl
                                     << "\tОшибка! Введена позиция выходящая за пределы последней позиции." << endl;
                                cout << "\tПожалуйста повторите ввод." << endl;
                            }

                        } while (position < 0 || position > index);

                        do
                        {
                            cout << endl
                                 << "\tВведите значение элемента которое будет на [" << position << "] позиции:";
                            data = 0;
                            data = getValueInt();

                        } while (data < -99 || data > 99);

                        list.Insert_Pos(position, data);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tСписок после вставки элемента: " << endl
                             << endl;
                        list.Show_All();
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 8:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 8 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Удалить элемент из указанной позиции списка." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    int position;
                    int index = list.amountIndex();

                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (list.Show_All())
                    {
                        cout << endl;
                        cout << "\tВыше представлен список до удаления элемента." << endl;
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }

                    if (operate)
                    {
                        cout << endl
                             << endl;

                        cout << "\tПозиции для удаления элемента (0 - " << index - 1 << "):";
                        do
                        {
                            position = 0;
                            cout << endl
                                 << "\tВведите позицию на которую хотите вставить элемент:";
                            position = getValueInt();

                            if (position < 0)
                            {
                                cout << endl
                                     << "\tОшибка! Введено отрицательное значение позиции." << endl;
                                cout << "\tПожалуйста повторите ввод." << endl;
                            }
                            if (position > index - 1)
                            {
                                cout << endl
                                     << "\tОшибка! Введена позиция выходящая за пределы последней позиции." << endl;
                                cout << "\tПожалуйста повторите ввод." << endl;
                            }

                        } while (position < 0 || position > index - 1);

                        list.Delete_Pos(position);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tСписок после удаления элемента с указанной позиции: " << endl
                             << endl;
                        list.Show_All();
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 9:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 9 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Провести поиск по указанному значению в списке." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {

                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (list.Show_All())
                    {
                        cout << endl;
                        cout << "\tВыше представлен список для поиска элемента." << endl;
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }

                    if (operate)
                    {
                        int data;
                        do
                        {
                            cout << endl
                                 << "\tВведите значение элемента для поиска:";
                            data = 0;
                            data = getValueInt();

                        } while (data < -99 || data > 99);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        if (list.Seach_Elem(data) > 0)
                        {
                            cout << "\tВ списке найден первый элемент с искомым значением (" << data << ")." << endl;
                            cout << "\tЭлемент находится на " << list.Seach_Elem(data) << "-ой позиции." << endl;
                        }
                        else
                        {
                            cout << "\tЭлемент с искомым значением отсутствует в списке." << endl;
                        }
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 10:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 10 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Провести поиск по искомому значению в списке с заменой значения." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (list.Show_All())
                    {
                        cout << endl;
                        cout << "\tВыше представлен список для замены значения(ий) элемента(ов)." << endl;
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }

                    if (operate)
                    {
                        int data;
                        int change;
                        int count;

                        do
                        {
                            cout << endl
                                 << "\tВведите значение которые хотите заменить в списке:";
                            data = 0;
                            data = getValueInt();

                        } while (data < -99 || data > 99);

                        do
                        {
                            cout << endl
                                 << "\tВведите значение, на которое хотите произвести замену:";
                            change = 0;
                            change = getValueInt();

                        } while (change < -99 || change > 99);

                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        count = list.Search_Change_Elem(data, change);
                        if (count > 0)
                        {
                            cout << "\tПроизведена замена " << count << " элемента(ов)." << endl;
                            cout << "\tСписок после замены значения(ий) элемента(ов): " << endl
                                 << endl;
                            list.Show_All();
                        }
                        else
                            cout << "\tЗамена не производилась, т.к элемент отсутствует в списке." << endl;
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 11:
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 11 пункт меню |_______" << endl
                 << endl
                 << endl;

            if (operate)
            {
                cout << "\t1. Выполнить реверс списка." << endl;
                cout << "\t2.   | Отмена |";
                do
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

                if (option == 1)
                {
                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    if (list.Show_All())
                    {
                        cout << endl;
                        cout << "\tВыше представлен cписок до реверса." << endl;
                    }
                    else
                    {
                        cout << "\tСписок пуст!" << endl;
                        operate = false;
                    }

                    if (operate)
                    {
                        cout << endl;
                        dot(26);
                        cout << endl
                             << endl;

                        cout << "\tРеверс списка произведен." << endl;
                        list.Revers_List();
                        cout << "\tПеревернутый список:" << endl
                             << endl;
                        list.Show_All();
                    }
                }
                if (option == 2)
                {
                    break;
                }
            }
            else
                cout << "\tДобавьте элементы в список (1 пункт или 2 пункт меню)." << endl;
            ;

            cout << endl;
            dotdot(80);
            cout << endl;
            tabs(9);
            cout << endl;
            equal(80);
            cout << endl
                 << "\tВернутся в главное меню нажмите-<ENTER>";
            cin.get();

            break;
        }

        case 12:
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
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }
}

/*
void eatline2(void)
{
    while (cin.fail())
    {
        if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << endl << "\tОшибка! Допускается только ввод цифр." << endl;
            cout << "\tПожалуйста повторите ввод." << endl;
        }
    }
}
*/
