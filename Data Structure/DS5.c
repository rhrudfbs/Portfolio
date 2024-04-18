#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void MENU();
int decode();
void ShowUL_R();
void Select_UL_R();
void Destroy_UL_R();

typedef struct
{
	int HP, MP, MOVE, CRD, ATT, UMP, RANGE, ACT, X, Y;
	char ID[10];
	char NAME;
}unitlist;

int main()
{
	int num = 20;
	unitlist UNIT[800] = { {.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 15, .ID = "H0001"},
		{.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 39, .Y = 16, .ID = "H0002"},
		{.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 39, .Y = 17, .ID = "H0003"},
		{.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 38, .Y = 18, .ID = "H0004"},
		{.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 19, .ID = "H0005"},
		{.NAME = 'H', .HP = 50, .MP = 0, .MOVE = 3, .CRD = 5, .ATT = 25, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 40, .Y = 20, .ID = "H0006"},
		{.NAME = 'Q', .HP = 70, .MP = 150, .MOVE = 6, .CRD = 15, .ATT = 1000, .UMP = 45, .RANGE = 1, .ACT = 2, .X = 40, .Y = 18, .ID = "Q0001"},
		{.NAME = 'Q', .HP = 70, .MP = 150, .MOVE = 6, .CRD = 15, .ATT = 1000, .UMP = 45, .RANGE = 1, .ACT = 2, .X = 39, .Y = 18, .ID = "Q0002"},
		{.NAME = 'D', .HP = 60, .MP = 200, .MOVE = 2, .CRD = 10, .ATT = -1, .UMP = 60, .RANGE = 5, .ACT = 2, .X = 40, .Y = 16, .ID = "D0001"},
		{.NAME = 'D', .HP = 60, .MP = 200, .MOVE = 2, .CRD = 10, .ATT = -1, .UMP = 60, .RANGE = 5, .ACT = 2, .X = 40, .Y = 17, .ID = "D0002"},
		{.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 1, .ID = "M0001"},
		{.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 2, .ID = "M0002"},
		{.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 3, .ID = "M0003"},
		{.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 2, .Y = 4, .ID = "M0004"},
		{.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 2, .Y = 5, .ID = "M0005"},
		{.NAME = 'M', .HP = 30, .MP = 0, .MOVE = 3, .CRD = 4, .ATT = 20, .UMP = 0, .RANGE = 1, .ACT = 1, .X = 1, .Y = 6, .ID = "M0006"},
		{.NAME = 'T', .HP = 120, .MP = 0, .MOVE = 4, .CRD = 17, .ATT = 40, .UMP = 0, .RANGE = 1, .ACT = 2, .X = 1, .Y = 4, .ID = "T0001"},
		{.NAME = 'T', .HP = 120, .MP = 0, .MOVE = 4, .CRD = 17, .ATT = 40, .UMP = 0, .RANGE = 1, .ACT = 2, .X = 1, .Y = 5, .ID = "T0002"},
		{.NAME = 'V', .HP = 80, .MP = 140, .MOVE = 5, .CRD = 12, .ATT = 50, .UMP = 35, .RANGE = 3, .ACT = 2, .X = 2, .Y = 3, .ID = "V0001"},
		{.NAME = 'V', .HP = 80, .MP = 140, .MOVE = 5, .CRD = 12, .ATT = 50, .UMP = 35, .RANGE = 3, .ACT = 2, .X = 3, .Y = 3, .ID = "V0002"} };
	for (int j = 1; j <= 20; j++)
	{
		for (int k = 1; k <= 40; k++)
		{
			int ox = 0;
			for (int i = 0; i <= num - 1; i++)
			{
				if (UNIT[i].X == k && UNIT[i].Y == j)
				{
					printf("%c", UNIT[i].NAME);
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
	while (1)
	{
		int menu, msg, x, y;
		MENU();
		scanf_s("%d%*c", &menu);
		system("cls");
		if (menu == 1)
		{
			for (int i = 0; i <= num - 1; i++)
			{
				printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", UNIT[i].HP, UNIT[i].MP, UNIT[i].X, UNIT[i].Y, UNIT[i].ID);
			}
		}
		else if (menu == 2)
		{
			ShowUL_R(UNIT, num);
		}
		else if (menu == 3)
		{
			printf("S 40 15 와 같은 방식으로 명령어를 입력하시오\n");
			msg = decode();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				int ox = 0;
				for (int i = 0; i <= num - 1; i++)
				{
					if (UNIT[i].X == x && UNIT[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", UNIT[i].HP, UNIT[i].MP, UNIT[i].X, UNIT[i].Y, UNIT[i].ID);
						ox = 1;
					}
				}
				if (ox == 0)
				{
					printf("유닛이 없는 좌표입니다\n");
				}
			}
			else
			{
				printf("좌표값이 잘못되었습니다\n");
			}
		}
		else if (menu == 4)
		{
			printf("S 40 15 와 같은 방식으로 명령어를 입력하시오\n");
			msg = decode();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				Select_UL_R(UNIT, x, y, num);
			}
			else
			{
				printf("좌표값이 잘못되었습니다\n");
			}
		}
		else if (menu == 5)
		{
			printf("D 40 15 와 같은 방식으로 명령어를 입력하시오\n");
			msg = decode();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				int ox = 0;
				for (int i = 0; i <= num - 1; i++)
				{
					if (UNIT[i].X == x && UNIT[i].Y == y)
					{
						*(UNIT[i].ID) = NULL;
						UNIT[i].NAME = NULL, UNIT[i].HP = NULL, UNIT[i].MP = NULL, UNIT[i].MOVE = NULL, UNIT[i].CRD = NULL, UNIT[i].ATT = NULL, UNIT[i].UMP = NULL, UNIT[i].RANGE = NULL, UNIT[i].ACT = NULL, UNIT[i].X = NULL, UNIT[i].Y = NULL;
						ox = 1;
					}
				}
				if (ox == 0)
				{
					printf("유닛이 없는 좌표입니다\n");
				}
			}
			else
			{
				printf("좌표값이 잘못되었습니다\n");
			}
		}
		else if (menu == 6)
		{
			printf("D 40 15 와 같은 방식으로 명령어를 입력하시오\n");
			msg = decode();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				Destroy_UL_R(UNIT, x, y, num);
			}
			else
			{
				printf("좌표값이 잘못되었습니다\n");
			}
		}
		else if (menu == 7)
		{
			for (int j = 1; j <= 20; j++)
			{
				for (int k = 1; k <= 40; k++)
				{
					int ox = 0;
					for (int i = 0; i <= num - 1; i++)
					{
						if (UNIT[i].X == k && UNIT[i].Y == j)
						{
							printf("%c", UNIT[i].NAME);
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
		for (int j = 0; j < num - 1; j++)//이번 시험에서 데이터를 지울 때는 한 배열만 지우므로 이렇게 코드 짰습니다. 빈 곳 뒤로 보내고 배열 앞으로 당기는 코드
		{
			for (int i = 0; i < num - 1; i++)
			{
				if (UNIT[i].X == 0)
				{
					for (int k = 0; k <= 10; k++)
					{
						*(UNIT[i].ID + k) = *(UNIT[i + 1].ID + k);
					}
					UNIT[i].NAME = UNIT[i + 1].NAME, UNIT[i].HP = UNIT[i + 1].HP, UNIT[i].MP = UNIT[i + 1].MP, UNIT[i].MOVE = UNIT[i + 1].MOVE, UNIT[i].CRD = UNIT[i + 1].CRD, UNIT[i].ATT = UNIT[i + 1].ATT, UNIT[i].UMP = UNIT[i + 1].UMP, UNIT[i].RANGE = UNIT[i + 1].RANGE, UNIT[i].ACT = UNIT[i + 1].ACT, UNIT[i].X = UNIT[i + 1].X, UNIT[i].Y = UNIT[i + 1].Y;
					*(UNIT[i + 1].ID) = NULL;
					UNIT[i + 1].NAME = NULL, UNIT[i + 1].HP = NULL, UNIT[i + 1].MP = NULL, UNIT[i + 1].MOVE = NULL, UNIT[i + 1].CRD = NULL, UNIT[i + 1].ATT = NULL, UNIT[i + 1].UMP = NULL, UNIT[i + 1].RANGE = NULL, UNIT[i + 1].ACT = NULL, UNIT[i + 1].X = NULL, UNIT[i + 1].Y = NULL;
				}
			}
		}
		for (int i = 0; i <= num - 1; i++)
		{
			if (UNIT[i].X == 0)
			{
				num--;
			}
		}
	}
}

void MENU()
{
	printf("1. ShowUL\n");
	printf("2. ShowUL_R\n");
	printf("3. Select_UL\n");
	printf("4. Select_UL_R\n");
	printf("5. Destroy_UL\n");
	printf("6. Destroy_UL_R\n");
	printf("7. DisplayMap_UL\n");
}

int decode()
{
	int cmd, x11, x12, y11, y12;
	char* msg = (char*)malloc(sizeof(char) * 20);
	gets_s(msg, sizeof(char) * 20);
	if (*(msg + 3) >= '0' && *(msg + 3) <= '9')
	{
		x11 = *(msg + 2) - 48;
		x12 = *(msg + 3) - 48;
		if (*(msg + 6) >= '0' && *(msg + 6) <= '9')
		{
			y11 = *(msg + 5) - 48;
			y12 = *(msg + 6) - 48;
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 5) - 48;
		}
	}
	else
	{
		x11 = 0;
		x12 = *(msg + 2) - 48;
		if (*(msg + 5) >= '0' && *(msg + 5) <= '9')
		{
			y11 = *(msg + 4) - 48;
			y12 = *(msg + 5) - 48;
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 4) - 48;
		}
	}
	cmd = x11 * 1000 + x12 * 100 + y11 * 10 + y12;
	free(msg);
	return cmd;
}

void ShowUL_R(unitlist* u, int size)
{
	if (size != 0)
	{
		printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", (*u).HP, (*u).MP, (*u).X, (*u).Y, (*u).ID);
		u++;
		size--;
		ShowUL_R(u, size);
	}
}

void Select_UL_R(unitlist* u, int x, int y, int size)
{
	if (size != 0)
	{
		if ((*u).X == x && (*u).Y == y)
		{
			printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", (*u).HP, (*u).MP, (*u).X, (*u).Y, (*u).ID);
			size = 0;
		}
		else
		{
			u++;
			size--;
			Select_UL_R(u, x, y, size);
		}
	}
}

void Destroy_UL_R(unitlist* u, int x, int y, int size)
{
	if (size != 0)
	{
		if ((*u).X == x && (*u).Y == y)
		{
			*((*u).ID) = NULL;
			(*u).NAME = NULL, (*u).HP = NULL, (*u).MP = NULL, (*u).MOVE = NULL, (*u).CRD = NULL, (*u).ATT = NULL, (*u).UMP = NULL, (*u).RANGE = NULL, (*u).ACT = NULL, (*u).X = NULL, (*u).Y = NULL;
			size = 0;
		}
		else
		{
			u++;
			size--;
			Destroy_UL_R(u, x, y, size);
		}
	}
}