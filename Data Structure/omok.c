#include <stdio.h>
#include <Windows.h>

void Reset();
void ResetBag();
void ResetChecker();
void Display();
void Play();


void ACheckAll();
void CheckHorizon();
void CheckVertical();
void CheckCross();
void CheckIncross();


void TransRow();
void TransRowInfo();
int CheckTopRow();
int TopRowCount();


void Defend();
int CheckTopRow_2();
int TopRowCount_2();


int RealBlankCheck();
int BlankCheck();
int RealBlockCheck();
int BlockedBlackCheck();
int BlockedWhiteCheck();

#define Blank 0
#define BlackTurn 0
#define WhiteTurn 1
#define Black 1
#define White 2
#define MBlack 3
#define MWhite 4
#define FBlack 5
#define FWhite 6

int main(void)
{
	system("color 70");
	int bag[19][19], horizon[19][19], vertical[19][19], cross[19][19], incross[19][19];
	int turn = 0;
	Reset(bag);
	while(1)
	{
		ResetBag(bag);
		ResetChecker(horizon, vertical, cross, incross);
		ACheckAll(bag, horizon, vertical, cross, incross);
		TransRow(bag, horizon, vertical, cross, incross);
		Defend(horizon, vertical, cross, incross, bag, &turn);
		Display(bag);
		TransRowInfo(bag, horizon, vertical, cross, incross);
		Play(bag, &turn);
	}
	return 0;
}


void Reset(int* obj)
{
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			*obj = 0;
			obj++;
		}
	}
}

void ResetBag(int* bag)
{
	for (int i = 0; i < 361; i++)
	{
		if (*bag == MBlack)
		{
			*bag = Black;
		}
		else if (*bag == MWhite)
		{
			*bag = White;
		}
		else if (*bag == FBlack || *bag == FWhite)
		{
			*bag = Blank;
		}
		bag++;
	}
}

void ResetChecker(int* horizon, int* vertical, int* cross, int* incross)
{
	for (int i = 0; i < 361; i++)
	{
		*horizon = 0;
		*vertical = 0;
		*cross = 0;
		*incross = 0;
		horizon++;
		vertical++;
		cross++;
		incross++;
	}
}

void Display(int* obj)
{
	int black_data = 0, white_data = 0;
	printf("    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18\n");
	for (int y = 0; y < 19; y++)
	{
		if (y < 10)
			printf("%d ", y);
		else printf("%d", y);
		for (int x = 0; x < 19; x++)
		{
			if (*obj == Blank)
			{
				printf(" ┼  ");
			}
			else if (*obj == Black)
			{
				printf(" ● ");
				black_data++;
			}
			else if (*obj == White)
			{
				printf(" ○ ");
				white_data++;
			}
			else if (*obj == MBlack)
			{
				printf(" ■ ");
				black_data++;
			}
			else if (*obj == MWhite)
			{
				printf(" □ ");
				white_data++;
			}
			else if (*obj == FBlack)
			{
				printf(" ★ ");
			}
			else if (*obj == FWhite)
			{
				printf(" ☆ ");
			}
			obj++;
		}
		printf("\n\n");
	}
	printf("흑돌의 개수 : %d\n", black_data);
	printf("백돌의 개수 : %d\n", white_data);
}

void Play(int* bag, int* turn)
{
	int x, y;
	printf("좌표를 입력하십시오\n");
	scanf_s("%d %d%*c", &x, &y);
	int* point = bag + x + y * 19;
	if (x >= 0 && x <= 18 && y >= 0 && y <= 18)
	{
		if (RealBlankCheck(point))
		{
			if (*turn % 2 == BlackTurn)
			{
				*point = Black;
				(*turn)++;
			}
			else if (*turn % 2 == WhiteTurn)
			{
				*point = White;
				(*turn)++;
			}
		}
		else printf("이미 돌이 놓여져 있습니다\n");
	}
	else printf("잘못된 좌표값입니다\n");
}



void ACheckAll(int* bag, int* horizon, int* vertical, int* cross, int* incross)
{
	CheckHorizon(bag, horizon);
	CheckVertical(bag, vertical);
	CheckCross(bag, cross);
	CheckIncross(bag, incross);
}

void CheckHorizon(int* bag, int* horizon)
{
	for (int y = 0; y <= 18; y++)
	{
		for (int x = 0; x <= 18; x++)
		{
			if (BlockedBlackCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(horizon + x + y * 19))++;
				for (int X = x + 1, Y = y; X <= 18; X++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedBlackCheck(bag + X + Y * 19))
						{
							(*(horizon + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(horizon + x + y * 19))++;
				for (int X = x + 1, Y = y; X <= 18; X++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedWhiteCheck(bag + X + Y * 19))
						{
							(*(horizon + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
		}
	}
}

void CheckVertical(int* bag, int* vertical)
{
	for (int x = 0; x <= 18; x++)
	{
		for (int y = 0; y <= 18; y++)
		{
			if (BlockedBlackCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(vertical + x + y * 19))++;
				for (int X = x, Y = y + 1; Y <= 18; Y++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedBlackCheck(bag + X + Y * 19))
						{
							(*(vertical + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(vertical + x + y * 19))++;
				for (int X = x, Y = y + 1; Y <= 18; Y++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedWhiteCheck(bag + X + Y * 19))
						{
							(*(vertical + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
		}
	}
}

void CheckCross(int* bag, int* cross)
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int x = 0, y = Z; y <= 18; x++, y++)
		{
			if (BlockedBlackCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(cross + x + y * 19))++;
				for (int X = x + 1, Y = y + 1; Y <= 18; X++, Y++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedBlackCheck(bag + X + Y * 19))
						{
							(*(cross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(cross + x + y * 19))++;
				for (int X = x + 1, Y = y + 1; Y <= 18; X++, Y++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedWhiteCheck(bag + X + Y * 19))
						{
							(*(cross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int x = Z, y = 0; x <= 18; x++, y++)
		{
			if (BlockedBlackCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(cross + x + y * 19))++;
				for (int X = x + 1, Y = y + 1; X <= 18; X++, Y++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedBlackCheck(bag + X + Y * 19))
						{
							(*(cross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(cross + x + y * 19))++;
				for (int X = x + 1, Y = y + 1; X <= 18; X++, Y++)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedWhiteCheck(bag + X + Y * 19))
						{
							(*(cross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
		}
	}
}

void CheckIncross(int* bag, int* incross)
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int x = 0, y = Z; y >= 0; x++, y--)
		{
			if (BlockedBlackCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(incross + x + y * 19))++;
				for (int X = x + 1, Y = y - 1; Y >= 0; X++, Y--)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedBlackCheck(bag + X + Y * 19))
						{
							(*(incross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(incross + x + y * 19))++;
				for (int X = x + 1, Y = y - 1; Y >= 0; X++, Y--)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedWhiteCheck(bag + X + Y * 19))
						{
							(*(incross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int x = Z, y = 18; x <= 18; x++, y--)
		{
			if (BlockedBlackCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(incross + x + y * 19))++;
				for (int X = x + 1, Y = y - 1; Y >= 0; X++, Y--)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedBlackCheck(bag + X + Y * 19))
						{
							(*(incross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19))
			{
				int count = 0;
				(*(incross + x + y * 19))++;
				for (int X = x + 1, Y = y - 1; Y >= 0; X++, Y--)
				{
					if (X >= 0 && X <= 18 && Y >= 0 && Y <= 18)
					{
						if (BlockedWhiteCheck(bag + X + Y * 19))
						{
							(*(incross + x + y * 19))++;
						}
						else if (RealBlankCheck(bag + X + Y * 19))
						{
							if (count == 0)
							{
								count++;
							}
							else if (count == 1)
							{
								break;
							}
						}
						else break;
					}
				}
			}
		}
	}
}



void TransRow(int* bag, int* horizon, int* vertical, int* cross, int* incross)
{
	int cmp = CheckTopRow(bag, horizon, vertical, cross, incross);
	int count = TopRowCount(bag, horizon, vertical, cross, incross, cmp);
	int i = 0;
	if (count != 0)
	{
		int* sort = (int*)malloc(sizeof(int*) * count);
		int* loc_x = (int*)malloc(sizeof(int*) * count);
		int* loc_y = (int*)malloc(sizeof(int*) * count);
		for (int y = 0; y <= 18; y++)
		{
			for (int x = 0; x <= 18; x++)
			{
				if (*(bag + x + y * 19) != Blank)
				{
					if (*(horizon + x + y * 19) == cmp)
					{
						sort[i] = 1;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(vertical + x + y * 19) == cmp)
					{
						sort[i] = 2;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(cross + x + y * 19) == cmp)
					{
						sort[i] = 3;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(incross + x + y * 19) == cmp)
					{
						sort[i] = 4;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
				}
			}
		}
		for (int j = 0; j < count; j++)
		{
			if (sort[j] == 1)
			{
				int space = 0;
				for (int k = 0; k < cmp; k++)
				{
					int* startbag = bag + loc_x[j] + loc_y[j] * 19;
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k + space;
					if (*startbag == Black || *startbag == MBlack)
					{
						if (*checkbag != Black && *checkbag != MBlack)
						{
							k--;
							space++;
						}
						else *checkbag = MBlack;
					}
					else if (*startbag == White || *startbag == MWhite)
					{
						if (*checkbag != White && *checkbag != MWhite)
						{
							k--;
							space++;
						}
						else *checkbag = MWhite;
					}
				}
			}
			else if (sort[j] == 2)
			{
				int space = 0;
				for (int k = 0; k < cmp; k++)
				{
					int* startbag = bag + loc_x[j] + loc_y[j] * 19;
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k * 19 + space * 19;
					if (*startbag == Black || *startbag == MBlack)
					{
						if (*checkbag != Black && *checkbag != MBlack)
						{
							space = 1;
							k--;
						}
						else *checkbag = MBlack;
					}
					else if (*startbag == White || *startbag == MWhite)
					{
						if (*checkbag != White && *checkbag != MWhite)
						{
							space = 1;
							k--;
						}
						else *checkbag = MWhite;
					}
				}
			}
			else if (sort[j] == 3)
			{
				int space = 0;
				for (int k = 0; k < cmp; k++)
				{
					int* startbag = bag + loc_x[j] + loc_y[j] * 19;
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k * 20 + space * 20;
					if (*startbag == Black || *startbag == MBlack)
					{
						if (*checkbag != Black && *checkbag != MBlack)
						{
							space = 1;
							k--;
						}
						else *checkbag = MBlack;
					}
					else if (*startbag == White || *startbag == MWhite)
					{
						if (*checkbag != White && *checkbag != MWhite)
						{
							space = 1;
							k--;
						}
						else *checkbag = MWhite;
					}
				}
			}
			else if (sort[j] == 4)
			{
				int space = 0;
				for (int k = 0; k < cmp; k++)
				{
					int* startbag = bag + loc_x[j] + loc_y[j] * 19;
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 - k * 18 - space * 18;
					if (*startbag == Black || *startbag == MBlack)
					{
						if (*checkbag != Black && *checkbag != MBlack)
						{
							space = 1;
							k--;
						}
						else *checkbag = MBlack;
					}
					else if (*startbag == White || *startbag == MWhite)
					{
						if (*checkbag != White && *checkbag != MWhite)
						{
							space = 1;
							k--;
						}
						else *checkbag = MWhite;
					}
				}
			}
		}
		free(sort);
		free(loc_x);
		free(loc_y);
	}
}

void TransRowInfo(int* bag, int* horizon, int* vertical, int* cross, int* incross)
{
	int cmp = CheckTopRow(bag, horizon, vertical, cross, incross);
	int count = TopRowCount(bag, horizon, vertical, cross, incross, cmp);
	int i = 0;
	if (count != 0)
	{
		int* sort = (int*)malloc(sizeof(int*) * count);
		int* loc_x = (int*)malloc(sizeof(int*) * count);
		int* loc_y = (int*)malloc(sizeof(int*) * count);
		for (int y = 0; y <= 18; y++)
		{
			for (int x = 0; x <= 18; x++)
			{
				if (*(bag + x + y * 19) != Blank)
				{
					if (*(horizon + x + y * 19) == cmp)
					{
						sort[i] = 1;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(vertical + x + y * 19) == cmp)
					{
						sort[i] = 2;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(cross + x + y * 19) == cmp)
					{
						sort[i] = 3;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(incross + x + y * 19) == cmp)
					{
						sort[i] = 4;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
				}
			}
		}
		if (cmp > 1)
		{
			printf("한 칸 떨어진 것 포함 연속으로 놓인 돌의 개수가 많은 것을 흑돌은 ■, 백돌은 □로 표시\n");
			printf("한 칸 떨어진 것 포함 연속으로 놓인 돌의 개수가 많은 것들의 좌표 리스트\n");
			for (int j = 0; j < count; j++)
			{
				int* startbag = bag + loc_x[j] + loc_y[j] * 19;
				if (*startbag == Black || *startbag == MBlack)
				{
					printf("흑돌\n");
				}
				else if (*startbag == White || *startbag == MWhite)
				{
					printf("백돌\n");
				}
				if (sort[j] == 1)
				{
					int space = 0;
					for (int k = 0; k < cmp; k++)
					{
						int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k + space;
						if (*startbag == Black || *startbag == MBlack)
						{
							if (*checkbag != Black && *checkbag != MBlack)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j] + k + space, loc_y[j]);
						}
						else if (*startbag == White || *startbag == MWhite)
						{
							if (*checkbag != White && *checkbag != MWhite)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j] + k + space, loc_y[j]);
						}
					}
				}
				else if (sort[j] == 2)
				{
					int space = 0;
					for (int k = 0; k < cmp; k++)
					{
						int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k * 19 + space * 19;
						if (*startbag == Black || *startbag == MBlack)
						{
							if (*checkbag != Black && *checkbag != MBlack)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j], loc_y[j] + k + space);
						}
						else if (*startbag == White || *startbag == MWhite)
						{
							if (*checkbag != White && *checkbag != MWhite)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j], loc_y[j] + k + space);
						}
					}
				}
				else if (sort[j] == 3)
				{
					int space = 0;
					for (int k = 0; k < cmp; k++)
					{
						int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k * 20 + space * 20;
						if (*startbag == Black || *startbag == MBlack)
						{
							if (*checkbag != Black && *checkbag != MBlack)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j] + k + space, loc_y[j] + k + space);
						}
						else if (*startbag == White || *startbag == MWhite)
						{
							if (*checkbag != White && *checkbag != MWhite)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j] + k + space, loc_y[j] + k + space);
						}
					}
				}
				else if (sort[j] == 4)
				{
					int space = 0;
					for (int k = 0; k < cmp; k++)
					{
						int* checkbag = bag + loc_x[j] + loc_y[j] * 19 - k * 18 - space * 18;
						if (*startbag == Black || *startbag == MBlack)
						{
							if (*checkbag != Black && *checkbag != MBlack)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j] + k + space, loc_y[j] - k - space);
						}
						else if (*startbag == White || *startbag == MWhite)
						{
							if (*checkbag != White && *checkbag != MWhite)
							{
								space = 1;
								k--;
							}
							else printf("%d %d\n", loc_x[j] + k + space, loc_y[j] - k - space);
						}
					}
				}
				printf("----------\n");
			}
		}
		printf("상대방의 공격을 막아야 할 때 백돌이 놓아야 할 위치는 ☆, 흑돌이 놓아야 할 위치는 ★\n");
		free(sort);
		free(loc_x);
		free(loc_y);
	}
}

int CheckTopRow(int* bag, int* horizon, int* vertical, int* cross, int* incross)
{
	int cmp = 0;
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (RealBlockCheck(bag + x + y * 19))
			{
				if (*(horizon + x + y * 19) > cmp)
				{
					cmp = *(horizon + x + y * 19);
				}
				if (*(vertical + x + y * 19) > cmp)
				{
					cmp = *(vertical + x + y * 19);
				}
				if (*(cross + x + y * 19) > cmp)
				{
					cmp = *(cross + x + y * 19);
				}
				if (*(incross + x + y * 19) > cmp)
				{
					cmp = *(incross + x + y * 19);
				}
			}
		}
	}
	return cmp;
}

int TopRowCount(int* bag, int* horizon, int* vertical, int* cross, int* incross, int cmp)
{
	int count = 0;
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (RealBlockCheck(bag + x + y * 19))
			{
				if (*(horizon + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(vertical + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(cross + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(incross + x + y * 19) == cmp)
				{
					count++;
				}
			}
		}
	}
	return count;
}



void Defend(int* horizon, int* vertical, int* cross, int* incross, int* bag, int* turn)
{
	int cmp = CheckTopRow_2(bag, horizon, vertical, cross, incross, turn);
	int count = TopRowCount_2(bag, horizon, vertical, cross, incross, cmp, turn);
	int i = 0;
	if (count != 0)
	{
		int* sort = (int*)malloc(sizeof(int*) * count);
		int* loc_x = (int*)malloc(sizeof(int*) * count);
		int* loc_y = (int*)malloc(sizeof(int*) * count);
		for (int y = 0; y <= 18; y++)
		{
			for (int x = 0; x <= 18; x++)
			{
				if (BlockedBlackCheck(bag + x + y * 19) && *turn % 2 == WhiteTurn)
				{
					if (*(horizon + x + y * 19) == cmp)
					{
						sort[i] = 1;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(vertical + x + y * 19) == cmp)
					{
						sort[i] = 2;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(cross + x + y * 19) == cmp)
					{
						sort[i] = 3;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(incross + x + y * 19) == cmp)
					{
						sort[i] = 4;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
				}
				else if (BlockedWhiteCheck(bag + x + y * 19) && *turn % 2 == BlackTurn)
				{
					if (*(horizon + x + y * 19) == cmp)
					{
						sort[i] = 1;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(vertical + x + y * 19) == cmp)
					{
						sort[i] = 2;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(cross + x + y * 19) == cmp)
					{
						sort[i] = 3;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
					if (*(incross + x + y * 19) == cmp)
					{
						sort[i] = 4;
						loc_x[i] = x;
						loc_y[i] = y;
						i++;
					}
				}
			}
		}
		for (int j = 0; j < count; j++)
		{
			if (sort[j] == 1)
			{
				int space = 0;
				int* startbag = bag + loc_x[j] + loc_y[j] * 19 - 1;
				int forwardcheck = *startbag;
				if (loc_x[j] != 0 && *turn % 2 == BlackTurn && RealBlankCheck(startbag))
				{
					*startbag = FBlack;
				}
				else if (loc_x[j] != 0 && *turn % 2 == WhiteTurn && RealBlankCheck(startbag))
				{
					*startbag = FWhite;
				}
				for (int k = 0; k < cmp; k++)
				{
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k + space;
					if (RealBlankCheck(checkbag))
					{
						if (*turn % 2 == BlackTurn)
						{
							if (cmp == 3 && (BlockedBlackCheck(startbag) || BlockedBlackCheck(bag + loc_x[j] + loc_y[j] * 19 + cmp + 1)))
							{
								//그냥 넘어가기
							}
							else if (cmp == 3 && loc_x[j] == 0)//***********
							{
								
							}
							else if (cmp == 3 && loc_x + cmp + 1 - 1 == 18)//***********
							{
								
							}
							else *checkbag = FBlack;
						}
						else if (*turn % 2 == WhiteTurn)
						{
							if (cmp == 3 && (BlockedWhiteCheck(startbag) || BlockedWhiteCheck(bag + loc_x[j] + loc_y[j] * 19 + cmp + 1)))
							{
								//그냥 넘어가기
							}
							else if (cmp == 3 && loc_x[j] == 0)//***********
							{

							}
							else if (cmp == 3 && loc_x + cmp + 1 - 1 == 18)//***********
							{

							}
							else *checkbag = FWhite;
						}
						space = 1;
						k--;
					}
				}
				int* finalbag = bag + loc_x[j] + loc_y[j] * 19 + cmp + space;
				int backwardcheck = *finalbag;
				int final_x = loc_x[j] + cmp + space - 1;
				if (final_x != 18 && *turn % 2 == BlackTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FBlack;
				}
				else if (final_x != 18 && *turn % 2 == WhiteTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FWhite;
				}
				if (*turn % 2 == BlackTurn && cmp == 3)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (loc_x[j] == 0 && BlankCheck(&backwardcheck))//***********
					{
						*finalbag = Blank;
					}
					else if (final_x == 18 && BlankCheck(&forwardcheck))//***********
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == BlackTurn && cmp == 4 && space == 1)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 3)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (loc_x[j] == 0 && BlankCheck(&backwardcheck))//***********
					{
						*finalbag = Blank;
					}
					else if (final_x == 18 && BlankCheck(&forwardcheck))//***********
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 4 && space == 1)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
			}
			else if (sort[j] == 2)
			{
				int space = 0;
				int* startbag = bag + loc_x[j] + loc_y[j] * 19 - 19;
				int forwardcheck = *startbag;
				if (loc_y[j] != 0 && *turn % 2 == BlackTurn && RealBlankCheck(startbag))
				{
					*startbag = FBlack;
				}
				else if (loc_y[j] != 0 && *turn % 2 == WhiteTurn && RealBlankCheck(startbag))
				{
					*startbag = FWhite;
				}
				for (int k = 0; k < cmp; k++)
				{
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k * 19 + space * 19;
					if (RealBlankCheck(checkbag))
					{
						if (*turn % 2 == BlackTurn)
						{
							if (cmp == 3 && (BlockedBlackCheck(startbag) || BlockedBlackCheck(bag + loc_x[j] + loc_y[j] * 19 + cmp * 19 + 1 * 19)))
							{

							}
							else if (cmp == 3 && loc_y[j] == 0)
							{
								
							}
							else if (cmp == 3 && loc_y[j] + cmp + 1 - 1 == 18)
							{
								
							}
							else *checkbag = FBlack;
						}
						else if (*turn % 2 == WhiteTurn)
						{
							if (cmp == 3 && (BlockedWhiteCheck(startbag) || BlockedWhiteCheck(bag + loc_x[j] + loc_y[j] * 19 + cmp * 19 + 1 * 19)))
							{

							}
							else if (cmp == 3 && loc_y[j] == 0)
							{

							}
							else if (cmp == 3 && loc_y[j] + cmp + 1 - 1 == 18)
							{

							}
							else *checkbag = FWhite;
						}
						space = 1;
						k--;
					}
				}
				int* finalbag = bag + loc_x[j] + loc_y[j] * 19 + cmp * 19 + space * 19;
				int backwardcheck = *finalbag;
				int final_y = loc_y[j] + cmp + space - 1;
				if (final_y != 18 && *turn % 2 == BlackTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FBlack;
				}
				else if (final_y != 18 && *turn % 2 == WhiteTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FWhite;
				}
				if (*turn % 2 == BlackTurn && cmp == 3)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (loc_y[j] == 0 && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (final_y == 18 && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == BlackTurn && cmp == 4 && space == 1)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 3)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (loc_y[j] == 0 && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (final_y == 18 && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 4 && space == 1)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
			}
			else if (sort[j] == 3)
			{
				int space = 0;
				int* startbag = bag + loc_x[j] + loc_y[j] * 19 - 1 - 19;
				int forwardcheck = *startbag;
				if (loc_x[j] != 0 && loc_y[j] != 0 && *turn % 2 == BlackTurn && RealBlankCheck(startbag))
				{
					*startbag = FBlack;
				}
				else if (loc_x[j] != 0 && loc_y[j] != 0 && *turn % 2 == WhiteTurn && RealBlankCheck(startbag))
				{
					*startbag = FWhite;
				}
				for (int k = 0; k < cmp; k++)
				{
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 + k * 20 + space * 20;
					if (RealBlankCheck(checkbag))
					{
						if (*turn % 2 == BlackTurn)
						{
							if (cmp == 3 && (BlockedBlackCheck(startbag) || BlockedBlackCheck(bag + loc_x[j] + loc_y[j] * 19 + cmp * 20 + 1 * 20)))
							{

							}
							else if (cmp == 3 && (loc_x[j] == 0 || loc_y[j] == 0))
							{
								
							}
							else if (cmp == 3 && (loc_x[j] + cmp + 1 - 1== 18 || loc_y[j] + cmp + 1 - 1== 18))
							{
								
							}
							else *checkbag = FBlack;
						}
						else if (*turn % 2 == WhiteTurn)
						{
							if (cmp == 3 && (BlockedWhiteCheck(startbag) || BlockedWhiteCheck(bag + loc_x[j] + loc_y[j] * 19 + cmp * 20 + 1 * 20)))
							{

							}
							else if (cmp == 3 && (loc_x[j] == 0 || loc_y[j] == 0))
							{

							}
							else if (cmp == 3 && (loc_x[j] + cmp + 1 - 1 == 18 || loc_y[j] + cmp + 1 - 1 == 18))
							{

							}
							else *checkbag = FWhite;
						}
						space = 1;
						k--;
					}
				}
				int* finalbag = bag + loc_x[j] + loc_y[j] * 19 + cmp * 20 + space * 20;
				int backwardcheck = *finalbag;
				int final_x = loc_x[j] + cmp + space - 1;
				int final_y = loc_y[j] + cmp + space - 1;
				if (final_x != 18 && final_y != 18 && *turn % 2 == BlackTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FBlack;
				}
				else if (final_x != 18 && final_y != 18 && *turn % 2 == WhiteTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FWhite;
				}
				if (*turn % 2 == BlackTurn && cmp == 3)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if ((loc_x[j] == 0 && BlankCheck(&backwardcheck)) || (loc_y[j] == 0 && BlankCheck(&backwardcheck)))
					{
						*finalbag = Blank;
					}
					else if ((final_x == 18 && BlankCheck(&forwardcheck)) || (final_y == 18 && BlankCheck(&forwardcheck)))
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == BlackTurn && cmp == 4 && space == 1)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 3)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if ((loc_x[j] == 0 && BlankCheck(&backwardcheck)) || (loc_y[j] == 0 && BlankCheck(&backwardcheck)))
					{
						*finalbag = Blank;
					}
					else if ((final_x == 18 && BlankCheck(&forwardcheck)) || (final_y == 18 && BlankCheck(&forwardcheck)))
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 4 && space == 1)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
			}
			else if (sort[j] == 4)
			{
				int space = 0;
				int* startbag = bag + loc_x[j] + loc_y[j] * 19 + 18;
				int forwardcheck = *startbag;
				if (loc_x[j] != 0 && loc_y[j] != 18 && *turn % 2 == BlackTurn && RealBlankCheck(startbag))
				{
					*startbag = FBlack;
				}
				else if (loc_x[j] != 0 && loc_y[j] != 18 && *turn % 2 == WhiteTurn && RealBlankCheck(startbag))
				{
					*startbag = FWhite;
				}
				for (int k = 0; k < cmp; k++)
				{
					int* checkbag = bag + loc_x[j] + loc_y[j] * 19 - k * 18 - space * 18;
					if (RealBlankCheck(checkbag))
					{
						if (*turn % 2 == BlackTurn)
						{
							if (cmp == 3 && (BlockedBlackCheck(startbag) || BlockedBlackCheck(bag + loc_x[j] + loc_y[j] * 19 - cmp * 18 - 1 * 18)))
							{

							}
							else if (cmp == 3 && (loc_x[j] == 0 || loc_y[j] == 18))
							{
								
							}
							else if (cmp == 3 && (loc_x[j] + cmp + 1 - 1 == 18 || loc_y[j] - cmp - 1 + 1 == 0))
							{
								
							}
							else *checkbag = FBlack;
						}
						else if (*turn % 2 == WhiteTurn)
						{
							if (cmp == 3 && (BlockedWhiteCheck(startbag) || BlockedWhiteCheck(bag + loc_x[j] + loc_y[j] * 19 - cmp * 18 - 1 * 18)))
							{

							}
							else if (cmp == 3 && (loc_x[j] == 0 || loc_y[j] == 18))
							{

							}
							else if (cmp == 3 && (loc_x[j] + cmp + 1 - 1 == 18 || loc_y[j] - cmp - 1 + 1 == 0))
							{

							}
							else *checkbag = FWhite;
						}
						space = 1;
						k--;
					}
				}
				int* finalbag = bag + loc_x[j] + loc_y[j] * 19 - cmp * 18 - space * 18;
				int backwardcheck = *finalbag;
				int final_x = loc_x[j] + cmp + space - 1;
				int final_y = loc_y[j] - cmp - space + 1;
				if (final_x != 18 && final_y != 0 && *turn % 2 == BlackTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FBlack;
				}
				else if (final_x != 18 && final_y != 0 && *turn % 2 == WhiteTurn && RealBlankCheck(finalbag))
				{
					*finalbag = FWhite;
				}
				if (*turn % 2 == BlackTurn && cmp == 3)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if ((loc_x[j] == 0 && BlankCheck(&backwardcheck)) || (loc_y[j] == 18 && BlankCheck(&backwardcheck)))
					{
						*finalbag = Blank;
					}
					else if ((final_x == 18 && BlankCheck(&forwardcheck)) || (final_y == 0 && BlankCheck(&forwardcheck)))
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == BlackTurn && cmp == 4 && space == 1)
				{
					if (BlockedBlackCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedBlackCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 3)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if ((loc_x[j] == 0 && BlankCheck(&backwardcheck)) || (loc_y[j] == 18 && BlankCheck(&backwardcheck)))
					{
						*finalbag = Blank;
					}
					else if ((final_x == 18 && BlankCheck(&forwardcheck)) || (final_y == 0 && BlankCheck(&forwardcheck)))
					{
						*startbag = Blank;
					}
				}
				else if (*turn % 2 == WhiteTurn && cmp == 4 && space == 1)
				{
					if (BlockedWhiteCheck(startbag) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
					}
					else if (BlockedWhiteCheck(finalbag) && BlankCheck(&forwardcheck))
					{
						*startbag = Blank;
					}
					else if (BlankCheck(&forwardcheck) && BlankCheck(&backwardcheck))
					{
						*finalbag = Blank;
						*startbag = Blank;
					}
				}
			}
		}
		free(sort);
		free(loc_x);
		free(loc_y);
	}
}

int CheckTopRow_2(int* bag, int* horizon, int* vertical, int* cross, int* incross, int* turn)
{
	int cmp = 3;
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (BlockedBlackCheck(bag + x + y * 19) && *turn % 2 == WhiteTurn)
			{
				if (*(horizon + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 - 1;
					int space = 0;
					for (int k = 0; k < *(horizon + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 + k + space;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 + *(horizon + x + y * 19) + space;
					int final_x = x + *(horizon + x + y * 19) + space - 1;
					if ((x == 0 && BlockedWhiteCheck(finalbag)) || (final_x == 18 && BlockedWhiteCheck(startbag)) || (BlockedWhiteCheck(finalbag) && BlockedWhiteCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(horizon + x + y * 19);
				}
				if (*(vertical + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 - 19;
					int space = 0;
					for (int k = 0; k < *(vertical + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 + k * 19 + space * 19;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 + *(vertical + x + y * 19) * 19 + space * 19;
					int final_y = y + *(vertical + x + y * 19) + space - 1;
					if ((y == 0 && BlockedWhiteCheck(finalbag)) || (final_y == 18 && BlockedWhiteCheck(startbag)) || (BlockedWhiteCheck(finalbag) && BlockedWhiteCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(vertical + x + y * 19);
				}
				if (*(cross + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 - 20;
					int space = 0;
					for (int k = 0; k < *(cross + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 + k * 20 + space * 20;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 + *(cross + x + y * 19) * 20 + space * 20;
					int final_x = x + *(cross + x + y * 19) + space - 1;
					int final_y = y + *(cross + x + y * 19) + space - 1;
					if ((*(cross + x + y * 19) == 3 && space == 0 && x == 0 && y == 16 && final_x == 2 && final_y == 18) || (*(cross + x + y * 19) == 4 && space == 0 && x == 0 && y == 15 && final_x == 3 && final_y == 18) || (*(cross + x + y * 19) == 3 && space == 1 && x == 0 && y == 15 && final_x == 3 && final_y == 18) || (*(cross + x + y * 19) == 3 && space == 0 && x == 16 && y == 0 && final_x == 18 && final_y == 2) || (*(cross + x + y * 19) == 4 && space == 0 && x == 15 && y == 0 && final_x == 18 && final_y == 3) || (*(cross + x + y * 19) == 3 && space == 1 && x == 15 && y == 0 && final_x == 18 && final_y == 3) || (x == 0 && BlockedWhiteCheck(finalbag)) || (y == 0 && BlockedWhiteCheck(finalbag)) || (final_x == 18 && BlockedWhiteCheck(startbag)) || (final_y == 18 && BlockedWhiteCheck(startbag)) || (BlockedWhiteCheck(finalbag) && BlockedWhiteCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(cross + x + y * 19);
				}
				if (*(incross + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 + 18;
					int space = 0;
					for (int k = 0; k < *(incross + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 - k * 18 - space * 18;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 - *(incross + x + y * 19) * 18 - space * 18;
					int final_x = x + *(incross + x + y * 19) + space - 1;
					int final_y = y - *(incross + x + y * 19) - space + 1;
					if ((*(incross + x + y * 19) == 3 && space == 0 && x == 0 && y == 2 && final_x == 2 && final_y == 0) || (*(incross + x + y * 19) == 4 && space == 0 && x == 0 && y == 3 && final_x == 3 && final_y == 0) || (*(incross + x + y * 19) == 3 && space == 1 && x == 0 && y == 3 && final_x == 3 && final_y == 0) || (*(incross + x + y * 19) == 3 && space == 0 && x == 16 && y == 18 && final_x == 18 & final_y == 16) || (*(incross + x + y * 19) == 4 && space == 0 && x == 15 && y == 18 && final_x == 18 && final_y == 15) || (*(incross + x + y * 19) == 3 && space == 1 && x == 15 && y == 18 && final_x == 18 && final_y == 15) || (x == 0 && BlockedWhiteCheck(finalbag)) || (y == 18 && BlockedWhiteCheck(finalbag)) || (final_x == 18 && BlockedWhiteCheck(startbag)) || (final_y == 0 && BlockedWhiteCheck(startbag)) || (BlockedWhiteCheck(finalbag) && BlockedWhiteCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(incross + x + y * 19);
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19) && *turn % 2 == BlackTurn)
			{
				if (*(horizon + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 - 1;
					int space = 0;
					for (int k = 0; k < *(horizon + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 + k + space;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 + *(horizon + x + y * 19) + space;
					int final_x = x + *(horizon + x + y * 19) + space - 1;
					if ((x == 0 && BlockedBlackCheck(finalbag)) || (final_x == 18 && BlockedBlackCheck(startbag)) || (BlockedBlackCheck(finalbag) && BlockedBlackCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(horizon + x + y * 19);
				}
				if (*(vertical + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 - 19;
					int space = 0;
					for (int k = 0; k < *(vertical + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 + k * 19 + space * 19;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 + *(vertical + x + y * 19) * 19 + space * 19;
					int final_y = y + *(vertical + x + y * 19) + space - 1;
					if ((y == 0 && BlockedBlackCheck(finalbag)) || (final_y == 18 && BlockedBlackCheck(startbag)) || (BlockedBlackCheck(finalbag) && BlockedBlackCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(vertical + x + y * 19);
				}
				if (*(cross + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 - 20;
					int space = 0;
					for (int k = 0; k < *(cross + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 + k * 20 + space * 20;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 + *(cross + x + y * 19) * 20 + space * 20;
					int final_x = x + *(cross + x + y * 19) + space - 1;
					int final_y = y + *(cross + x + y * 19) + space - 1;
					if ((*(cross + x + y * 19) == 3 && space == 0 && x == 0 && y == 16 && final_x == 2 && final_y == 18) || (*(cross + x + y * 19) == 4 && space == 0 && x == 0 && y == 15 && final_x == 3 && final_y == 18) || (*(cross + x + y * 19) == 3 && space == 1 && x == 0 && y == 15 && final_x == 3 && final_y == 18) || (*(cross + x + y * 19) == 3 && space == 0 && x == 16 && y == 0 && final_x == 18 && final_y == 2) || (*(cross + x + y * 19) == 4 && space == 0 && x == 15 && y == 0 && final_x == 18 && final_y == 3) || (*(cross + x + y * 19) == 3 && space == 1 && x == 15 && y == 0 && final_x == 18 && final_y == 3) || (x == 0 && BlockedBlackCheck(finalbag)) || (y == 0 && BlockedBlackCheck(finalbag)) || (final_x == 18 && BlockedBlackCheck(startbag)) || (final_y == 18 && BlockedBlackCheck(startbag)) || (BlockedBlackCheck(finalbag) && BlockedBlackCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(cross + x + y * 19);
				}
				if (*(incross + x + y * 19) > cmp)
				{
					int* startbag = bag + x + y * 19 + 18;
					int space = 0;
					for (int k = 0; k < *(incross + x + y * 19); k++)
					{
						int* checkbag = bag + x + y * 19 - k * 18 - space * 18;
						if (RealBlankCheck(checkbag))
						{
							if (space == 0)
							{
								space++;
								k--;
							}
							else break;
						}
					}
					int* finalbag = bag + x + y * 19 - *(incross + x + y * 19) * 18 - space * 18;
					int final_x = x + *(incross + x + y * 19) + space - 1;
					int final_y = y - *(incross + x + y * 19) - space + 1;
					if ((*(incross + x + y * 19) == 3 && space == 0 && x == 0 && y == 2 && final_x == 2 && final_y == 0) || (*(incross + x + y * 19) == 4 && space == 0 && x == 0 && y == 3 && final_x == 3 && final_y == 0) || (*(incross + x + y * 19) == 3 && space == 1 && x == 0 && y == 3 && final_x == 3 && final_y == 0) || (*(incross + x + y * 19) == 3 && space == 0 && x == 16 && y == 18 && final_x == 18 & final_y == 16) || (*(incross + x + y * 19) == 4 && space == 0 && x == 15 && y == 18 && final_x == 18 && final_y == 15) || (*(incross + x + y * 19) == 3 && space == 1 && x == 15 && y == 18 && final_x == 18 && final_y == 15) || (x == 0 && BlockedBlackCheck(finalbag)) || (y == 18 && BlockedBlackCheck(finalbag)) || (final_x == 18 && BlockedBlackCheck(startbag)) || (final_y == 0 && BlockedBlackCheck(startbag)) || (BlockedBlackCheck(finalbag) && BlockedBlackCheck(startbag)))
					{
						cmp = cmp;
					}
					else cmp = *(incross + x + y * 19);
				}
			}
		}
	}
	return cmp;
}

int TopRowCount_2(int* bag, int* horizon, int* vertical, int* cross, int* incross, int cmp, int* turn)
{
	int count = 0;
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (BlockedBlackCheck(bag + x + y * 19) && *turn % 2 == WhiteTurn)
			{
				if (*(horizon + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(vertical + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(cross + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(incross + x + y * 19) == cmp)
				{
					count++;
				}
			}
			else if (BlockedWhiteCheck(bag + x + y * 19) && *turn % 2 == BlackTurn)
			{
				if (*(horizon + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(vertical + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(cross + x + y * 19) == cmp)
				{
					count++;
				}
				if (*(incross + x + y * 19) == cmp)
				{
					count++;
				}
			}
		}
	}
	return count;
}



int RealBlankCheck(int* obj)
{
	if (*obj == Blank || *obj == FBlack || *obj == FWhite)
	{
		return 1;
	}
	else return 0;
}

int BlankCheck(int* obj)
{
	if (*obj == Blank)
	{
		return 1;
	}
	else return 0;
}

int RealBlockCheck(int* obj)
{
	if (*obj == Black || *obj == MBlack || *obj == White || *obj == MWhite)
	{
		return 1;
	}
	else return 0;
}

int BlockedBlackCheck(int* obj)
{
	if (*obj == Black || *obj == MBlack)
	{
		return 1;
	}
	else return 0;
}

int BlockedWhiteCheck(int* obj)
{
	if (*obj == White || *obj == MWhite)
	{
		return 1;
	}
	else return 0;
}