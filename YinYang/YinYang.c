#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

#define N 9 // размер поля по вертикали
#define M 9 // размер поля по горизонтали
#define TASK 4 // кол-во созданных задач

_Bool checkSolution(char arr[N][M]);
_Bool autoCheck(char arr[N][M], int i, int j, char cell);
void printHeader(char userName[], int taskNum, int menuNav);
void printField(char arr[N][M]);
void printMenu();
void printActMenu();
int fileReading(int task_num, char mas[N][M], int sol);
int countMaxSteps(char arr[N][M]);

_Bool false = 0;
_Bool true = 1;
char userName[50];
int userScore = 0, userSuccess = 0, userSteps = 0, maxSteps1, maxSteps2, maxSteps3;

// главная функция программы
int main()
{
    // локализация
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // объявление переменных
    int taskNum = -1, currAct = -1, menuNav = -1;
    char board[N][M], solution[N][M];
    _Bool sol = false;

    // приветствие, ввод имени
    printf("Здравствуйте! Вы запустили игру YinYang!\nВведите ваше имя: ");
    scanf("%s", &userName);

    // диалог с пользователем
    while (1)
    {
        printHeader(userName, taskNum, -1);

        printMenu();

        printf("Введите номер пункта: ");
        scanf("%d", &menuNav);

        if (menuNav == 1) 
        {
            printHeader(userName, taskNum, menuNav);
            // выбор номера задачи
            printf("Введите номер варианта задачи (1-%d): ", TASK);
            int oldTaskNum = taskNum;
            scanf("%d", &taskNum);

            if (taskNum == oldTaskNum) 
            {
                printf("Это задание итак уже выбрано\n");
                system("pause");
            }
            else if (taskNum < 1 || taskNum > TASK) 
            {
                printf("Ошибка ввода номера заданиия\n");
                taskNum = -1;
                system("pause");
            }
            else {
                // чтение условия из файла
                if (fileReading(taskNum, board, false) != 0) 
                {
                    printf("Ошибка чтения условия задачи");
                    system("pause");
                }
                else {
                    userSteps = 0;
                    maxSteps1 = countMaxSteps(board);
                    maxSteps2 = maxSteps1 * 1.2 + 1;
                    maxSteps3 = maxSteps1 * 1.5 + 2;

                    printf("В случае верного решения вы получите баллы, в зависимости от кол-ва шагов решения:\n<=%d шага(ов) - 5 баллов\n%d-%d шага(ов) - 4 балла\n%d-%d шага(ов) - 3 балла\n>%d шага(ов) - 2 балла.\n", maxSteps1, maxSteps1, maxSteps2, maxSteps2, maxSteps3, maxSteps3);

                    printf("Выбрана задача номер %d\n", taskNum);
                    system("pause");
                }
            }
        }
        else if (menuNav == 2) 
        {
            if (taskNum < 1 || taskNum > TASK) 
            {
                printf("Вы не выбрали задание или задания с введенным номером не существует\n");
                system("pause");
            }
            else {

                // чтение условия из файла
                if (fileReading(taskNum, board, false) != 0) 
                {
                    printf("Ошибка чтения из файла");
                    system("pause");
                }
                else {

                    int x, y;
                    char cell;

                    while (1)
                    {
                        printHeader(userName, taskNum, menuNav);
                        printField(board);
                        printActMenu();

                        printf("Ваш выбор: ");
                        scanf("%d", &currAct);

                        if (currAct == 1)
                        {
                            printf("Выберите цвет ('0'-черный '1'-белый '.'-пусто): ");
                            scanf(" %c", &cell);

                            if (cell != '0' && cell != '1' && cell != '.') 
                            {
                                printf("Ошибка ввода цвета\n");
                                //break;
                            }
                            else 
                            {

                                while (1)
                                {
                                    printHeader(userName, taskNum, menuNav);
                                    printField(board);

                                    printf("Вы выбрали ввод кружков, цвет - %s\n", cell == '1' ? "белый" : "черный");

                                    printf("Ввод координат 'y x' (строка и столбец), начиная с [0;0]. Для выхода введите 99 в любую из координат.\nШаг %d, ваш ввод: ", userSteps);
                                    scanf("%d %d", &x, &y);

                                    if (x == 99 || y == 99) 
                                    {
                                        break;
                                    }
                                    else if (x < 0 || x>8 || y < 0 || y>8 || (cell != '1' && cell != '0' && cell != '.')) 
                                    {
                                        printf("Ошибка ввода координат\n");
                                        system("pause");
                                    }
                                    else {
                                        if (cell != '.') 
                                        {
                                            if (autoCheck(board, x, y, cell)) 
                                            {
                                                userSteps++;
                                                board[x][y] = cell;
                                            }
                                            else {
                                                printf("Нельзя ввести кружок - нет связи цвета\n");
                                                system("pause");
                                            }
                                        }
                                        else 
                                        {
                                            userSteps++;
                                            board[x][y] = cell;
                                        }
                                    }
                                }
                            }
                        }
                        else if (currAct == 2)
                        {
                            if (checkSolution(board)) 
                            {
                                int oldScore = userScore;

                                userSuccess += 1;

                                if (userSteps <= maxSteps1)
                                    userScore += 5;
                                else if (userSteps <= maxSteps2)
                                    userScore += 4;
                                else if (userSteps <= maxSteps3)
                                    userScore += 3;
                                else
                                    userScore += 2;

                                printf("Головоломка решена!\nВы решили головоломок - %d\nЗа данное решение вам добавлено баллов - %d\nВсего вы набрали баллов - %d\n", userSuccess, userScore - oldScore, userScore);
                                userSteps = 0;
                                system("pause");
                                break;
                            }
                            else 
                            {
                                printf("Головоломка не решена :(\n");
                                system("pause");
                            }
                        }
                        else if (currAct == 3)
                        {
                            fileReading(taskNum, solution, true);
                            printf("Верное решение головоломки:\n\n");
                            printField(solution);
                            printf("\nТолько не списывай точь-в-точь :)\n");
                            system("pause");
                        }
                        else if (currAct == 4) 
                        {
                            printf("Ваше решение не сохранится, вы уверены?\nВведите '4' ещё раз для выхода: ");
                            scanf("%d", &currAct);

                            if (currAct == 4)
                                break;
                        }
                        else 
                        {
                            printf("Ошибка выбора пункта действия\n");
                            system("pause");
                        }
                    }
                }
            }
        }
        else if (menuNav == 3) 
        {
            printHeader(userName, taskNum, menuNav);
        }
        else if (menuNav == 4) 
        {
            printf("Это путь воина");
            printHeader(userName, taskNum, menuNav);
        }
        else if (menuNav == 5) 
        {
            printHeader(userName, taskNum, menuNav);
            return 0;
        }
        else 
        {
            printf("Ошибка ввода значения пункта меню\n");
        }
    }

    return 0;
}

// проверка решения
_Bool checkSolution(char arr[N][M])
{
    // проверка соединений
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!(arr[i][j] == '0' || arr[i][j] == '1'))
                return false;
            if (i > 0)
                if (arr[i][j] == arr[i - 1][j])
                    continue;
            if (j > 0)
                if (arr[i][j] == arr[i][j - 1])
                    continue;
            if (i < N - 1)
                if (arr[i][j] == arr[i + 1][j])
                    continue;
            if (j < M - 1)
                if (arr[i][j] == arr[i][j + 1])
                    continue;
            return false;
        }
    }

    // проверка скоплений
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < M - 1; j++)
        {
            if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 1][j + 1])
                return false;
        }
    }
    return true;
}

// автопроверка соединений при вводе
_Bool autoCheck(char arr[N][M], int i, int j, char cell)
{
    // проверка на то, все ли точки вокруг
    int maxDot = 0, dot = 0;

    if (i > 0) 
    {
        maxDot++;
        if (arr[i - 1][j] == '.')
            dot++;
    }
    if (j > 0) 
    {
        maxDot++;
        if (arr[i][j - 1] == '.')
            dot++;
    }
    if (i < N - 1) 
    {
        maxDot++;
        if (arr[i + 1][j] == '.')
            dot++;
    }
    if (j < M - 1) 
    {
        maxDot++;
        if (arr[i][j + 1] == '.')
            dot++;
    }

    if (maxDot == dot)
        return true;

    // вокруг есть хоть 1 кружок, значит должна быть связь
    if (i > 0)
        if (cell == arr[i - 1][j])
            return true;
    if (j > 0)
        if (cell == arr[i][j - 1])
            return true;
    if (i < N - 1)
        if (cell == arr[i + 1][j])
            return true;
    if (j < M - 1)
        if (cell == arr[i][j + 1])
            return true;

    return false;
}

// вывод игрового поля и пунктов меню
void printHeader(char userName[], int taskNum, int menuNav)
{
    system("cls");
    printf("Игра-головоломка YinYang (Инь-Янь)\t\t\tПользователь: %s\t\t\tЗадача: ", userName);
    if (taskNum > 0)
        printf("выбран номер %d", taskNum);
    else
        printf("не выбрана");

    printf("\n\n\n");

    if (menuNav == 1) 
    {
        printf("Выбран пункт - ввод номера задания:\n");
    }
    else if (menuNav == 2) 
    {
        printf("Выбран пункт - решение задания:\n");
    }
    else if (menuNav == 3) 
    {
        printf("Выбран пункт - правила игры:\n");
        printf("Расставить черные (0) и белые (1) кружки в поле так, чтобы соблюдались условия:\n--Кружки каждого цвета должны быть связаны между собой по горизонтали или по вертикали (иметь такой же цвет) рядом.\n--Групп, размером 2х2 или более, состоящих из кружков одного цвета, быть не должно.\nПри соблюдении данных правил головоломка будет считаться решённой верно.\n");
        system("pause");
    }
    else if (menuNav == 4) 
    {
        printf("Выбран пункт - просмотр достижений:\n");
        printf("%s, вы решили задач - %d и набрали баллов - %d\n", userName, userSuccess, userScore);
        system("pause");
    }
    else if (menuNav == 5) 
    {
        printf("До свидания, %s! Вы решили задач %d и набрали баллов %d!\n", userName, userSuccess, userScore);
    }
}

// вывод игрового поля
void printField(char arr[N][M])
{
    printf("_|");

    for (int i = 0; i < N; i++)
    {
        printf("%d", i);

        if (i != N - 1)
            printf("|");
    }

    printf("\n");

    for (int i = 0; i < N; i++)
    {
        printf("%d|", i);

        for (int j = 0; j < M; j++)
            printf("%c ", arr[i][j]);

        printf("\n");
    }
}

// вывод пунктов меню
void printMenu() //char arr[N][M]
{
    printf("МЕНЮ ДЕЙСТВИЙ:\n");
    printf("1) Выбор задания\n");
    printf("2) Начало игры\n");
    printf("3) Правила игры\n");
    printf("4) Достижения\n");
    printf("5) Выход\n");
}

// вывод пунктов меню действий с полем
void printActMenu()
{
    printf("Выберите действие:\n");
    printf("1) Вставить кружок\n");
    printf("2) Проверить решение\n");
    printf("3) Подсмотреть ответ\n");
    printf("4) Возврат в меню\n");
}
// считывание условия из файла в массив по номеру задачи
int fileReading(int task_num, char mas[N][M], int sol)
{
    char fname[20];

    // название файла в строку по номеру задачи
    if (sol)
        sprintf(fname, "solutions/%d", task_num);
    else
        sprintf(fname, "%d", task_num);

    // открываем поток, обработка ошибок
    FILE* pf;
    pf = fopen(strcat(fname, ".txt"), "r");

    if (pf == NULL) 
    {
        printf("Ошибка при открытии файла\n");
        return -1;
    }

    // считывание из файла в массив
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            fscanf(pf, "%c ", &mas[i][j]);
    }

    // закрываем поток
    fclose(pf);

    return 0;
}

// вычисление max шагов
int countMaxSteps(char arr[N][M])
{
    int maxSteps = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (arr[i][j] == '.')
                maxSteps++;
        }
    }
    return maxSteps;
}
