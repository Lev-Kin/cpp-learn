// Задание 1.
// Создайте приложение "Телефонная книга".
// Необходимо хранить данные об абоненте:
// - Фамилия;
// - Имя;
// - Отчество;
// - домашний телефон;
// - рабочий телефон;
// - мобильный телефон;
// - дополнительная информация о контакте.
// внутри соответствующего класса.
// Наполните класс переменными-членами, функциями-членами, конструкторами,
// inline-функциями-членами, используйте инициализаторы, реализуйте деструктор.
// Обязательно необходимо выделять динамически память под ФИО.
// Предоставьте пользователю возможность добавлять новых абонентов,
// удалять абонентов, искать абонентов по ФИО, искать абонентов по телефонам,
// показывать всех абонентов, сохранять информацию в файл и загружать из файла.

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <iomanip> // std::setw

#define FILE_NAME "Notebook.dat"

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

class Notebook
{
public:
    struct Phones
    {
        char *home;
        char *work;
        char *mobile;
    } phone;
    struct FullName
    {
        char *name;
        char *surname;
        char *patronymic;
    } nsp;

    char *addition;

    Notebook()
    {
        phone.home = new char[15];
        phone.work = new char[15];
        phone.mobile = new char[15];

        nsp.name = new char[81];
        nsp.surname = new char[81];
        nsp.patronymic = new char[81];

        addition = new char[81];
    }
    ~Notebook()
    {
        delete[] phone.home;
        phone.home = NULL;
        delete[] phone.work;
        phone.work = NULL;
        delete[] phone.mobile;
        phone.mobile = NULL;

        delete[] nsp.name;
        nsp.name = NULL;
        delete[] nsp.surname;
        nsp.surname = NULL;
        delete[] nsp.patronymic;
        nsp.patronymic = NULL;

        delete[] addition;
        addition = NULL;
    }

    void InputFullName()
    {
        cout << "\t------------------------------" << endl;
        cout << "\tДанные по ФИО:" << endl;
        cout << "\tИмя: ";
        cin >> nsp.name;
        cout << "\tФамилия: ";
        cin >> nsp.surname;
        cout << "\tОтчество: ";
        cin >> nsp.patronymic;
    }
    void InputPhones()
    {
        cout << "\t------------------------------" << endl;
        cout << "\tДанные по телефонам:" << endl;
        cout << "\tДомашний: ";
        cin >> phone.home;
        cout << "\tРабочий: ";
        cin >> phone.work;
        cout << "\tМобильный: ";
        cin >> phone.mobile;
    }
    void InputAddition()
    {
        eatline();
        cout << "\t------------------------------" << endl;
        cout << "\tДомашний адрес: ";
        cin.getline(addition, 81);
    }

    void Show()
    {
        cout << " |   | 1. Имя --> " << setw(32) << nsp.name << " | Домашний:" << setw(15) << phone.home << " |" << endl;
        cout << " |   | 2. Фамилия --> " << setw(28) << nsp.surname << " | Рабочий:" << setw(16) << phone.work << " |" << endl;
        cout << " |   | 3. Отчество --> " << setw(27) << nsp.patronymic << " | Мобильный:" << setw(14) << phone.mobile << " |" << endl;
        cout << " |   | Дополнительно: -     -     -     -     -    |--------------------------|" << endl;
        cout << " |   | 4. Домашний адрес --> " << setw(21) << addition << " |                          |" << endl;
    }

    Notebook *Remove(Notebook *PNotebookDelete, int index, int *size_)
    {
        int size_delete;
        size_delete = *size_;
        if (index < 0 || index > size_delete - 1)
        {
            cout << "\tИндекс за границами массива." << endl;
            return NULL;
        }

        Notebook *tmp;
        tmp = new Notebook[size_delete];
        for (int i = 0; i < size_delete; i++)
        {
            strcpy(tmp[i].phone.home, PNotebookDelete[i].phone.home);
            strcpy(tmp[i].phone.work, PNotebookDelete[i].phone.work);
            strcpy(tmp[i].phone.mobile, PNotebookDelete[i].phone.mobile);
            strcpy(tmp[i].nsp.surname, PNotebookDelete[i].nsp.surname);
            strcpy(tmp[i].nsp.name, PNotebookDelete[i].nsp.name);
            strcpy(tmp[i].nsp.patronymic, PNotebookDelete[i].nsp.patronymic);
            strcpy(tmp[i].addition, PNotebookDelete[i].addition);
        }
        delete[] PNotebookDelete;

        PNotebookDelete = new Notebook[size_delete - 1];
        for (int i = 0, j = 0; i < size_delete; i++, j++)
        {
            if (i == index)
                i++;

            strcpy(PNotebookDelete[j].phone.home, tmp[i].phone.home);
            strcpy(PNotebookDelete[j].phone.work, tmp[i].phone.work);
            strcpy(PNotebookDelete[j].phone.mobile, tmp[i].phone.mobile);
            strcpy(PNotebookDelete[j].nsp.surname, tmp[i].nsp.surname);
            strcpy(PNotebookDelete[j].nsp.name, tmp[i].nsp.name);
            strcpy(PNotebookDelete[j].nsp.patronymic, tmp[i].nsp.patronymic);
            strcpy(PNotebookDelete[j].addition, tmp[i].addition);
        }
        (*size_)--;
        size_delete = *size_;
        delete[] tmp;
        return PNotebookDelete;
    }
    int Save(const char *fileName, Notebook *PNotebookSave, int size_)
    {
        size_t size_data;
        FILE *file = fopen(fileName, "w+b");
        fseek(file, 0, SEEK_SET);
        fwrite(&size_, sizeof(int), 1, file);
        for (int i = 0; i < size_; i++)
        {
            size_data = strlen((PNotebookSave + i)->nsp.surname) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->nsp.surname, sizeof(char), size_data, file);
            size_data = strlen((PNotebookSave + i)->nsp.name) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->nsp.name, sizeof(char), size_data, file);
            size_data = strlen((PNotebookSave + i)->nsp.patronymic) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->nsp.patronymic, sizeof(char), size_data, file);
            size_data = strlen((PNotebookSave + i)->phone.home) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->phone.home, sizeof(char), size_data, file);
            size_data = strlen((PNotebookSave + i)->phone.work) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->phone.work, sizeof(char), size_data, file);
            size_data = strlen((PNotebookSave + i)->phone.mobile) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->phone.mobile, sizeof(char), size_data, file);
            size_data = strlen((PNotebookSave + i)->addition) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PNotebookSave + i)->addition, sizeof(char), size_data, file);
        }
        fclose(file);
        return 1;
    }

    Notebook *Load(const char *fileName, int *size)
    {
        Notebook *PNotebookLoad;
        FILE *file = fopen(fileName, "r+b");
        if (!file)
        {
            cout << "\tОШИБКА! Файл с именем " << fileName << " не существует." << endl;
            return NULL;
        }
        int size_load;
        size_t size_data;
        fseek(file, 0, SEEK_SET);
        fread(&size_load, sizeof(int), 1, file);
        PNotebookLoad = new Notebook[size_load];
        for (int i = 0; i < size_load; i++)
        {
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->nsp.surname, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->nsp.name, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->nsp.patronymic, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->phone.home, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->phone.work, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->phone.mobile, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PNotebookLoad + i)->addition, sizeof(char), size_data, file);
        }
        fclose(file);
        *size = size_load;
        return PNotebookLoad;
    }
};

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char enter; // для подтверждения выхода в главное меню
    char repeat;
    int option;
    int key = 0;

    int find; // для поиска
    int available;
    int c_note = 0; // счетчик записей
    int i;

    char *name_delete;
    char *surname_delete;
    char *patronymic_delete;
    char *phone_home; // поиск по домашнему телефону

    surname_delete = new char[81];
    name_delete = new char[81];
    patronymic_delete = new char[81];
    phone_home = new char[81];

    Notebook *PNotebookA;
    Notebook *PNotebookATmp;

    PNotebookA = new Notebook[1];

    if (!PNotebookA)
        exit(0);
    do
    {
        system("cls");
        equal(80);
        cout << endl;
        tabs(9);
        cout << endl;
        apostrophe(80);
        cout << endl;
        cout << "\t\t\t   ***| Телефонная книга |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню:" << endl;
        cout << "\t1. Добавить абонента." << endl;
        cout << "\t2. Удалить абонента." << endl;
        cout << "\t3. Найти абонента." << endl;
        cout << "\t4. Показать список всех абонентов." << endl;
        cout << "\t5. Сохранить информацию в файл." << endl;
        cout << "\t6. Загрузить информацию из файла." << endl;
        cout << "\t7.   | ВыхоД |";
        do
        {
            key = 0;
            key = getValueInt();

        } while (key <= 0);

        cout << endl;

        switch (key)
        {
        case 1: // добавить абонентов
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
                 << endl;
            cout << "\t1. Ввод записи абонента (добавить)." << endl;
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

            if (option == 1)
            {
                do
                {
                    cout << endl;
                    dot(26);
                    cout << endl
                         << endl;

                    cout << "\tЗапись № " << c_note << endl;
                    if (c_note)
                    {
                        PNotebookATmp = new Notebook[c_note];
                        for (i = 0; i < c_note; i++)
                        {
                            strcpy(PNotebookATmp[i].phone.home, PNotebookA[i].phone.home);
                            strcpy(PNotebookATmp[i].phone.work, PNotebookA[i].phone.work);
                            strcpy(PNotebookATmp[i].phone.mobile, PNotebookA[i].phone.mobile);
                            strcpy(PNotebookATmp[i].nsp.surname, PNotebookA[i].nsp.surname);
                            strcpy(PNotebookATmp[i].nsp.name, PNotebookA[i].nsp.name);
                            strcpy(PNotebookATmp[i].nsp.patronymic, PNotebookA[i].nsp.patronymic);
                            strcpy(PNotebookATmp[i].addition, PNotebookA[i].addition);
                        }
                        delete[] PNotebookA;

                        PNotebookA = new Notebook[c_note + 1];
                        for (i = 0; i < c_note; i++)
                        {
                            strcpy(PNotebookA[i].phone.home, PNotebookATmp[i].phone.home);
                            strcpy(PNotebookA[i].phone.work, PNotebookATmp[i].phone.work);
                            strcpy(PNotebookA[i].phone.mobile, PNotebookATmp[i].phone.mobile);
                            strcpy(PNotebookA[i].nsp.surname, PNotebookATmp[i].nsp.surname);
                            strcpy(PNotebookA[i].nsp.name, PNotebookATmp[i].nsp.name);
                            strcpy(PNotebookA[i].nsp.patronymic, PNotebookATmp[i].nsp.patronymic);
                            strcpy(PNotebookA[i].addition, PNotebookATmp[i].addition);
                        }
                        delete[] PNotebookATmp;
                    }

                    PNotebookA[c_note].InputFullName();
                    PNotebookA[c_note].InputPhones();
                    PNotebookA[c_note].InputAddition();
                    c_note++;

                    cout << "\t";
                    dotdot(30);
                    cout << endl
                         << "\tY - Ввести еще одну запись (добавить).";
                    cout << endl
                         << "     |  Q - Выход в Главное меню.";
                    cout << endl
                         << "     '->";
                    repeat = getche();
                } while (repeat == 'y' || repeat == 'Y');
            }
            break;

        case 2:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl;
            cout << "\t1. Удалить абонента." << endl;
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

            available = -1;

            if (option == 1)
            {
                cout << endl;
                cout << "\tВведите данные по ФИО для удаления из телефонной книги:" << endl;
                cout << "\tИмя: ";
                cin >> name_delete;
                cout << "\tФамилия: ";
                cin >> surname_delete;
                cout << "\tОтчество: ";
                cin >> patronymic_delete;
                for (i = 0; i < c_note; i++)
                {
                    if (!strcmp(PNotebookA[i].nsp.surname, surname_delete) && !strcmp(PNotebookA[i].nsp.name, name_delete) && !strcmp(PNotebookA[i].nsp.patronymic, patronymic_delete))
                    {
                        available = i;
                        PNotebookA = PNotebookA->Remove(PNotebookA, available, &c_note);
                        cout << endl
                             << "\tАбонент удален." << endl;
                        break;
                    }
                }

                if (available == -1)
                    cout << endl
                         << "\tАбонент с таким ФИО не найден." << endl;

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
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl;
            cout << "\t1. Поиск абонента по ФИО." << endl;
            cout << "\t2. Поиск абонента по домашнему номеру телефона." << endl;
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

            find = -1;

            if (option == 1)
            {
                cout << endl;
                cout << "\tВведите данные по ФИО для нахождения в телефоной книги:" << endl;
                cout << "\tИмя: ";
                cin >> name_delete;
                cout << "\tФамилия: ";
                cin >> surname_delete;
                cout << "\tОтчество: ";
                cin >> patronymic_delete;
                cout << endl;
                cout << " .____________________________________________________________________________." << endl;
                cout << " | № |               Абонент (ФИО)                 | Контактные данные (тел.) |" << endl;
                cout << " |---|---------------------------------------------|--------------------------|" << endl;
                for (i = 0; i < c_note; i++)
                {
                    if (strcmp(PNotebookA[i].nsp.surname, surname_delete) == 0 && strcmp(PNotebookA[i].nsp.name, name_delete) == 0 && strcmp(PNotebookA[i].nsp.patronymic, patronymic_delete) == 0)
                    {
                        cout << " | " << i << " |                                             |                          |" << endl;
                        find = 1;
                        PNotebookA[i].Show();
                    }
                }
                cout << " |___|_____________________________________________|__________________________|" << endl;
                if (find == -1)
                    cout << endl
                         << "\tАбонент с таким ФИО не найден." << endl;

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
            if (option == 2)
            {
                cout << endl;
                cout << "\tВведите домашний телефон абонента: ";
                cin >> phone_home;
                cout << endl;
                cout << " .____________________________________________________________________________." << endl;
                cout << " | № |               Абонент (ФИО)                 | Контактные данные (тел.) |" << endl;
                cout << " |---|---------------------------------------------|--------------------------|" << endl;
                for (i = 0; i < c_note; i++)
                {
                    if (strcmp(PNotebookA[i].phone.home, phone_home) == 0)
                    {
                        cout << " | " << i << " |                                             |                          |" << endl;
                        find = 1;
                        PNotebookA[i].Show();
                    }
                }
                cout << " |___|_____________________________________________|__________________________|" << endl;
                if (find == -1)
                    cout << endl
                         << "\tАбонент с таким ФИО не найден." << endl;

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
                 << endl;

            cout << "  Телефонная книга." << endl;
            cout << " .____________________________________________________________________________." << endl;
            cout << " | № |               Абонент (ФИО)                 | Контактные данные (тел.) |" << endl;
            cout << " |---|---------------------------------------------|--------------------------|" << endl;
            for (i = 0; i < c_note; i++)
            {
                cout << " | " << i << " |                                             |                          |" << endl;
                PNotebookA[i].Show();
                if (i != c_note - 1)
                    cout << " |---|---------------------------------------------|--------------------------|" << endl;
            }
            cout << " |___|_____________________________________________|__________________________|" << endl;

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
                 << endl;
            cout << "\t===> Вы точно хотите? <===" << endl;
            cout << "\t1.    >>>СОХРАНИТЬ<<< (записать перезаписать данные)." << endl;
            cout << "\t2.      | Отмена |"; // оставить как есть

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

            if (option == 1)
            {
                if (PNotebookA->Save(FILE_NAME, PNotebookA, c_note))
                    cout << endl
                         << "\tДанные успешно сохранены в файл. (" << FILE_NAME << ")" << endl;

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

        case 6:
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 6 пункт меню |_______" << endl
                 << endl;
            cout << "\t===> Вы точно хотите? <===" << endl;
            cout << "\t1.    >>>ЗАГРУЗИТЬ<<< (несохраненные данные будут потеряны)." << endl;
            cout << "\t2.      | Отмена |"; // оставить как есть

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

            if (option == 1)
            {
                if (PNotebookA)
                    delete[] PNotebookA;
                PNotebookA = PNotebookA->Load(FILE_NAME, &c_note);
                if (PNotebookA != NULL)
                    cout << endl
                         << "\tДанные успешно загружены с файла. (" << FILE_NAME << ")" << endl;

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
            break;

        default:
            cout << endl;
            cout << "\tНеверный пункт меню." << endl;
            cout << "\tБудьте внимательны!!!" << endl;
            cout << "\tДля продолжения-<ENTER>";
            enter = getch();
            break;
        }
    } while (key != 7);

    if (PNotebookA)
        delete[] PNotebookA;

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

// проверка ввода int (после ввода)
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
