// Задание.
// 1. Создайте класс Train. Необходимо хранить следующие данные:
//    Пункт отправления;
//    Пункт назначения;
//    Номер поезда;
//    Время отправления;
//    Число люкс (СВ) мест; “?можно написать 1000 мест в поезде?”
//    Число купейных мест;
//    Число (занятых) плацкартных мест;
//    Время прибытия. Ввод данных осуществить через клавиатуру.
// 2. Создать массив объектов.
// 3. Вывести: (до заданного значит конечного (или просто ищем станцию))
//    a) список поездов, следующих до заданного пункта назначения; ?
//    b) список поездов, следующих до заданного пункта назначения и
//       отправляющихся после заданного часа;? (время отп или приб или в пути?)
//    c) список поездов, отправляющихся до заданного пункта назначения и
//       имеющих свободные места.? (а свободные места откуда с потолка??)
// 4. При необходимости используйте:
//    - перегруженные конструкторы;
//    - конструктор копирования;
//    - константные функции-члены (например, для отображения информации о
//      свободных местах и т.д.).
// 5. Иметь возможность сохранять данные в файл и считывать из него.

// (Такое условие составлено неверно!)
// (это Поезда а не книги или компьютеры.)
// Добавлены необходимые данные для корректного решения практической работы.
// Для расчетов взят стандартный пассажирский поезд дальнего следования.
// 15 вагонов:
// 1 - вагон ресторан.
// 1 - вагон спальный (24 места)
// 5 - плацкарт * (54 мест) = (270 мест)
// 8 - купе * (36 мест) = (288 мест)

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

#define FILE_NAME "TrainSchedule.dat"

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
void tableUp(void);
void tableDown(void);

///////////////////////////////////////////////////////////

int getValueInt();

///////////////////////////////////////////////////////////

class TrainSchedule
{
public:
    struct Trains
    {
        char *type;      // тип номер поезда
        char *reservedS; // плацкартные зарезервированные места
        char *reservedC; // купейные зарезервированные места
        char *reservedV; // люкс зарезервированные места
        char *freeS;     // плацкартные свободные места
        char *freeC;     // купейные свободные места
        char *freeV;     // люкс свободные места
    } train;

    struct Destinations
    {
        char *departure; // отбытие начальная станция следования
        char *hour_dep;
        char *min_dep;
        char *arrive; // прибытия конечная станция следования
        char *hour_arr;
        char *min_arr;
    } route;

    TrainSchedule()
    {
        train.type = new char('\0');
        train.freeS = new char('\0');
        train.freeC = new char('\0');
        train.freeV = new char('\0');
        train.reservedS = new char('\0');
        train.reservedC = new char('\0');
        train.reservedV = new char('\0');
        route.departure = new char('\0');
        route.hour_dep = new char('\0');
        route.min_dep = new char('\0');
        route.arrive = new char('\0');
        route.hour_arr = new char('\0');
        route.min_arr = new char('\0');
    }
    ~TrainSchedule()
    {
        delete[] train.type;
        train.type = nullptr;
        delete[] train.freeS;
        train.freeS = nullptr;
        delete[] train.freeS;
        train.freeC = nullptr;
        delete[] train.freeS;
        train.freeV = nullptr;
        delete[] train.reservedS;
        train.reservedS = nullptr;
        delete[] train.reservedC;
        train.reservedC = nullptr;
        delete[] train.reservedV;
        train.reservedV = nullptr;
        delete[] route.departure;
        route.departure = nullptr;
        delete[] route.hour_dep;
        route.hour_dep = nullptr;
        delete[] route.min_dep;
        route.min_dep = nullptr;
        delete[] route.arrive;
        route.arrive = nullptr;
        delete[] route.hour_arr;
        route.hour_arr = nullptr;
        delete[] route.min_arr;
        route.min_arr = nullptr;
    }
    void inputTrains();
    void inputDestinations();
    void tableMiddle();

    TrainSchedule *Remove(TrainSchedule *PTrainScheduleDelete, int index, int *size_)
    {
        int size_delete;
        size_delete = *size_;
        if (index < 0 || index > size_delete - 1)
        {
            cout << "\tИндекс за границами массива." << endl;
            return NULL;
        }

        TrainSchedule *tmp;
        tmp = new TrainSchedule[size_delete];
        for (int i = 0; i < size_delete; i++)
        {
            strcpy(tmp[i].train.type, PTrainScheduleDelete[i].train.type);
            strcpy(tmp[i].train.freeS, PTrainScheduleDelete[i].train.freeS);
            strcpy(tmp[i].train.freeC, PTrainScheduleDelete[i].train.freeC);
            strcpy(tmp[i].train.freeV, PTrainScheduleDelete[i].train.freeV);
            strcpy(tmp[i].train.reservedS, PTrainScheduleDelete[i].train.reservedS);
            strcpy(tmp[i].train.reservedC, PTrainScheduleDelete[i].train.reservedC);
            strcpy(tmp[i].train.reservedV, PTrainScheduleDelete[i].train.reservedV);
            strcpy(tmp[i].route.departure, PTrainScheduleDelete[i].route.departure); ////
            strcpy(tmp[i].route.hour_dep, PTrainScheduleDelete[i].route.hour_dep);
            strcpy(tmp[i].route.min_dep, PTrainScheduleDelete[i].route.min_dep);
            strcpy(tmp[i].route.arrive, PTrainScheduleDelete[i].route.arrive);
            strcpy(tmp[i].route.hour_arr, PTrainScheduleDelete[i].route.hour_arr);
            strcpy(tmp[i].route.min_arr, PTrainScheduleDelete[i].route.min_arr);
        }
        delete[] PTrainScheduleDelete;

        PTrainScheduleDelete = new TrainSchedule[size_delete - 1];
        for (int i = 0, j = 0; i < size_delete; i++, j++)
        {
            if (i == index)
                i++;

            strcpy(PTrainScheduleDelete[j].train.type, tmp[i].train.type);
            strcpy(PTrainScheduleDelete[j].train.freeS, tmp[i].train.freeS);
            strcpy(PTrainScheduleDelete[j].train.freeC, tmp[i].train.freeC);
            strcpy(PTrainScheduleDelete[j].train.freeV, tmp[i].train.freeV);
            strcpy(PTrainScheduleDelete[j].train.reservedS, tmp[i].train.reservedS);
            strcpy(PTrainScheduleDelete[j].train.reservedC, tmp[i].train.reservedC);
            strcpy(PTrainScheduleDelete[j].train.reservedV, tmp[i].train.reservedV);
            strcpy(PTrainScheduleDelete[j].route.departure, tmp[i].route.departure); ////
            strcpy(PTrainScheduleDelete[j].route.hour_dep, tmp[i].route.hour_dep);
            strcpy(PTrainScheduleDelete[j].route.min_dep, tmp[i].route.min_dep);
            strcpy(PTrainScheduleDelete[j].route.arrive, tmp[i].route.arrive);
            strcpy(PTrainScheduleDelete[j].route.hour_arr, tmp[i].route.hour_arr);
            strcpy(PTrainScheduleDelete[j].route.min_arr, tmp[i].route.min_arr);
        }
        (*size_)--;
        size_delete = *size_;
        delete[] tmp;
        return PTrainScheduleDelete;
    }
    int Save(const char *fileName, TrainSchedule *PTrainScheduleSave, int size_)
    {
        size_t size_data;
        FILE *file = fopen(fileName, "w+b");
        fseek(file, 0, SEEK_SET);
        fwrite(&size_, sizeof(int), 1, file);
        for (int i = 0; i < size_; i++)
        {
            size_data = strlen((PTrainScheduleSave + i)->train.type) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->train.type, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->train.freeS) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->train.freeS, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->train.freeC) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->train.freeC, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->train.freeV) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->train.freeV, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->train.reservedS) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->train.reservedS, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->train.reservedC) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite(&(PTrainScheduleSave + i)->train.reservedC, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->train.reservedV) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite(&(PTrainScheduleSave + i)->train.reservedV, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->route.departure) + 1; /////////////////
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->route.departure, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->route.hour_dep) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->route.hour_dep, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->route.min_dep) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->route.min_dep, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->route.arrive) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->route.arrive, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->route.hour_arr) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->route.hour_arr, sizeof(char), size_data, file);
            size_data = strlen((PTrainScheduleSave + i)->route.min_arr) + 1;
            fwrite(&size_data, sizeof(int), 1, file);
            fwrite((PTrainScheduleSave + i)->route.min_arr, sizeof(char), size_data, file);
        }
        fclose(file);
        return 1;
    }

    TrainSchedule *Load(const char *fileName, int *size)
    {
        TrainSchedule *PTrainScheduleLoad;
        FILE *file = fopen(fileName, "r+b");
        if (!file)
        {
            cout << "\tОШИБКА! Файл с именем " << fileName << " не существует." << endl;
            return NULL;
        }
        else
        {
            cout << endl
                 << "\tДанные успешно загружены с файла. (" << FILE_NAME << ")" << endl;
        }
        int size_load;
        size_t size_data;
        fseek(file, 0, SEEK_SET);
        fread(&size_load, sizeof(int), 1, file);
        PTrainScheduleLoad = new TrainSchedule[size_load];
        for (int i = 0; i < size_load; i++)
        {
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.type, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.freeS, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.freeC, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.freeV, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.reservedS, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.reservedC, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->train.reservedV, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file); /////////////////////////////////////////
            fread((PTrainScheduleLoad + i)->route.departure, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->route.hour_dep, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->route.min_dep, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->route.arrive, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->route.hour_arr, sizeof(char), size_data, file);
            fread(&size_data, sizeof(int), 1, file);
            fread((PTrainScheduleLoad + i)->route.min_arr, sizeof(char), size_data, file);
        }
        fclose(file);
        *size = size_load;
        return PTrainScheduleLoad;
    }
};

void TrainSchedule::inputTrains()
{
    int _reservedS;
    int _reservedC;
    int _reservedV;
    int _freeS;
    int _freeC;
    int _freeV;
    char str1[10];
    char str2[10];
    char str3[10];
    cout << "\t------------------------------" << endl;
    cout << "\tДанные поезду:";
    do
    {
        cout << endl
             << "\tТип поезда (номер):" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        cin >> train.type;

    } while (train.type[0] == '\0' || (int)strlen(train.type) > 7);

    // 5 вагонов плацкарт * (54 мест) = (270 мест)
    do
    {
        do
        {
            cout << endl
                 << "\tКоличество зарезервированных плацкартный мест (0 - 270):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> train.reservedS;

        } while (train.reservedS[0] == '\0' || (int)strlen(train.reservedS) > 3);
        _reservedS = atoi(train.reservedS);

        if (_reservedS > 270)
        {
            cout << endl
                 << "\tКоличество зарезервированных плацкартный мест" << endl;
            cout << "\tне должно превышать количества имеющихся мест." << endl;
        }

    } while (_reservedS < 0 || _reservedS > 270);
    _freeS = 270 - _reservedS;
    sprintf(str1, "%d", _freeS);
    strcpy(train.freeS, str1);

    // 8 вагонов купе * (36 мест) = (288 мест)
    do
    {
        do
        {
            cout << endl
                 << "\tКоличество зарезервированных купейных мест (0 - 288):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> train.reservedC;

        } while (train.reservedC[0] == '\0' || (int)strlen(train.reservedC) > 3);
        _reservedC = atoi(train.reservedC);

        if (_reservedC > 288)
        {
            cout << endl
                 << "\tКоличество зарезервированных купейных мест" << endl;
            cout << "\tне должно превышать количества имеющихся мест." << endl;
        }

    } while (_reservedC < 0 || _reservedC > 288);
    _freeC = 288 - _reservedC;
    sprintf(str2, "%d", _freeC);
    strcpy(train.freeC, str2);

    // 1 вагон спальный = (24 места)
    do
    {
        do
        {
            cout << endl
                 << "\tКоличество зарезервированных люкс мест (0 - 24):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> train.reservedV;

        } while (train.reservedV[0] == '\0' || (int)strlen(train.reservedV) > 2);
        _reservedV = atoi(train.reservedV);

        if (_reservedV > 24)
        {
            cout << endl
                 << "\tКоличество зарезервированных люкс мест" << endl;
            cout << "\tне должно превышать количества имеющихся мест." << endl;
        }

    } while (_reservedV < 0 || _reservedV > 24);
    _freeV = 24 - _reservedV;
    sprintf(str3, "%d", _freeV);
    strcpy(train.freeV, str3);
}

void TrainSchedule::inputDestinations()
{
    int _hour_dep;
    int _min_dep;
    int _hour_arr;
    int _min_arr;
    cout << endl;
    cout << "\t-------------------------------------" << endl;
    cout << "\tДанные по маршруту следования поезда:" << endl;
    do
    {
        cout << endl
             << "\tОтправление от станции (начальный пункт следования):" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        cin >> route.departure;

    } while (route.departure[0] == '\0' || (int)strlen(route.departure) > 15);

    cout << endl;
    cout << "\t.   .   .   .   .   .   .   .   .   .   .   ." << endl;
    cout << endl;

    cout << "\tВремя отправления поезда с начальной станции:";
    do
    {
        do
        {
            cout << endl
                 << "\tЧасов (0 - 23):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> route.hour_dep;

        } while (route.hour_dep[0] == '\0' || (int)strlen(route.hour_dep) > 2);
        _hour_dep = atoi(route.hour_dep);

        if (_hour_dep > 23 || _hour_dep < 0)
        {
            cout << endl
                 << "\tОшибка ввода!!!" << endl;
        }

    } while (_hour_dep < 0 || _hour_dep > 23);

    do
    {
        do
        {
            cout << endl
                 << "\tМинут (0 - 59):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> route.min_dep;

        } while (route.min_dep[0] == '\0' || (int)strlen(route.min_dep) > 2);
        _min_dep = atoi(route.min_dep);

        if (_min_dep > 59 || _hour_dep < 0)
        {
            cout << endl
                 << "\tОшибка ввода!!!" << endl;
        }

    } while (_min_dep < 0 || _min_dep > 59);

    cout << endl;
    cout << "\t................................................" << endl;
    do
    {
        cout << endl
             << "\tПрибытие на станцию (конечный пункт следования):" << endl;
        cout << "     |" << endl;
        cout << "     '->";
        cin >> route.arrive;

    } while (route.arrive[0] == '\0' || (int)strlen(route.arrive) > 15);

    cout << endl;
    cout << "\t.   .   .   .   .   .   .   .   .   .   .   ." << endl;
    cout << endl;

    cout << "\tВремя прибытия поезда на конечную станции:";
    do
    {
        do
        {
            cout << endl
                 << "\tЧасов (0 - 23):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> route.hour_arr;

        } while (route.hour_arr[0] == '\0' || (int)strlen(route.hour_arr) > 2);
        _hour_arr = atoi(route.hour_arr);

        if (_hour_arr > 23 || _hour_arr < 0)
        {
            cout << endl
                 << "\tОшибка ввода!!!" << endl;
        }

    } while (_hour_arr < 0 || _hour_arr > 23);

    do
    {
        do
        {
            cout << endl
                 << "\tМинут (0 - 59):" << endl;
            cout << "     |" << endl;
            cout << "     '->";
            cin >> route.min_arr;

        } while (route.min_arr[0] == '\0' || (int)strlen(route.min_arr) > 2);
        _min_arr = atoi(route.min_arr);

        if (_min_arr > 59 || _min_arr < 0)
        {
            cout << endl
                 << "\tОшибка ввода!!!" << endl;
        }
    } while (_min_arr < 0 || _min_arr > 59);
}

void tableUp(void)
{
    cout << " .____________________________________________________________________________." << endl;
    cout << " |   |         |                                        |   Количество мест   |" << endl;
    cout << " | № | Поезд № |               Информация               | Занятых | Свободных |" << endl;
    cout << " |---|---------|----------------------------------------|---------|-----------|" << endl;
}

void TrainSchedule::tableMiddle()
{
    cout << " |   |         |  1. Маршрут следования:   -   -   -    |---------|-----------|" << endl;
    cout << " |   |         | " << right << setw(18) << route.departure << " - " << setw(17) << left << route.arrive << " |---------|-----------|" << endl;
    cout << " |   | " << setw(7) << train.type << " |  2. Время:   -   -   -   -   -   -   - |---------------------|" << endl;
    cout << " |   |         |  Отправления от станции >> " << right << setw(15) << route.departure << " в " << setw(2) << route.hour_dep << ":" << setw(2) << route.min_dep << "           |" << endl;
    cout << " |   |         |  Прибытие на    станцию << " << right << setw(15) << route.arrive << " в " << setw(2) << route.hour_arr << ":" << setw(2) << route.min_arr << "           |" << endl;
    cout << " |   |         |  3. Места в поезде:   -   -   -   -   -|---------------------|" << endl;
    cout << " |   |         |  Плацкартных -->                       | " << setw(7) << train.reservedS << " | " << setw(9) << train.freeS << " |" << endl;
    cout << " |   |         |  Купейных   -->                        | " << setw(7) << train.reservedC << " | " << setw(9) << train.freeC << " |" << endl;
    cout << " |   |         |  Места люкс -->                        | " << setw(7) << train.reservedV << " | " << setw(9) << train.freeV << " |" << endl;
}

void tableDown(void)
{
    cout << " |___|_________|________________________________________|_________|___________|" << endl;
}

int main()
{
    int i1 = GetConsoleCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char enter; // для подтверждения выхода в главное меню
    char repeat;
    int option;
    int menu;

    int find; // для поиска
    int available;
    int c_note = 0; // счетчик записей
    int i;

    char *train_delete;
    char *arrive_;
    train_delete = new char[81];
    arrive_ = new char[81];

    TrainSchedule *PTrainScheduleA;
    TrainSchedule *PTrainScheduleATmp;

    //=======================================================================================
    system("cls");
    equal(80);
    printf("\n");
    tabs(9);
    printf("\n");
    apostrophe(80);
    printf("\n");

    PTrainScheduleA = new TrainSchedule[1];
    if (!PTrainScheduleA)
        exit(0);
    PTrainScheduleA = PTrainScheduleA->Load(FILE_NAME, &c_note);

    printf("\n");
    dotdot(80);
    printf("\n");
    tabs(9);
    printf("\n");
    equal(80);
    printf("\n\tДля продолжения нажмите-<ENTER>");
    getch();
    //=======================================================================================

    do
    {
        system("cls");
        equal(80);
        cout << endl;
        tabs(9);
        cout << endl;
        apostrophe(80);
        cout << endl;
        cout << "\t\t\t   ***| Расписание поездов |***" << endl
             << endl
             << endl;
        cout << "\t________________________| Главное меню |________________________________" << endl;
        cout << "\t   Выберите ПУНКТ меню:" << endl;
        cout << "\t1. Добавить поезд в расписание." << endl;
        cout << "\t2. Показать расписание поездов." << endl;
        cout << "\t3. Удалить поезд с расписания." << endl;
        cout << "\t4. Поиск поездов по расписанию." << endl;
        cout << "\t5. Сохранить информацию в файл." << endl;
        cout << "\t6. Загрузить информацию из файла." << endl;
        cout << "\t7.   | ВыхоД |";
        do
        {
            menu = 0;
            menu = getValueInt();

        } while (menu <= 0);

        cout << endl;

        switch (menu)
        {
        case 1: // добавить абонентов
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 1 пункт меню |_______" << endl
                 << endl;
            cout << "\t1. Ввод записи в расписания (добавить)." << endl;
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

                    PTrainScheduleATmp = new TrainSchedule[c_note];
                    for (i = 0; i < c_note; i++)
                    {
                        strcpy(PTrainScheduleATmp[i].train.type, PTrainScheduleA[i].train.type);
                        strcpy(PTrainScheduleATmp[i].train.freeS, PTrainScheduleA[i].train.freeS);
                        strcpy(PTrainScheduleATmp[i].train.freeC, PTrainScheduleA[i].train.freeC);
                        strcpy(PTrainScheduleATmp[i].train.freeV, PTrainScheduleA[i].train.freeV);
                        strcpy(PTrainScheduleATmp[i].train.reservedS, PTrainScheduleA[i].train.reservedS);
                        strcpy(PTrainScheduleATmp[i].train.reservedC, PTrainScheduleA[i].train.reservedC);
                        strcpy(PTrainScheduleATmp[i].train.reservedV, PTrainScheduleA[i].train.reservedV);
                        strcpy(PTrainScheduleATmp[i].route.departure, PTrainScheduleA[i].route.departure); ////
                        strcpy(PTrainScheduleATmp[i].route.hour_dep, PTrainScheduleA[i].route.hour_dep);
                        strcpy(PTrainScheduleATmp[i].route.min_dep, PTrainScheduleA[i].route.min_dep);
                        strcpy(PTrainScheduleATmp[i].route.arrive, PTrainScheduleA[i].route.arrive);
                        strcpy(PTrainScheduleATmp[i].route.hour_arr, PTrainScheduleA[i].route.hour_arr);
                        strcpy(PTrainScheduleATmp[i].route.min_arr, PTrainScheduleA[i].route.min_arr);
                    }
                    delete[] PTrainScheduleA;

                    PTrainScheduleA = new TrainSchedule[c_note + 1];
                    for (i = 0; i < c_note; i++)
                    {
                        strcpy(PTrainScheduleA[i].train.type, PTrainScheduleATmp[i].train.type);
                        strcpy(PTrainScheduleA[i].train.freeS, PTrainScheduleATmp[i].train.freeS);
                        strcpy(PTrainScheduleA[i].train.freeC, PTrainScheduleATmp[i].train.freeC);
                        strcpy(PTrainScheduleA[i].train.freeV, PTrainScheduleATmp[i].train.freeV);
                        strcpy(PTrainScheduleA[i].train.reservedS, PTrainScheduleATmp[i].train.reservedS);
                        strcpy(PTrainScheduleA[i].train.reservedC, PTrainScheduleATmp[i].train.reservedC);
                        strcpy(PTrainScheduleA[i].train.reservedV, PTrainScheduleATmp[i].train.reservedV);
                        strcpy(PTrainScheduleA[i].route.departure, PTrainScheduleATmp[i].route.departure); ////
                        strcpy(PTrainScheduleA[i].route.hour_dep, PTrainScheduleATmp[i].route.hour_dep);
                        strcpy(PTrainScheduleA[i].route.min_dep, PTrainScheduleATmp[i].route.min_dep);
                        strcpy(PTrainScheduleA[i].route.arrive, PTrainScheduleATmp[i].route.arrive);
                        strcpy(PTrainScheduleA[i].route.hour_arr, PTrainScheduleATmp[i].route.hour_arr);
                        strcpy(PTrainScheduleA[i].route.min_arr, PTrainScheduleATmp[i].route.min_arr);
                    }
                    delete[] PTrainScheduleATmp;

                    if (PTrainScheduleA)
                    {
                        cout << "\tЗапись № " << c_note << endl;
                        PTrainScheduleA[c_note].inputTrains();
                        PTrainScheduleA[c_note].inputDestinations();
                        c_note++;
                    }

                    cout << "\t";
                    dotdot(40);
                    cout << endl
                         << "\tY - Ввести еще одну запись (добавить).";
                    cout << endl
                         << "     |  Q - Выход в Главное меню.";
                    cout << endl
                         << "     '->";
                    repeat = getche();
                } while (repeat == 'y' || repeat == 'Y');
            }
        }
        break;

        case 2: // просмотр поездов
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 2 пункт меню |_______" << endl
                 << endl;

            cout << "  Расписание поездов." << endl;
            tableUp();
            for (i = 0; i < c_note; i++)
            {
                cout << " | " << i << " |         |                                        |---------|-----------|" << endl;
                PTrainScheduleA[i].tableMiddle();
                if (i != c_note - 1)
                    cout << " |---|--------------------------------------------------|---------------------|" << endl;
            }
            tableDown();

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

        case 3: // удаление поезда с рассписания
        {
            dash(80);
            cout << endl;
            cout << "\t\t      _______| Выбран 3 пункт меню |_______" << endl
                 << endl;
            cout << "\t1. Удалить поезд с расписания." << endl;
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
                cout << "\tВведите для удаления из расписания:" << endl;
                cout << "\t";

                do
                {
                    cout << endl
                         << "\tНомер поезда (тип):" << endl;
                    cout << "     |" << endl;
                    cout << "     '->";
                    cin >> train_delete;

                } while (train_delete[0] == '\0' || (int)strlen(train_delete) > 7);

                for (i = 0; i < c_note; i++)
                {
                    if (!strcmp(PTrainScheduleA[i].train.type, train_delete))
                    {
                        available = i;
                        PTrainScheduleA = PTrainScheduleA->Remove(PTrainScheduleA, available, &c_note);
                        cout << endl
                             << "\tПоезд удален с расписания." << endl;
                        break;
                    }
                }

                if (available == -1)
                    cout << endl
                         << "\tПоезд с таким номером не найден." << endl;

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

        case 4:
        {
            do
            {
                cout << endl;
                dash(80);
                cout << endl;
                cout << "\t\t      _______| Выбран 4 пункт меню |_______" << endl
                     << endl;
                cout << "\t   Выберите поиск поездов:" << endl;
                cout << "\t1. По конечной станции." << endl;
                cout << "\t2. По конечной станции и после заданного часа." << endl;
                cout << "\t3. По конечной станции и наличию свободных мест." << endl;
                cout << "\t4.   | Отмена |"; // оставить как есть

                do // защита ввода
                {
                    option = 0;
                    option = getValueInt();

                    if (option != 1 && option != 2 && option != 3 && option != 4)
                    {
                        cout << endl
                             << "\tНекорректный ввод (Действие = 4 -отмена).";
                        cout << endl
                             << "\tПожалуйста сделайте выбор.";
                    }
                } while (option != 1 && option != 2 && option != 3 && option != 4);

                find = -1;

                if (option == 1)
                {
                    cout << endl;
                    cout << "\tВведите данные для нахождения в расписании:" << endl;
                    do
                    {
                        cout << endl
                             << "\tВведите названия конечной станции:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin >> arrive_;

                    } while (arrive_[0] == '\0' || (int)strlen(arrive_) > 15);

                    cout << endl
                         << "  Поиск в расписании поездов." << endl;
                    tableUp();
                    for (i = 0; i < c_note; i++)
                    {
                        if (strcmp(PTrainScheduleA[i].route.arrive, arrive_) == 0)
                        {
                            find = 1;
                            cout << " | " << i << " |         |                                        |---------|-----------|" << endl;
                            PTrainScheduleA[i].tableMiddle();
                            if (i != c_note - 1)
                                cout << " |---|---------|----------------------------------------|---------------------|" << endl;
                        }
                    }
                    tableDown();

                    if (find == -1)
                        cout << endl
                             << "\tПоезда с такой конечной станцией не найдены." << endl;
                }
                if (option == 2)
                {
                    int hour;
                    cout << endl;
                    cout << "\tВведите данные для нахождения в расписании:" << endl;
                    do
                    {
                        cout << endl
                             << "\tВведите названия конечной станции:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin >> arrive_;

                    } while (arrive_[0] == '\0' || (int)strlen(arrive_) > 15);

                    do
                    {
                        cout << endl
                             << "\tВведите час после которого произвести поиск:" << endl;
                        hour = 0;
                        hour = getValueInt();

                    } while (hour < 0 || hour > 23);

                    cout << endl
                         << "  Поиск в расписании поездов." << endl;
                    tableUp();
                    for (i = 0; i < c_note; i++)
                    {
                        if ((strcmp(PTrainScheduleA[i].route.arrive, arrive_) == 0) && (hour < atoi(PTrainScheduleA[i].route.hour_dep)))
                        {
                            find = 1;
                            cout << " | " << i << " |         |                                        |---------|-----------|" << endl;
                            PTrainScheduleA[i].tableMiddle();
                            if (i != c_note - 1)
                                cout << " |---|--------------------------------------------------|--------------------------|" << endl;
                        }
                    }
                    tableDown();

                    if (find == -1)
                    {
                        cout << endl
                             << "\tПоезда с такой конечной станцей не найдены" << endl;
                        cout << "\t и отправленных от указанного часа нет." << endl;
                    }
                }
                if (option == 3)
                {
                    int seats;
                    int sumseats;
                    cout << endl;
                    cout << "\tВведите данные для нахождения в расписании:" << endl;
                    do
                    {
                        cout << endl
                             << "\tВведите названия конечной станции:" << endl;
                        cout << "     |" << endl;
                        cout << "     '->";
                        cin >> arrive_;

                    } while (arrive_[0] == '\0' || (int)strlen(arrive_) > 15);

                    do
                    {
                        cout << endl
                             << "\tВведите необходимое количество свободных мест:" << endl;
                        seats = 0;
                        seats = getValueInt();

                    } while (seats < 0 || seats > 1000);

                    cout << endl
                         << "  Поиск в расписание поездов." << endl;
                    tableUp();
                    for (i = 0; i < c_note; i++)
                    {
                        sumseats = 0;
                        sumseats = atoi(PTrainScheduleA[i].train.freeS) + atoi(PTrainScheduleA[i].train.freeC) + atoi(PTrainScheduleA[i].train.freeV);
                        if ((strcmp(PTrainScheduleA[i].route.arrive, arrive_) == 0) && (seats < sumseats))
                        {
                            find = 1;
                            cout << " | " << i << " |         |                                        |---------|-----------|" << endl;
                            PTrainScheduleA[i].tableMiddle();
                            if (i != c_note - 1)
                                cout << " |---|--------------------------------------------------|--------------------------|" << endl;
                        }
                    }
                    tableDown();

                    if (find == -1)
                    {
                        cout << endl
                             << "\tПоезда с такой конечной станцией не найдены" << endl;
                        cout << "\t необходимого количества свободных мест нет." << endl;
                    }
                }
                if (option == 4)
                {
                    break;
                }

                cout << endl;
                dotdot(80);
                cout << endl;
                tabs(9);
                cout << endl;
                equal(80);
                cout << endl
                     << "\tY - Повторить поиск.";
                cout << endl
                     << "     |  Q - Выход в Главное меню.";
                cout << endl
                     << "     '->";
                repeat = getche();
            } while (repeat == 'y' || repeat == 'Y');
        }
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
                if (PTrainScheduleA->Save(FILE_NAME, PTrainScheduleA, c_note))
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
                cout << endl;
                if (PTrainScheduleA)
                    delete[] PTrainScheduleA;
                PTrainScheduleA = PTrainScheduleA->Load(FILE_NAME, &c_note);

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
    } while (menu != 7);

    if (PTrainScheduleA)
        delete[] PTrainScheduleA;

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
