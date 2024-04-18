#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void MENU();
struct unitlist* MakeUL_SL();
void DisplayUL_SL();
void ShowUL_SL();
void SelectUL_SL();
void ProduceUL_SL();
struct unitlist* DestroyUL_SL();
void FindWeakEnemy();
struct unitlist* SortByIDUL_SL();

typedef struct
{
    int HP, MP, MOVE, CRD, ATT, UMP, RANGE, ACT, X, Y;
    char ID[10];
    char NAME[10];
    struct unitlist* NEXT;
}unitlist;

int main()
{
    int size = 20;
    unitlist UNIT[20] = { {.NAME = "Hydra", .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 15, .ID = "H0001"},
       {.NAME = "Hydra", .HP = 45, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 39, .Y = 16, .ID = "H0002"},
       {.NAME = "Hydra", .HP = 20, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 39, .Y = 17, .ID = "H0003"},
       {.NAME = "Hydra", .HP = 30, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 38, .Y = 18, .ID = "H0004"},
       {.NAME = "Hydra", .HP = 47, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 19, .ID = "H0005"},
       {.NAME = "Hydra", .HP = 37, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 20, .ID = "H0006"},
       {.NAME = "Queen", .HP = 35, .MP = 150, .MOVE = 6, .CRD = 15, .ATT = 1000, .UMP = 45, .RANGE = 1, .ACT = 2, .X = 40, .Y = 18, .ID = "Q0001"},
       {.NAME = "Queen", .HP = 70, .MP = 150, .MOVE = 6, .CRD = 15, .ATT = 1000, .UMP = 45, .RANGE = 1, .ACT = 2, .X = 39, .Y = 18, .ID = "Q0002"},
       {.NAME = "Defiler", .HP = 40, .MP = 200, .MOVE = 2, .CRD = 10, .ATT = -1, .UMP = 60, .RANGE = 5, .ACT = 2, .X = 40, .Y = 16, .ID = "D0001"},
       {.NAME = "Defiler", .HP = 15, .MP = 200, .MOVE = 2, .CRD = 10, .ATT = -1, .UMP = 60, .RANGE = 5, .ACT = 2, .X = 40, .Y = 17, .ID = "D0002"},
       {.NAME = "Marin", .HP = 25, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 1, .ID = "M0001"},
       {.NAME = "Marin", .HP = 20, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 2, .ID = "M0002"},
       {.NAME = "Marin", .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 3, .ID = "M0003"},
       {.NAME = "Marin", .HP = 15, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 2, .Y = 4, .ID = "M0004"},
       {.NAME = "Marin", .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 2, .Y = 5, .ID = "M0005"},
       {.NAME = "Marin", .HP = 27, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 6, .ID = "M0006"},
       {.NAME = "Tank", .HP = 120, .MP = 0, .MOVE = 4, .CRD = 17, .ATT = 40, .UMP = 0, .RANGE = 1, .ACT = 2, .X = 1, .Y = 4, .ID = "T0001"},
       {.NAME = "Tank", .HP = 50, .MP = 0, .MOVE = 4, .CRD = 17, .ATT = 40, .UMP = 0, .RANGE = 1, .ACT = 2, .X = 1, .Y = 5, .ID = "T0002"},
       {.NAME = "Vessel", .HP = 80, .MP = 140, .MOVE = 5, .CRD = 12, .ATT = 50, .UMP = 35, .RANGE = 3, .ACT = 2, .X = 2, .Y = 3, .ID = "V0001"},
       {.NAME = "Vessel", .HP = 75, .MP = 140, .MOVE = 5, .CRD = 12, .ATT = 50, .UMP = 35, .RANGE = 3, .ACT = 2, .X = 3, .Y = 3, .ID = "V0002"} };
    unitlist* start = NULL;
    start = MakeUL_SL(UNIT, start, size);
    DisplayUL_SL(start, start);
    int unit;
    printf("���׸� �����Ͻ÷��� 1, �׶��� �����Ͻ÷��� 2�� �Է����ֽʽÿ�\n");//���� �׶� ���׸� �� ���� �׶� ������ ����, ��ũ, ������ �߰� ���� ������ �����, ��, �����Ϸ��� �߽��ϴ�.
    printf("�ƹ��͵� �������� �ʰ� �����ϰ� �����ø� 3�� �Է����ּ���\n");
    int cmpox = 1;
    while (cmpox)
    {
        scanf_s("%d%*c", &unit);
        if (unit == 1)
        {
            printf("���׸� �����ϼ̽��ϴ�\n");
            cmpox = 0;
        }
        else if (unit == 2)
        {
            printf("�׶��� �����ϼ̽��ϴ�\n");
            cmpox = 0;
        }
        else if (unit == 3)
        {
            printf("�ƹ��͵� �������� �ʴ� ���� �����ϼ̽��ϴ�.\n");
            cmpox = 0;
        }
        else
        {
            printf("�߸��� ������ �Է��ϼ̽��ϴ�. �ٽ� �Է����ֽʽÿ�\n");
            printf("���׸� �����Ͻ÷��� 1, �׶��� �����Ͻ÷��� 2�� �Է����ֽʽÿ�\n");
            printf("�ƹ��͵� �������� �ʰ� �����ϰ� �����ø� 3�� �Է����ּ���\n");
        }
    }
    while (1)
    {
        int menu, x = NULL, y = NULL, distance = NULL;
        MENU();
        scanf_s("%d%*c", &menu);
        system("cls");
        if (menu == 0)
        {
            DisplayUL_SL(start, start);
        }
        else if (menu == 1)
        {
            ShowUL_SL(start, start);
        }
        else if (menu == 2)
        {
            SelectUL_SL(start, start, x, y);
        }
        else if (menu == 3)
        {
            ProduceUL_SL(start, start);
        }
        else if (menu == 4)
        {
            start = DestroyUL_SL(start, start, UNIT, x, y);
        }
        else if (menu == 5)
        {
            FindWeakEnemy(start, start, x, y, distance, unit);
        }
        else if (menu == 6)
        {
            start = SortByIDUL_SL(start, start);
            //ShowUL_SL(start, start); //����� �ٷ� Ȯ���ϰ� �����ø� �ּ� Ǯ���ֽø� �˴ϴ�.
        }
    }
}

//�޴��� ����ϴ� �Լ�
void MENU()
{
    printf("0. DisplayUL_SL\n");
    printf("1. ShowUL_SL\n");
    printf("2. SelectUL_SL\n");
    printf("3. ProduceUL_SL\n");
    printf("4. DestroyUL_SL\n");
    printf("5. FindWeakEnemyUL_SL\n");
    printf("6. SortByIDUL_SL\n");
    printf("�޴��� �������ֽʽÿ�.\n");
}

//���� ������ִ� �Լ�
void DisplayUL_SL(unitlist* u, unitlist* start)
{
    for (int j = 1; j <= 20; j++)
    {
        for (int i = 1; i <= 40; i++)
        {
            int ox = 0;
            u = start;
            for (u; (*u).NEXT != start; u = (*u).NEXT)
            {
                if ((*u).X == i && (*u).Y == j)
                {
                    printf("%c", *((*u).NAME));
                    ox = 1;
                }
            }
            if ((*u).NEXT == start)
            {
                if ((*u).X == i && (*u).Y == j)
                {
                    printf("%c", *((*u).NAME));
                    ox = 1;
                }
            }
            if (ox == 0)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

struct unitlist* MakeUL_SL(unitlist* u, unitlist* start, int size)
{
    if (size != 0)
    {
        if (start == NULL)//���� �ּ� �������ֱ�
        {
            start = u;
        }
        (*u).NEXT = u + 1;
        size--;
        MakeUL_SL((*u).NEXT, start, size);//���Ḯ��Ʈ ������ ���� ����ü ȣ��
    }
    else if (size == 0)
    {
        u--;
        (*u).NEXT = start;
        return start;//�����ּ� ����
    }
}

void ShowUL_SL(unitlist* u, unitlist* start)
{
    if ((*u).NEXT != start)
    {
        printf("���� ���� : %s\n", (*u).NAME);
        printf("ü�� : %d \t ���� : %d \t �̵��Ÿ� : %d \n��Ÿ� : %d \t ���ݷ� : %d \t �Ҹ� ���� : %d\n���ݹ��� : %d \t �ൿ�� : %d \nX��ǥ : %d \t Y��ǥ : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        ShowUL_SL((*u).NEXT, start);
    }
    else if ((*u).NEXT == start)
    {
        printf("���� ���� : %s\n", (*u).NAME);
        printf("ü�� : %d \t ���� : %d \t �̵��Ÿ� : %d \n��Ÿ� : %d \t ���ݷ� : %d \t �Ҹ� ���� : %d\n���ݹ��� : %d \t �ൿ�� : %d \nX��ǥ : %d \t Y��ǥ : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
    }
}

void SelectUL_SL(unitlist* u, unitlist* start, int x, int y)
{
    if (x == NULL && y == NULL)
    {
        int ox = 1;
        while (ox)
        {
            printf("��ǥ�� �Է��Ͻʽÿ�.\n");
            scanf_s("%d %d%*c", &x, &y);
            if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
            {
                ox = 0;
            }
            else if (x == 0 && y == 0)
            {
                return;
            }
            else
            {
                printf("�߸��� ��ǥ �����Դϴ�.\n");
                printf("�ٽ� �Է����ֽʽÿ�.\n");
                printf("�޴��� ���ư��� �����ø� '0 0'�� �Է��� �ֽʽÿ�.\n");
            }
        }
    }
    if ((*u).NEXT != start)
    {
        if ((*u).X == x && (*u).Y == y)
        {
            printf("���� ���� : %s\n", (*u).NAME);
            printf("ü�� : %d \t ���� : %d \t �̵��Ÿ� : %d \n��Ÿ� : %d \t ���ݷ� : %d \t �Ҹ� ���� : %d\n���ݹ��� : %d \t �ൿ�� : %d \nX��ǥ : %d \t Y��ǥ : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        }
        else SelectUL_SL((*u).NEXT, start, x, y);
    }
    else if ((*u).NEXT == start)
    {
        if ((*u).X == x && (*u).Y == y)
        {
            printf("���� ���� : %s\n", (*u).NAME);
            printf("ü�� : %d \t ���� : %d \t �̵��Ÿ� : %d \n��Ÿ� : %d \t ���ݷ� : %d \t �Ҹ� ���� : %d\n���ݹ��� : %d \t �ൿ�� : %d \nX��ǥ : %d \t Y��ǥ : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        }
    }
}

void ProduceUL_SL(unitlist* u, unitlist* start)
{
    unitlist* new = malloc(sizeof(unitlist));
    printf("������ ������ ��ǥ�� �Է��Ͻʽÿ�.\n");
    int ox = 1;
    while (ox)
    {
        printf("��ǥ�� �Է��Ͻʽÿ�.\n");
        scanf_s("%d %d%*c", &(*new).X, &(*new).Y);
        if ((*new).X >= 1 && (*new).X <= 40 && (*new).Y >= 1 && (*new).Y <= 20)
        {
            ox = 0;
        }
        else if ((*new).X == 0 && (*new).Y == 0)
        {
            free(new);
            return;
        }
        else
        {
            printf("�߸��� ��ǥ �����Դϴ�.\n");
            printf("�ٽ� �Է����ֽʽÿ�.\n");
            printf("�޴��� ���ư��� �����ø� '0 0'�� �Է��� �ֽʽÿ�.\n");
        }
    }
    //scanf_s("%d %d%*c", &(*new).X, &(*new).Y);
    system("cls");
    printf("������ ������ �Է��Ͻÿ�\n");
    printf("Hydra - ����� \t Queen - �� \t Defiler - �����Ϸ�\t\n");
    printf("Marin - ���� \t Tank - ��ũ \t Vessel - ���� \t\n");
    printf("������ ������ ���ڿ� �� �� �� ���ڰ� �ʿ� ǥ�ð� �˴ϴ�. ������ �ּ���\n");
    gets_s((*new).NAME, sizeof(char) * 10);
    system("cls");
    printf("ü���� �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).HP);
    system("cls");
    printf("������ �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).MP);
    system("cls");
    printf("�̵��Ÿ��� �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).MOVE);
    system("cls");
    printf("��Ÿ��� �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).CRD);
    system("cls");
    printf("���ݷ��� �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).ATT);
    system("cls");
    printf("�Ҹ� ������ �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).UMP);
    system("cls");
    printf("���� ������ �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).RANGE);
    system("cls");
    printf("�ൿ���� �Է��Ͻÿ�\n");
    scanf_s("%d%*c", &(*new).ACT);
    system("cls");
    printf("ID�� �Է��Ͻÿ�\n");
    gets_s((*new).ID, sizeof(char) * 10);
    system("cls");
    while ((*u).NEXT != start)
    {
        u = (*u).NEXT;
    }
    if ((*u).NEXT == start)
    {
        (*u).NEXT = new;
        (*new).NEXT = start;
    }
}

struct unitlist* DestroyUL_SL(unitlist* u, unitlist* start, unitlist* add, int x, int y)
{
    unitlist* add1 = (*u).NEXT;
    unitlist* add2 = (*add1).NEXT;
    if (x == NULL && y == NULL)
    {
        int ox = 1;
        while (ox)
        {
            printf("��ǥ�� �Է��Ͻʽÿ�.\n");
            scanf_s("%d %d%*c", &x, &y);
            if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
            {
                ox = 0;
            }
            else if (x == 0 && y == 0)
            {
                return;
            }
            else
            {
                printf("�߸��� ��ǥ �����Դϴ�.\n");
                printf("�ٽ� �Է����ֽʽÿ�.\n");
                printf("�޴��� ���ư��� �����ø� '0 0'�� �Է��� �ֽʽÿ�.\n");
            }
        }
    }
    if ((*u).NEXT != start)
    {
        if ((*add1).X == x && (*add1).Y == y)
        {
            (*u).NEXT = add2;
            if (add1 >= add && add1 <= add + 19)
            {
                (*add1).NEXT = NULL;
                *((*add1).NAME) = NULL, (*add1).HP = NULL, (*add1).MP = NULL, (*add1).MOVE = NULL, (*add1).CRD = NULL, (*add1).ATT = NULL, (*add1).UMP = NULL, (*add1).RANGE = NULL, (*add1).ACT = NULL, (*add1).X = NULL, (*add1).Y = NULL, * ((*add1).ID) = NULL;
            }
            else free(add1);
            return start;
        }
        else DestroyUL_SL((*u).NEXT, start, add, x, y);
    }
    else if ((*u).NEXT == start)
    {
        if ((*add1).X == x && (*add1).Y == y)
        {
            (*u).NEXT = add2;
            if (add1 >= add && add1 <= add + 19)
            {
                (*add1).NEXT = NULL;
                *((*add1).NAME) = NULL, (*add1).HP = NULL, (*add1).MP = NULL, (*add1).MOVE = NULL, (*add1).CRD = NULL, (*add1).ATT = NULL, (*add1).UMP = NULL, (*add1).RANGE = NULL, (*add1).ACT = NULL, (*add1).X = NULL, (*add1).Y = NULL, * ((*add1).ID) = NULL;
            }
            else free(add1);
            return add2;
        }
        else
        {
            printf("������ ���� ��ǥ�Դϴ�.\n");
            return start;
        }
    }
}

void FindWeakEnemy(unitlist* u, unitlist* start, int x, int y, int distance, int unit)
{
    if (x == NULL && y == NULL && distance == NULL)
    {
        int ox = 1;
        while (ox)
        {
            printf("��ǥ�� �Ÿ��� �Է��Ͻʽÿ�.\n");
            printf("��) 34 15 6 -> 34�� x��ǥ, 15�� y��ǥ, 6�� �Ÿ�\n");
            scanf_s("%d %d %d%*c", &x, &y, &distance);
            if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
            {
                ox = 0;
            }
            else if (x == 0 && y == 0)
            {
                return;
            }
            else
            {
                printf("�߸��� ��ǥ �����Դϴ�.\n");
                printf("�ٽ� �Է����ֽʽÿ�.\n");
                printf("�޴��� ���ư��� �����ø� '0 0 0'�� �Է��� �ֽʽÿ�.\n");
            }
        }
    }
    int count = 0;
    while ((*u).NEXT != start)
    {
        if (unit == 1 || unit == 3)
        {
            if (*((*u).NAME) == 'M' || *((*u).NAME) == 'T' || *((*u).NAME) == 'V')
            {
                int length;
                if (abs((*u).X - x) >= abs((*u).X - x))
                {
                    length = abs((*u).X - x);
                }
                else length = abs((*u).Y - y);
                if (length <= distance)
                {
                    count++;
                }
            }
        }
        else if (unit == 2 || unit == 3)
        {
            if (*((*u).NAME) == 'H' || *((*u).NAME) == 'Q' || *((*u).NAME) == 'D')
            {
                int length;
                if (abs((*u).X - x) >= abs((*u).X - x))
                {
                    length = abs((*u).X - x);
                }
                else length = abs((*u).Y - y);
                if (length <= distance)
                {
                    count++;
                }
            }
        }
        u = (*u).NEXT;
    }
    if ((*u).NEXT == start)
    {
        if (unit == 1 || unit == 3)
        {
            if (*((*u).NAME) == 'M' || *((*u).NAME) == 'T' || *((*u).NAME) == 'V')
            {
                int length;
                if (abs((*u).X - x) >= abs((*u).X - x))
                {
                    length = abs((*u).X - x);
                }
                else length = abs((*u).Y - y);
                if (length <= distance)
                {
                    count++;
                }
            }
        }
        else if (unit == 2 || unit == 3)
        {
            if (*((*u).NAME) == 'H' || *((*u).NAME) == 'Q' || *((*u).NAME) == 'D')
            {
                int length;
                if (abs((*u).X - x) >= abs((*u).X - x))
                {
                    length = abs((*u).X - x);
                }
                else length = abs((*u).Y - y);
                if (length <= distance)
                {
                    count++;
                }
            }
        }
    }
    if (count == 0)
    {
        printf("�־��� ��ǥ�κ��� �־��� �Ÿ� ���� ���� ������ �ϳ��� �����ϴ�.\n");
        return;
    }
    unitlist** index = (unitlist*)malloc(sizeof(unitlist*) * count);
    printf("%d\n", sizeof(unitlist));
    printf("%d\n", sizeof(index));
    u = start;
    for (int i = 0; i < count; u = (*u).NEXT)
    {
        if (unit == 1 ||unit == 3)
        {
            if (*((*u).NAME) == 'M' || *((*u).NAME) == 'T' || *((*u).NAME) == 'V')
            {
                int length;
                if (abs((*u).X - x) >= abs((*u).X - x))
                {
                    length = abs((*u).X - x);
                }
                else length = abs((*u).Y - y);
                if (length <= distance)
                {
                    index[i] = u;
                    i++;
                }
            }
        }
        else if (unit == 2 || unit == 3)
        {
            if (*((*u).NAME) == 'H' || *((*u).NAME) == 'Q' || *((*u).NAME) == 'D')
            {
                int length;
                if (abs((*u).X - x) >= abs((*u).X - x))
                {
                    length = abs((*u).X - x);
                }
                else length = abs((*u).Y - y);
                if (length <= distance)
                {
                    index[i] = u;
                    i++;
                }
            }
        }
    }
    u = start;
    for (int j = 0; j < count - 1; j++)
    {
        for (int i = 0; i < count - 1; i++)
        {
            if ((*index[i]).HP > (*index[i + 1]).HP)
            {
                unitlist* temp = index[i];
                index[i] = index[i + 1];
                index[i + 1] = temp;
            }
        }
    }
    for (int i = 0; (*index[i]).HP == (*index[0]).HP; i++)
    {
        printf("���� ���� : %s\n", (*index[i]).NAME);
        printf("ü�� : %d \t ���� : %d \t �̵��Ÿ� : %d \n��Ÿ� : %d \t ���ݷ� : %d \t �Ҹ� ���� : %d\n���ݹ��� : %d \t �ൿ�� : %d \nX��ǥ : %d \t Y��ǥ : %d \t ID : %s\n\n\n", (*index[i]).HP, (*index[i]).MP, (*index[i]).MOVE, (*index[i]).CRD, (*index[i]).ATT, (*index[i]).UMP, (*index[i]).RANGE, (*index[i]).ACT, (*index[i]).X, (*index[i]).Y, (*index[i]).ID);
    }
    free(index);
}

struct unitlist* SortByIDUL_SL(unitlist* u, unitlist* start)
{
    int count = 0;
    while ((*u).NEXT != start)
    {
        count++;
        u = (*u).NEXT;
    }
    if ((*u).NEXT == start)
    {
        count++;
    }
    u = start;
    if (count == 0)
    {
        printf("error\n");
    }
    unitlist** index = (unitlist*)malloc(sizeof(unitlist*) * count);
    for (int i = 0; i < count; i++, u = (*u).NEXT)
    {
        index[i] = u;
    }
    for (int j = 0; j < count - 1; j++)
    {
        for (int i = 0; i < count - 1; i++)
        {
            if (strcmp((*index[i]).ID, (*index[i + 1]).ID) > 0)
            {
                unitlist* temp = index[i];
                index[i] = index[i + 1];
                index[i + 1] = temp;
            }
        }
    }
    for (int i = 0; i < count - 1; i++)
    {
        (*index[i]).NEXT = index[i + 1];
    }
    (*index[count - 1]).NEXT = index[0];
    return index[0];
}