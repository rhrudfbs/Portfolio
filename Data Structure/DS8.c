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
    printf("저그를 선택하시려면 1, 테란을 선택하시려면 2를 입력해주십시오\n");//제가 테란 저그를 잘 몰라서 테란 유닛을 마린, 탱크, 베슬로 했고 저그 유닛을 히드라, 퀸, 디파일러로 했습니다.
    printf("아무것도 선택하지 않고 진행하고 싶으시면 3을 입력해주세요\n");
    int cmpox = 1;
    while (cmpox)
    {
        scanf_s("%d%*c", &unit);
        if (unit == 1)
        {
            printf("저그를 선택하셨습니다\n");
            cmpox = 0;
        }
        else if (unit == 2)
        {
            printf("테란을 선택하셨습니다\n");
            cmpox = 0;
        }
        else if (unit == 3)
        {
            printf("아무것도 선택하지 않는 것을 선택하셨습니다.\n");
            cmpox = 0;
        }
        else
        {
            printf("잘못된 정보를 입력하셨습니다. 다시 입력해주십시오\n");
            printf("저그를 선택하시려면 1, 테란을 선택하시려면 2를 입력해주십시오\n");
            printf("아무것도 선택하지 않고 진행하고 싶으시면 3을 입력해주세요\n");
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
            //ShowUL_SL(start, start); //결과를 바로 확인하고 싶으시면 주석 풀어주시면 됩니다.
        }
    }
}

//메뉴를 출력하는 함수
void MENU()
{
    printf("0. DisplayUL_SL\n");
    printf("1. ShowUL_SL\n");
    printf("2. SelectUL_SL\n");
    printf("3. ProduceUL_SL\n");
    printf("4. DestroyUL_SL\n");
    printf("5. FindWeakEnemyUL_SL\n");
    printf("6. SortByIDUL_SL\n");
    printf("메뉴를 선택해주십시오.\n");
}

//맵을 만들어주는 함수
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
        if (start == NULL)//시작 주소 지정해주기
        {
            start = u;
        }
        (*u).NEXT = u + 1;
        size--;
        MakeUL_SL((*u).NEXT, start, size);//연결리스트 정보로 다음 구조체 호출
    }
    else if (size == 0)
    {
        u--;
        (*u).NEXT = start;
        return start;//시작주소 리턴
    }
}

void ShowUL_SL(unitlist* u, unitlist* start)
{
    if ((*u).NEXT != start)
    {
        printf("유닛 종류 : %s\n", (*u).NAME);
        printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        ShowUL_SL((*u).NEXT, start);
    }
    else if ((*u).NEXT == start)
    {
        printf("유닛 종류 : %s\n", (*u).NAME);
        printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
    }
}

void SelectUL_SL(unitlist* u, unitlist* start, int x, int y)
{
    if (x == NULL && y == NULL)
    {
        int ox = 1;
        while (ox)
        {
            printf("좌표를 입력하십시오.\n");
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
                printf("잘못된 좌표 정보입니다.\n");
                printf("다시 입력해주십시오.\n");
                printf("메뉴로 돌아가고 싶으시면 '0 0'을 입력해 주십시오.\n");
            }
        }
    }
    if ((*u).NEXT != start)
    {
        if ((*u).X == x && (*u).Y == y)
        {
            printf("유닛 종류 : %s\n", (*u).NAME);
            printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        }
        else SelectUL_SL((*u).NEXT, start, x, y);
    }
    else if ((*u).NEXT == start)
    {
        if ((*u).X == x && (*u).Y == y)
        {
            printf("유닛 종류 : %s\n", (*u).NAME);
            printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        }
    }
}

void ProduceUL_SL(unitlist* u, unitlist* start)
{
    unitlist* new = malloc(sizeof(unitlist));
    printf("유닛을 생성할 좌표를 입력하십시오.\n");
    int ox = 1;
    while (ox)
    {
        printf("좌표를 입력하십시오.\n");
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
            printf("잘못된 좌표 정보입니다.\n");
            printf("다시 입력해주십시오.\n");
            printf("메뉴로 돌아가고 싶으시면 '0 0'을 입력해 주십시오.\n");
        }
    }
    //scanf_s("%d %d%*c", &(*new).X, &(*new).Y);
    system("cls");
    printf("유닛의 종류를 입력하시오\n");
    printf("Hydra - 히드라 \t Queen - 퀸 \t Defiler - 디파일러\t\n");
    printf("Marin - 마린 \t Tank - 탱크 \t Vessel - 베슬 \t\n");
    printf("유닛의 종류의 문자열 중 맨 앞 글자가 맵에 표시가 됩니다. 유의해 주세요\n");
    gets_s((*new).NAME, sizeof(char) * 10);
    system("cls");
    printf("체력을 입력하시오\n");
    scanf_s("%d%*c", &(*new).HP);
    system("cls");
    printf("마나를 입력하시오\n");
    scanf_s("%d%*c", &(*new).MP);
    system("cls");
    printf("이동거리를 입력하시오\n");
    scanf_s("%d%*c", &(*new).MOVE);
    system("cls");
    printf("사거리를 입력하시오\n");
    scanf_s("%d%*c", &(*new).CRD);
    system("cls");
    printf("공격력을 입력하시오\n");
    scanf_s("%d%*c", &(*new).ATT);
    system("cls");
    printf("소모 마나를 입력하시오\n");
    scanf_s("%d%*c", &(*new).UMP);
    system("cls");
    printf("공격 범위를 입력하시오\n");
    scanf_s("%d%*c", &(*new).RANGE);
    system("cls");
    printf("행동력을 입력하시오\n");
    scanf_s("%d%*c", &(*new).ACT);
    system("cls");
    printf("ID를 입력하시오\n");
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
            printf("좌표를 입력하십시오.\n");
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
                printf("잘못된 좌표 정보입니다.\n");
                printf("다시 입력해주십시오.\n");
                printf("메뉴로 돌아가고 싶으시면 '0 0'을 입력해 주십시오.\n");
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
            printf("유닛이 없는 좌표입니다.\n");
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
            printf("좌표와 거리를 입력하십시오.\n");
            printf("예) 34 15 6 -> 34는 x좌표, 15는 y좌표, 6은 거리\n");
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
                printf("잘못된 좌표 정보입니다.\n");
                printf("다시 입력해주십시오.\n");
                printf("메뉴로 돌아가고 싶으시면 '0 0 0'을 입력해 주십시오.\n");
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
        printf("주어진 좌표로부터 주어진 거리 내에 적의 유닛이 하나도 없습니다.\n");
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
        printf("유닛 종류 : %s\n", (*index[i]).NAME);
        printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*index[i]).HP, (*index[i]).MP, (*index[i]).MOVE, (*index[i]).CRD, (*index[i]).ATT, (*index[i]).UMP, (*index[i]).RANGE, (*index[i]).ACT, (*index[i]).X, (*index[i]).Y, (*index[i]).ID);
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