#include <stdio.h>
#include <Windows.h>

void MENU();
void ShowUL_R();
void Produce_UL_R();
void SelectAll_UL_R();
void Destroy_UL_R();
void FindWeakEnemy_R();

typedef struct
{
    int HP, MP, MOVE, CRD, ATT, UMP, RANGE, ACT, X, Y;
    char ID[10];
    char NAME;
}unitlist;

int main()
{
    int num = 20, size = 800;
    unitlist UNIT[800] = { {.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 15, .ID = "H0001"},
       {.NAME = 'H', .HP = 45, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 39, .Y = 16, .ID = "H0002"},
       {.NAME = 'H', .HP = 20, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 39, .Y = 17, .ID = "H0003"},
       {.NAME = 'H', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 38, .Y = 18, .ID = "H0004"},
       {.NAME = 'H', .HP = 47, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 19, .ID = "H0005"},
       {.NAME = 'H', .HP = 37, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 20, .ID = "H0006"},
       {.NAME = 'Q', .HP = 35, .MP = 150, .MOVE = 6, .CRD = 15, .ATT = 1000, .UMP = 45, .RANGE = 1, .ACT = 2, .X = 40, .Y = 18, .ID = "Q0001"},
       {.NAME = 'Q', .HP = 70, .MP = 150, .MOVE = 6, .CRD = 15, .ATT = 1000, .UMP = 45, .RANGE = 1, .ACT = 2, .X = 39, .Y = 18, .ID = "Q0002"},
       {.NAME = 'D', .HP = 40, .MP = 200, .MOVE = 2, .CRD = 10, .ATT = -1, .UMP = 60, .RANGE = 5, .ACT = 2, .X = 40, .Y = 16, .ID = "D0001"},
       {.NAME = 'D', .HP = 15, .MP = 200, .MOVE = 2, .CRD = 10, .ATT = -1, .UMP = 60, .RANGE = 5, .ACT = 2, .X = 40, .Y = 17, .ID = "D0002"},
       {.NAME = 'M', .HP = 25, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 1, .ID = "M0001"},
       {.NAME = 'M', .HP = 20, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 2, .ID = "M0002"},
       {.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 3, .ID = "M0003"},
       {.NAME = 'M', .HP = 15, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 2, .Y = 4, .ID = "M0004"},
       {.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 2, .Y = 5, .ID = "M0005"},
       {.NAME = 'M', .HP = 27, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 6, .ID = "M0006"},
       {.NAME = 'T', .HP = 120, .MP = 0, .MOVE = 4, .CRD = 17, .ATT = 40, .UMP = 0, .RANGE = 1, .ACT = 2, .X = 1, .Y = 4, .ID = "T0001"},
       {.NAME = 'T', .HP = 50, .MP = 0, .MOVE = 4, .CRD = 17, .ATT = 40, .UMP = 0, .RANGE = 1, .ACT = 2, .X = 1, .Y = 5, .ID = "T0002"},
       {.NAME = 'V', .HP = 80, .MP = 140, .MOVE = 5, .CRD = 12, .ATT = 50, .UMP = 35, .RANGE = 3, .ACT = 2, .X = 2, .Y = 3, .ID = "V0001"},
       {.NAME = 'V', .HP = 75, .MP = 140, .MOVE = 5, .CRD = 12, .ATT = 50, .UMP = 35, .RANGE = 3, .ACT = 2, .X = 3, .Y = 3, .ID = "V0002"} };
    for (int j = 1; j <= 20; j++)
    {
        for (int i = 1; i <= 40; i++)
        {
            int ox = 0;
            for (int k = 0; k <= size - 1; k++)
            {
                if (UNIT[k].NAME == 'H' || UNIT[k].NAME == 'Q' || UNIT[k].NAME == 'D' || UNIT[k].NAME == 'M' || UNIT[k].NAME == 'T' || UNIT[k].NAME == 'V')
                {
                    if (UNIT[k].X == i && UNIT[k].Y == j)
                    {
                        printf("%c", UNIT[k].NAME);
                        ox = 1;
                    }
                }
            }
            if (ox == 0)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    while (1)
    {
        int menu, x1, y1, x2, y2;
        MENU();
        printf("메뉴를 선택하고 엔터를 입력해 주십시오\n");
        printf("예) 1(enter)\n");
        scanf_s("%d%*c", &menu);
        system("cls");
        if (menu == 1)
        {
            ShowUL_R(UNIT, size);
        }
        else if (menu == 2)
        {
            printf("유닛을 배치할 좌표를 입력하시오\n");
            printf("예) 15 17 -> 해석 : 15(x좌표) 17(y좌표)\n");
            scanf_s("%d %d%*c", &x1, &y1);
            if (x1 >= 1 && x1 <= 40 && y1 >= 1 && y1 <= 20)
            {
                Produce_UL_R(UNIT, size, x1, y1);
            }
            else
            {
                printf("잘못된 좌표값입니다.\n");
            }
        }
        else if (menu == 3)
        {
            printf("좌표 두 개를 입력하시오\n");
            printf("예) 15 17 30 19 -> 해석 : 15(x1좌표) 17(y1좌표) 30(x2좌표) 19(y2좌표)\n");
            scanf_s("%d %d %d %d%*c", &x1, &y1, &x2, &y2);
            if (x1 >= 1 && x1 <= 40 && y1 >= 1 && y1 <= 20 && x2 >= 1 && x2 <= 40 && y2 >= 1 && y2 <= 20)
            {
                SelectAll_UL_R(UNIT, size, x1, y1, x2, y2);
            }
            else
            {
                printf("잘못된 좌표값입니다.\n");
            }
        }
        else if (menu == 4)
        {
            printf("삭제할 유닛의 좌표를 입력하시오\n");
            printf("예) 15 17 -> 해석 : 15(x좌표) 17(y좌표)\n");
            scanf_s("%d %d%*c", &x1, &y1);
            if (x1 >= 1 && x1 <= 40 && y1 >= 1 && y1 <= 20)
            {
                Destroy_UL_R(UNIT, size, x1, y1);
            }
            else
            {
                printf("잘못된 좌표값입니다.\n");
            }
        }
        else if (menu == 5)
        {
            int distance;
            int index1 = 0;
            int index2 = 0;
            int p[800];
            printf("좌표를 입력하시오\n");
            printf("예) 15 17 20 -> 해석 : 15(x좌표) 17(y좌표)로 부터 20(거리) 내에 있는 유닛 중 HP가 가장 작은 유닛들을 출력해주십시오\n");
            scanf_s("%d %d %d%*c", &x1, &y1, &distance);
            if (x1 >= 1 && x1 <= 40 && y1 >= 1 && y1 <= 20)
            {
                FindWeakEnemy_R(UNIT, size, x1, y1, distance, p, index1, index2);
            }
            else
            {
                printf("잘못된 좌표값입니다.\n");
            }
        }
        else if (menu == 6)
        {
            for (int j = 1; j <= 20; j++)
            {
                for (int i = 1; i <= 40; i++)
                {
                    int ox = 0;
                    for (int k = 0; k <= size - 1; k++)
                    {
                        if (UNIT[k].NAME == 'H' || UNIT[k].NAME == 'Q' || UNIT[k].NAME == 'D' || UNIT[k].NAME == 'M' || UNIT[k].NAME == 'T' || UNIT[k].NAME == 'V')
                        {
                            if (UNIT[k].X == i && UNIT[k].Y == j)
                            {
                                printf("%c", UNIT[k].NAME);
                                ox = 1;
                            }
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
        else
        {
            printf("메뉴를 다시 입력해주십시오\n");
        }
    }
}

void MENU()
{
    printf("1. ShowUL_R\n");
    printf("2. Produce_UL_R\n");
    printf("3. SelectAll_UL_R\n");
    printf("4. Destroy_UL_R\n");
    printf("5. FindWeakEnemy_R\n");
    printf("6. DisplayMap_UL\n");
}

void ShowUL_R(unitlist* u, int size)
{
    if (size != 0)
    {
        if ((*u).NAME == 'H' || (*u).NAME == 'Q' || (*u).NAME == 'D' || (*u).NAME == 'M' || (*u).NAME == 'T' || (*u).NAME == 'V')
        {
            if ((*u).NAME == 'H')
            {
                printf("히드라\n");
            }
            else if ((*u).NAME == 'Q')
            {
                printf("퀸\n");
            }
            else if ((*u).NAME == 'D')
            {
                printf("디파일러\n");
            }
            else if ((*u).NAME == 'M')
            {
                printf("마린\n");
            }
            else if ((*u).NAME == 'T')
            {
                printf("탱크\n");
            }
            else if ((*u).NAME == 'V')
            {
                printf("베슬\n");
            }
            printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
        }
        else if ((*u).NAME == 'h' || (*u).NAME == 'q' || (*u).NAME == 'd' || (*u).NAME == 'm' || (*u).NAME == 't' || (*u).NAME == 'v')
        {
            printf("*************************************아래는 Destroy_UL_R함수로 삭제된 데이터 공간입니다.*******************************************************\n");
            if ((*u).NAME == 'h')
            {
                printf("히드라\n");
            }
            else if ((*u).NAME == 'q')
            {
                printf("퀸\n");
            }
            else if ((*u).NAME == 'd')
            {
                printf("디파일러\n");
            }
            else if ((*u).NAME == 'm')
            {
                printf("마린\n");
            }
            else if ((*u).NAME == 't')
            {
                printf("탱크\n");
            }
            else if ((*u).NAME == 'v')
            {
                printf("베슬\n");
            }
            printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
            printf("***********************************************************************************************************************************************\n");
        }
        u++;
        size--;
        ShowUL_R(u, size);
    }
}

void Produce_UL_R(unitlist* u, int size, int x1, int y1)
{
    if (size != 0)
    {
        if ((*u).NAME != 'H' && (*u).NAME != 'Q' && (*u).NAME != 'D' && (*u).NAME != 'M' && (*u).NAME != 'T' && (*u).NAME != 'V' && (*u).NAME != 'h' && (*u).NAME != 'q' && (*u).NAME != 'd' && (*u).NAME != 'm' && (*u).NAME != 't' && (*u).NAME != 'v')
        {
            (*u).X = x1, (*u).Y = y1;
            printf("유닛의 종류를 입력하시오\n");
            printf("주의) 아래 주어진 유닛의 대문자 이니셜로만 입력할 것\n");
            printf("H - 히드라 \t Q - 퀸 \t D - 디파일러\t\n");
            printf("M - 마린 \t T - 탱크 \t V - 베슬 \t\n");
            scanf_s("%c%*c", &(*u).NAME);
            system("cls");
            printf("체력을 입력하시오\n");
            scanf_s("%d%*c", &(*u).HP);
            system("cls");
            printf("마나를 입력하시오\n");
            scanf_s("%d%*c", &(*u).MP);
            system("cls");
            printf("이동거리를 입력하시오\n");
            scanf_s("%d%*c", &(*u).MOVE);
            system("cls");
            printf("사거리를 입력하시오\n");
            scanf_s("%d%*c", &(*u).CRD);
            system("cls");
            printf("공격력을 입력하시오\n");
            scanf_s("%d%*c", &(*u).ATT);
            system("cls");
            printf("소모 마나를 입력하시오\n");
            scanf_s("%d%*c", &(*u).UMP);
            system("cls");
            printf("공격 범위를 입력하시오\n");
            scanf_s("%d%*c", &(*u).RANGE);
            system("cls");
            printf("행동력을 입력하시오\n");
            scanf_s("%d%*c", &(*u).ACT);
            system("cls");
            printf("ID를 입력하시오\n");
            gets_s((*u).ID, sizeof(char) * 10);
            system("cls");
        }
        else
        {
            u++;
            size--;
            Produce_UL_R(u, size, x1, y1);
        }
    }
}

void SelectAll_UL_R(unitlist* u, int size, int x1, int y1, int x2, int y2)
{
    if (size != 0)
    {
        if (x1 >= x2 && y1 >= y2)
        {
            if ((*u).X <= x1 && (*u).X >= x2 && (*u).Y <= y1 && (*u).Y >= y2)
            {
                if ((*u).NAME == 'H' || (*u).NAME == 'Q' || (*u).NAME == 'D' || (*u).NAME == 'M' || (*u).NAME == 'T' || (*u).NAME == 'V')
                {
                    if ((*u).NAME == 'H')
                    {
                        printf("히드라\n");
                    }
                    else if ((*u).NAME == 'Q')
                    {
                        printf("퀸\n");
                    }
                    else if ((*u).NAME == 'D')
                    {
                        printf("디파일러\n");
                    }
                    else if ((*u).NAME == 'M')
                    {
                        printf("마린\n");
                    }
                    else if ((*u).NAME == 'T')
                    {
                        printf("탱크\n");
                    }
                    else if ((*u).NAME == 'V')
                    {
                        printf("베슬\n");
                    }
                    printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
                }
            }
        }
        else if (x1 < x2 && y1 >= y2)
        {
            if ((*u).X >= x1 && (*u).X <= x2 && (*u).Y <= y1 && (*u).Y >= y2)
            {
                if ((*u).NAME == 'H' || (*u).NAME == 'Q' || (*u).NAME == 'D' || (*u).NAME == 'M' || (*u).NAME == 'T' || (*u).NAME == 'V')
                {
                    if ((*u).NAME == 'H')
                    {
                        printf("히드라\n");
                    }
                    else if ((*u).NAME == 'Q')
                    {
                        printf("퀸\n");
                    }
                    else if ((*u).NAME == 'D')
                    {
                        printf("디파일러\n");
                    }
                    else if ((*u).NAME == 'M')
                    {
                        printf("마린\n");
                    }
                    else if ((*u).NAME == 'T')
                    {
                        printf("탱크\n");
                    }
                    else if ((*u).NAME == 'V')
                    {
                        printf("베슬\n");
                    }
                    printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
                }
            }
        }
        else if (x1 >= x2 && y1 < y2)
        {
            if ((*u).X <= x1 && (*u).X >= x2 && (*u).Y >= y1 && (*u).Y <= y2)
            {
                if ((*u).NAME == 'H' || (*u).NAME == 'Q' || (*u).NAME == 'D' || (*u).NAME == 'M' || (*u).NAME == 'T' || (*u).NAME == 'V')
                {
                    if ((*u).NAME == 'H')
                    {
                        printf("히드라\n");
                    }
                    else if ((*u).NAME == 'Q')
                    {
                        printf("퀸\n");
                    }
                    else if ((*u).NAME == 'D')
                    {
                        printf("디파일러\n");
                    }
                    else if ((*u).NAME == 'M')
                    {
                        printf("마린\n");
                    }
                    else if ((*u).NAME == 'T')
                    {
                        printf("탱크\n");
                    }
                    else if ((*u).NAME == 'V')
                    {
                        printf("베슬\n");
                    }
                    printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
                }
            }
        }
        else if (x1 < x2 && y1 < y2)
        {
            if ((*u).X >= x1 && (*u).X <= x2 && (*u).Y >= y1 && (*u).Y <= y2)
            {
                if ((*u).NAME == 'H' || (*u).NAME == 'Q' || (*u).NAME == 'D' || (*u).NAME == 'M' || (*u).NAME == 'T' || (*u).NAME == 'V')
                {
                    if ((*u).NAME == 'H')
                    {
                        printf("히드라\n");
                    }
                    else if ((*u).NAME == 'Q')
                    {
                        printf("퀸\n");
                    }
                    else if ((*u).NAME == 'D')
                    {
                        printf("디파일러\n");
                    }
                    else if ((*u).NAME == 'M')
                    {
                        printf("마린\n");
                    }
                    else if ((*u).NAME == 'T')
                    {
                        printf("탱크\n");
                    }
                    else if ((*u).NAME == 'V')
                    {
                        printf("베슬\n");
                    }
                    printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*u).HP, (*u).MP, (*u).MOVE, (*u).CRD, (*u).ATT, (*u).UMP, (*u).RANGE, (*u).ACT, (*u).X, (*u).Y, (*u).ID);
                }
            }
        }
        u++;
        size--;
        SelectAll_UL_R(u, size, x1, y1, x2, y2);
    }
}

void Destroy_UL_R(unitlist* u, int size, int x1, int y1)
{
    if (size != 0)
    {
        if ((*u).X == x1 && (*u).Y == y1)
        {
            /*(*u).HP = NULL;
            (*u).MP = NULL;
            (*u).MOVE = NULL;
            (*u).CRD = NULL;
            (*u).ATT = NULL;
            (*u).UMP = NULL;
            (*u).RANGE = NULL;
            (*u).ACT = NULL;
            (*u).X = NULL;
            (*u).Y = NULL;
            *(*u).ID = NULL;*/
            if ((*u).NAME == 'H')
            {
                (*u).NAME = 'h';
            }
            else if ((*u).NAME == 'Q')
            {
                (*u).NAME = 'q';
            }
            else if ((*u).NAME == 'D')
            {
                (*u).NAME = 'd';
            }
            else if ((*u).NAME == 'M')
            {
                (*u).NAME = 'm';
            }
            else if ((*u).NAME == 'T')
            {
                (*u).NAME = 't';
            }
            else if ((*u).NAME == 'V')
            {
                (*u).NAME = 'v';
            }
        }
        else
        {
            u++;
            size--;
            Destroy_UL_R(u, size, x1, y1);
        }
    }
}

void FindWeakEnemy_R(unitlist* u, int size, int x1, int y1, int dis, int* p, int index1, int index2)
{
    if (size != 0)
    {
        if ((*u).NAME == 'H' || (*u).NAME == 'Q' || (*u).NAME == 'D' || (*u).NAME == 'M' || (*u).NAME == 'T' || (*u).NAME == 'V')
        {
            int length;
            if (abs(x1 - (*u).X) >= abs(y1 - (*u).Y))
            {
                length = abs(x1 - (*u).X);
            }
            else
            {
                length = abs(y1 - (*u).Y);
            }
            if (length <= dis)
            {
                *(p + index1) = index2;
                index1++;
            }
        }
        index2++;
        u++;
        size--;
        if (size == 0)
        {
            u = u - index2;
            dis = index1;
            index2 = 0;
        }
        FindWeakEnemy_R(u, size, x1, y1, dis, p, index1, index2);
    }
    else if (size == 0)
    {
        if (dis != 1)
        {
            if ((*(u + *(p + index2))).HP > (*(u + *(p + index2 + 1))).HP)
            {
                int cmp = *(p + index2);
                *(p + index2) = *(p + index2 + 1);
                *(p + index2 + 1) = cmp;
            }
            index2++;
            if (index2 == index1 - 1)
            {
                index2 = 0;
                dis--;
            }
            FindWeakEnemy_R(u, size, x1, y1, dis, p, index1, index2);
        }
        else if (dis == 1)
        {
            if (index1 != 1)
            {
                if ((*(u + *(p + index2))).HP == (*(u + *(p + index2 + 1))).HP)
                {
                    if ((*(u + *(p + index2))).NAME == 'H')
                    {
                        printf("히드라\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'Q')
                    {
                        printf("퀸\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'D')
                    {
                        printf("디파일러\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'M')
                    {
                        printf("마린\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'T')
                    {
                        printf("탱크\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'V')
                    {
                        printf("베슬\n");
                    }
                    printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*(u + *(p + index2))).HP, (*(u + *(p + index2))).MP, (*(u + *(p + index2))).MOVE, (*(u + *(p + index2))).CRD, (*(u + *(p + index2))).ATT, (*(u + *(p + index2))).UMP, (*(u + *(p + index2))).RANGE, (*(u + *(p + index2))).ACT, (*(u + *(p + index2))).X, (*(u + *(p + index2))).Y, (*(u + *(p + index2))).ID);
                    index2++;
                    index1--;
                    FindWeakEnemy_R(u, size, x1, y1, dis, p, index1, index2);
                }
                else
                {
                    if ((*(u + *(p + index2))).NAME == 'H')
                    {
                        printf("히드라\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'Q')
                    {
                        printf("퀸\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'D')
                    {
                        printf("디파일러\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'M')
                    {
                        printf("마린\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'T')
                    {
                        printf("탱크\n");
                    }
                    else if ((*(u + *(p + index2))).NAME == 'V')
                    {
                        printf("베슬\n");
                    }
                    printf("체력 : %d \t 마나 : %d \t 이동거리 : %d \n사거리 : %d \t 공격력 : %d \t 소모 마나 : %d\n공격범위 : %d \t 행동력 : %d \nX좌표 : %d \t Y좌표 : %d \t ID : %s\n\n\n", (*(u + *(p + index2))).HP, (*(u + *(p + index2))).MP, (*(u + *(p + index2))).MOVE, (*(u + *(p + index2))).CRD, (*(u + *(p + index2))).ATT, (*(u + *(p + index2))).UMP, (*(u + *(p + index2))).RANGE, (*(u + *(p + index2))).ACT, (*(u + *(p + index2))).X, (*(u + *(p + index2))).Y, (*(u + *(p + index2))).ID);
                }
            }
        }
    }
}