// Задание.
// Создайте программу, имитирующую многоквартирный дом.
// Необходимо иметь классы “Человек”, “Квартира”, “Дом”.
// Класс “Квартира” содержит динамический массив объектов класса “Человек”.
// Класс “Дом” содержит массив объектов класса “Квартира”.
// Каждый из классов содержит переменные-члены и функции-члены,
// которые необходимы для предметной области класса.
// Следует обратить внимание, что память под строковые значения выделяется динамически.
// Например, для ФИО в классе “Человек”.
// Не забывайте обеспечить классы различными конструкторами
// (конструктор копирования обязателен), деструкторами.
// В main() протестировать работу полученного набора классов.

#include <iostream>
#include <windows.h>
#include <string.h>
#include <conio.h> // getch()
#include <iomanip> // std::setw

#define N 81

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

///////////////////////////////////////////////////////////

class Human
{
public:
    char *person;
    char *other;
    Human() /* конструктор */
    {
        person = new char[N];
        other = new char[N];
    }
    Human(const Human &ob) /* конструктор копирования */
    {
        person = ob.person;
        other = ob.other;
    }
    ~Human() /* деструктор */
    {
        delete[] person;
        person = NULL;
        delete[] other;
        other = NULL;
    }

    void install() /* заполнение и редактирование */
    {
        delete[] person;
        person = NULL;
        delete[] other;
        other = NULL;

        person = new char[N];
        other = new char[N];

        do
        {
            cout << "\tВведите Фамилию: ";
            gets_s(person, N);

        } while (person[0] == '\0' || (int)strlen(person) > 15);

        do
        {
            cout << "\tВведите место работы (ОАО Гомсельмаш): ";
            gets_s(other, N);

        } while (other[0] == '\0' || (int)strlen(other) > 15);
    }

    void show() /* показать */
    {
        cout << "\t= Фамилия: " << setw(15) << person << setw(39) << "=" << endl;
        cout << "\t= Дополнительно (работа): " << setw(15) << other << setw(24) << "=" << endl;
    }
};

class Flat
{
public:
    Human *humans;
    int number_flat;   /* номер квартиры */
    int amount_tenant; /* количество жильцов */
    int home_phone;    /* домашний телефон */

    Flat()
    {
        humans = new Human[1];
        number_flat = 0;
        amount_tenant = 0;
        home_phone = 0;
    }
    Flat(const Flat &ob)
    {
        humans = ob.humans;
    }
    ~Flat()
    {
        delete[] humans;
        humans = NULL;
    }

    void install()
    {
        do
        {
            cout << endl
                 << "\tВведите номер квартиры: ";
            number_flat = getValueInt();

        } while (number_flat <= 0 || number_flat > 100);

        do
        {
            cout << endl
                 << "\tВведите количество жильцов: ";
            amount_tenant = getValueInt();

        } while (amount_tenant <= 0 || amount_tenant > 5);

        do
        {
            cout << endl
                 << "\tВведите телефон квартиры: ";
            home_phone = getValueInt();

        } while (home_phone <= 0 || home_phone > 1000000);

        cout << endl;
        cout << "\tПроживающе жильцы квартиры №" << number_flat << endl;
        humans = new Human[amount_tenant];
        for (int i = 0; i < amount_tenant; i++)
        {
            cout << "\t--- " << i + 1 << " ---" << endl;
            humans[i].install();

            if (i != amount_tenant - 1)
            {
                cout << "\t";
                dotdot(55);
                cout << endl;
            }
            else
            {
                cout << endl;
                cout << "\tДанные о квартире №" << number_flat << " заполнены!" << endl;
                cout << "\t";
                dot(18);
                cout << endl;
            }
        }
    }

    void show()
    {
        cout << "\t=____/ Квартира №" << setw(3) << number_flat << "\\____" << setw(40) << "=" << endl;
        cout << "\t= Количество жильцов:" << setw(2) << amount_tenant << setw(42) << "=" << endl;
        cout << "\t= Tелефон квартиры:" << setw(7) << home_phone << setw(39) << "=" << endl;
        cout << "\t= Жильцы: \t\t\t\t\t\t\t=" << endl;
        for (int i = 0; i < amount_tenant; i++)
        {
            cout << "\t= --- " << i + 1 << " ---\t\t\t\t\t\t\t=" << endl;
            humans[i].show();

            if (i != amount_tenant - 1)
            {
                cout << "\t= ";
                dotdot(40);
                cout << "\t\t\t=" << endl;
            }
            else
                cout << "\t=_______________________________________________________________=" << endl;
        }
    }
};

class House
{
public:
    Flat *flats;
    char *address;    /* адрес многоквартирного дома */
    int number_house; /* номер дома */
    int amount_flat;  /* количество квартир */
    House()
    {
        flats = new Flat[1];
        address = new char[1];
        number_house = 0;
        amount_flat = 0;
    }
    House(const House &ob)
    {
        flats = ob.flats;
        address = ob.address;
    }
    ~House()
    {
        delete[] flats;
        flats = NULL;
        delete[] address;
        address = NULL;
    }

    void set(int a, int b, char *str)
    {
        number_house = a;
        amount_flat = b;
        address = new char[strlen(str) + 1];
        strcpy(address, str);
        flats = new Flat[amount_flat];
        cout << endl;
        cout << "\t\t___/ Создан ДOM №" << number_house << " \\___" << endl;
        cout << "\tРасположенный по адресу: " << address << endl;
        cout << "\tДOM №" << number_house << " многоквартирный в котором " << amount_flat << " квартир(ы)." << endl
             << endl;
    }

    void install()
    {
        for (int i = 0; i < amount_flat; i++)
        {
            cout << "\t___// " << i + 1 << " Квартира \\\\____";
            flats[i].install();
        }
    }

    void show()
    {
        cout << endl;
        cout << "\t\t\t\t                /,,,,,,/" << endl;
        cout << "\t\t\t\t             /,,,,,/" << endl;
        cout << "\t\t\t\t             //" << endl;
        cout << "\t\t\t\t           |  |" << endl;
        cout << "\t\t\t\t___________|__|__" << endl;
        cout << "\t\t      _________/                 \\__________________" << endl;
        cout << "\t ____________/  Дом №" << setw(3) << number_house << ". Адрес: " << setw(15) << address << setw(16) << "\\___" << endl;
        cout << "\t/\t\t\t\t\t\t\t        \\" << endl;
        cout << "\t=================================================================" << endl;

        for (int i = 0; i < amount_flat; i++)
        {
            flats[i].show();
        }
        cout << "\t=================================================================" << endl;
    }
};

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    House flat;

    char address[N];
    int amount_flat;
    int number_house;
    int number_flat;

    char enter;
    char repeat;
    int option;
    int menu;

    bool goback = true;
    bool work = false;
    do
    {
        system("cls");
        equal(80);
        cout << endl;
        tabs(9);
        cout << endl;
        apostrophe(80);
        cout << endl;
        cout << "\t\t\t  ***| Многоквартирный Дом |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню:" << endl;
        cout << "\t1. Создать и заполнить объект ДОМ. " << endl;
        cout << "\t2. Посмотреть запись ДОМ." << endl;
        cout << "\t3. Редактировать запись ДОМ." << endl;
        cout << "\t4. Поиск." << endl;
        cout << "\t5.   | ВыхоД |";
        do
        {
            menu = 0;
            menu = getValueInt();

        } while (menu <= 0);

        cout << endl;

        switch (menu)
        {
        case 1:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
                 << endl;
            cout << "\t1. Заполнить многоквартирный ДОМ данными (создать ДОМ)." << endl;
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
                if (work == false)
                {
                    do
                    {
                        cout << endl
                             << "\tВведите адрес дома: ";
                        gets_s(address, N);

                    } while (address[0] == '\0' || (int)strlen(address) > 15);

                    do
                    {
                        cout << endl
                             << "\tВведите номер дома: ";
                        number_house = getValueInt();

                    } while (number_house <= 0 || number_house > 100);

                    do
                    {
                        cout << endl
                             << "\tВведите количество квартир: ";
                        amount_flat = getValueInt();

                    } while (amount_flat == 0 || amount_flat > 10 || amount_flat < 2);

                    cout << endl;
                    dot(26);
                    cout << endl;

                    flat.set(number_house, amount_flat, address);
                    flat.install();
                    work = true;

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
                else
                {
                    cout << endl;
                    cout << "\t!!! ДОМ уже создан и заполнен данными." << endl;
                    cout << "\tДля редактирования многоквартирного дома - " << endl;
                    cout << "\t    пожалуйста воспользуйтесь 3 пунктом меню." << endl;

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
            }
            break;

        case 2:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl;
            if (work == false)
            {
                cout << "\tНеобходимо заполнить объект ДОМ (1 пункт меню).\n";
            }
            else
            {
                flat.show();
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
            break;

        case 3:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl;
            if (work == false)
            {
                cout << "\tНеобходимо заполнить объект ДОМ (1 пункт меню).\n";
            }
            else
            {
                cout << "\t1. Создать новый ДОМ (действующий ДОМ будет удален)." << endl;
                cout << "\t2. Изменить квартиру (в действующем ДОМе)." << endl;
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
                    do
                    {
                        cout << endl
                             << "\tВведите адрес дома: ";
                        gets_s(address, N);

                    } while (address[0] == '\0' || (int)strlen(address) > 15);

                    do
                    {
                        cout << endl
                             << "\tВведите номер дома: ";
                        number_house = getValueInt();

                    } while (number_house <= 0 || number_house > 100);

                    do
                    {
                        cout << endl
                             << "\tВведите количество квартир: ";
                        amount_flat = getValueInt();

                    } while (amount_flat == 0 || amount_flat > 10 || amount_flat < 2);
                    flat.set(number_house, amount_flat, address);
                    flat.install();
                }
                if (option == 2)
                {
                    int find = 0;

                    do
                    {
                        cout << endl
                             << "\tВведите номер квартиры которую хотите редактировать:";
                        number_flat = getValueInt();

                    } while (number_flat <= 0 || number_flat > 100);

                    cout << endl;
                    dot(26);
                    cout << endl;

                    for (int i = 0; i < amount_flat; i++)
                    {
                        if (flat.flats[i].number_flat == number_flat)
                        {
                            cout << "\tРедактируем квартиру с №" << number_flat << endl;
                            cout << "\tНовые данные:" << endl;
                            find = 1;
                            flat.flats[i].install();
                        }
                    }

                    if (find == 0)
                        cout << "\tКвартиры с таким номером в ДОМе нет." << endl;
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
            break;

        case 4:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl
                 << endl;
            if (work == false)
            {
                cout << "\tНеобходимо заполнить объект ДОМ (1 пункт меню).\n";
            }
            else
            {
                cout << "\t1. Поиск по фамилии." << endl;
                cout << "\t2. Поиск по номеру телефона." << endl;
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
                    char find_person[N];
                    int find = 0;

                    do
                    {
                        cout << endl
                             << "\tВведите фамилию: ";
                        gets_s(find_person, N);

                    } while (find_person[0] == '\0' || (int)strlen(find_person) > 15);

                    cout << endl;
                    dot(26);
                    cout << endl;

                    for (int i = 0; i < amount_flat; i++)
                    {
                        if (strcmp(flat.flats[i].humans->person, find_person) == 0)
                        {
                            find = 1;
                            flat.flats[i].show();
                        }
                    }

                    if (find == 0)
                        cout << "\tТакой фамилии в ДОМе не найдено.";
                }
                if (option == 2)
                {
                    int find_phone;
                    int find = 0;

                    do
                    {
                        cout << endl
                             << "\tВведите номер телефона: ";
                        find_phone = getValueInt();

                    } while (find_phone <= 0 || find_phone > 1000000);

                    cout << endl;
                    dot(26);
                    cout << endl;

                    for (int i = 0; i < amount_flat; i++)
                    {
                        if (flat.flats[i].home_phone == find_phone)
                        {
                            find = 1;
                            flat.flats[i].show();
                        }
                    }

                    if (find == 0)
                        cout << "\tТакого телефонного номера в ДОМе нет.";
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
            break;

        case 5:
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
