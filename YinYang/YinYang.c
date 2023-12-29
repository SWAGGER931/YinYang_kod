#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

#define N 9 // ������ ���� �� ���������
#define M 9 // ������ ���� �� �����������
#define TASK 4 // ���-�� ��������� �����

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

// ������� ������� ���������
int main()
{
    // �����������
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ���������� ����������
    int taskNum = -1, currAct = -1, menuNav = -1;
    char board[N][M], solution[N][M];
    _Bool sol = false;

    // �����������, ���� �����
    printf("������������! �� ��������� ���� YinYang!\n������� ���� ���: ");
    scanf("%s", &userName);

    // ������ � �������������
    while (1)
    {
        printHeader(userName, taskNum, -1);

        printMenu();

        printf("������� ����� ������: ");
        scanf("%d", &menuNav);

        if (menuNav == 1) 
        {
            printHeader(userName, taskNum, menuNav);
            // ����� ������ ������
            printf("������� ����� �������� ������ (1-%d): ", TASK);
            int oldTaskNum = taskNum;
            scanf("%d", &taskNum);

            if (taskNum == oldTaskNum) 
            {
                printf("��� ������� ���� ��� �������\n");
                system("pause");
            }
            else if (taskNum < 1 || taskNum > TASK) 
            {
                printf("������ ����� ������ ��������\n");
                taskNum = -1;
                system("pause");
            }
            else {
                // ������ ������� �� �����
                if (fileReading(taskNum, board, false) != 0) 
                {
                    printf("������ ������ ������� ������");
                    system("pause");
                }
                else {
                    userSteps = 0;
                    maxSteps1 = countMaxSteps(board);
                    maxSteps2 = maxSteps1 * 1.2 + 1;
                    maxSteps3 = maxSteps1 * 1.5 + 2;

                    printf("� ������ ������� ������� �� �������� �����, � ����������� �� ���-�� ����� �������:\n<=%d ����(��) - 5 ������\n%d-%d ����(��) - 4 �����\n%d-%d ����(��) - 3 �����\n>%d ����(��) - 2 �����.\n", maxSteps1, maxSteps1, maxSteps2, maxSteps2, maxSteps3, maxSteps3);

                    printf("������� ������ ����� %d\n", taskNum);
                    system("pause");
                }
            }
        }
        else if (menuNav == 2) 
        {
            if (taskNum < 1 || taskNum > TASK) 
            {
                printf("�� �� ������� ������� ��� ������� � ��������� ������� �� ����������\n");
                system("pause");
            }
            else {

                // ������ ������� �� �����
                if (fileReading(taskNum, board, false) != 0) 
                {
                    printf("������ ������ �� �����");
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

                        printf("��� �����: ");
                        scanf("%d", &currAct);

                        if (currAct == 1)
                        {
                            printf("�������� ���� ('0'-������ '1'-����� '.'-�����): ");
                            scanf(" %c", &cell);

                            if (cell != '0' && cell != '1' && cell != '.') 
                            {
                                printf("������ ����� �����\n");
                                //break;
                            }
                            else 
                            {

                                while (1)
                                {
                                    printHeader(userName, taskNum, menuNav);
                                    printField(board);

                                    printf("�� ������� ���� �������, ���� - %s\n", cell == '1' ? "�����" : "������");

                                    printf("���� ��������� 'y x' (������ � �������), ������� � [0;0]. ��� ������ ������� 99 � ����� �� ���������.\n��� %d, ��� ����: ", userSteps);
                                    scanf("%d %d", &x, &y);

                                    if (x == 99 || y == 99) 
                                    {
                                        break;
                                    }
                                    else if (x < 0 || x>8 || y < 0 || y>8 || (cell != '1' && cell != '0' && cell != '.')) 
                                    {
                                        printf("������ ����� ���������\n");
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
                                                printf("������ ������ ������ - ��� ����� �����\n");
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

                                printf("����������� ������!\n�� ������ ����������� - %d\n�� ������ ������� ��� ��������� ������ - %d\n����� �� ������� ������ - %d\n", userSuccess, userScore - oldScore, userScore);
                                userSteps = 0;
                                system("pause");
                                break;
                            }
                            else 
                            {
                                printf("����������� �� ������ :(\n");
                                system("pause");
                            }
                        }
                        else if (currAct == 3)
                        {
                            fileReading(taskNum, solution, true);
                            printf("������ ������� �����������:\n\n");
                            printField(solution);
                            printf("\n������ �� �������� ����-�-���� :)\n");
                            system("pause");
                        }
                        else if (currAct == 4) 
                        {
                            printf("���� ������� �� ����������, �� �������?\n������� '4' ��� ��� ��� ������: ");
                            scanf("%d", &currAct);

                            if (currAct == 4)
                                break;
                        }
                        else 
                        {
                            printf("������ ������ ������ ��������\n");
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
            printf("��� ���� �����");
            printHeader(userName, taskNum, menuNav);
        }
        else if (menuNav == 5) 
        {
            printHeader(userName, taskNum, menuNav);
            return 0;
        }
        else 
        {
            printf("������ ����� �������� ������ ����\n");
        }
    }

    return 0;
}

// �������� �������
_Bool checkSolution(char arr[N][M])
{
    // �������� ����������
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

    // �������� ���������
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

// ������������ ���������� ��� �����
_Bool autoCheck(char arr[N][M], int i, int j, char cell)
{
    // �������� �� ��, ��� �� ����� ������
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

    // ������ ���� ���� 1 ������, ������ ������ ���� �����
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

// ����� �������� ���� � ������� ����
void printHeader(char userName[], int taskNum, int menuNav)
{
    system("cls");
    printf("����-����������� YinYang (���-���)\t\t\t������������: %s\t\t\t������: ", userName);
    if (taskNum > 0)
        printf("������ ����� %d", taskNum);
    else
        printf("�� �������");

    printf("\n\n\n");

    if (menuNav == 1) 
    {
        printf("������ ����� - ���� ������ �������:\n");
    }
    else if (menuNav == 2) 
    {
        printf("������ ����� - ������� �������:\n");
    }
    else if (menuNav == 3) 
    {
        printf("������ ����� - ������� ����:\n");
        printf("���������� ������ (0) � ����� (1) ������ � ���� ���, ����� ����������� �������:\n--������ ������� ����� ������ ���� ������� ����� ����� �� ����������� ��� �� ��������� (����� ����� �� ����) �����.\n--�����, �������� 2�2 ��� �����, ��������� �� ������� ������ �����, ���� �� ������.\n��� ���������� ������ ������ ����������� ����� ��������� �������� �����.\n");
        system("pause");
    }
    else if (menuNav == 4) 
    {
        printf("������ ����� - �������� ����������:\n");
        printf("%s, �� ������ ����� - %d � ������� ������ - %d\n", userName, userSuccess, userScore);
        system("pause");
    }
    else if (menuNav == 5) 
    {
        printf("�� ��������, %s! �� ������ ����� %d � ������� ������ %d!\n", userName, userSuccess, userScore);
    }
}

// ����� �������� ����
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

// ����� ������� ����
void printMenu() //char arr[N][M]
{
    printf("���� ��������:\n");
    printf("1) ����� �������\n");
    printf("2) ������ ����\n");
    printf("3) ������� ����\n");
    printf("4) ����������\n");
    printf("5) �����\n");
}

// ����� ������� ���� �������� � �����
void printActMenu()
{
    printf("�������� ��������:\n");
    printf("1) �������� ������\n");
    printf("2) ��������� �������\n");
    printf("3) ����������� �����\n");
    printf("4) ������� � ����\n");
}
// ���������� ������� �� ����� � ������ �� ������ ������
int fileReading(int task_num, char mas[N][M], int sol)
{
    char fname[20];

    // �������� ����� � ������ �� ������ ������
    if (sol)
        sprintf(fname, "solutions/%d", task_num);
    else
        sprintf(fname, "%d", task_num);

    // ��������� �����, ��������� ������
    FILE* pf;
    pf = fopen(strcat(fname, ".txt"), "r");

    if (pf == NULL) 
    {
        printf("������ ��� �������� �����\n");
        return -1;
    }

    // ���������� �� ����� � ������
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            fscanf(pf, "%c ", &mas[i][j]);
    }

    // ��������� �����
    fclose(pf);

    return 0;
}

// ���������� max �����
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
