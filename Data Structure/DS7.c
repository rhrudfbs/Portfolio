#include <stdio.h>
#include <Windows.h>

void MENU();

int main()
{
	system("color 70");
	const int blank = 0;
	const int black = 1;
	const int white = 2;
	int bag[19][19], turn = 0;
	for (int j = 0; j <= 18; j++)
	{
		for (int i = 0; i <= 18; i++)
		{
			bag[i][j] = blank;
		}
	}
	for (int j = 0; j <= 18; j++)
	{
		for (int i = 0; i <= 18; i++)
		{
			if (bag[i][j] == blank)
			{
				printf(" ┼  ");
			}
			else if (bag[i][j] == black)
			{
				printf(" ● ");
			}
			else if (bag[i][j] == white)
			{
				printf(" ○ ");
			}
		}
		printf("\n\n");
	}
	while (1)
	{
		int x, y;
		int data[19][19], loc_x, loc_y, cmp, menu, data_black, data_white;
		MENU();
		scanf_s("%d%*c", &menu);
		system("cls");
		if (menu == 0)
		{
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ┼  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" ● ");
					}
					else if (bag[i][j] == white)
					{
						printf(" ○ ");
					}
				}
				printf("\n\n");
			}
			data_black = 0, data_white = 0;
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == black)
					{
						data_black++;
					}
					else if (bag[i][j] == white)
					{
						data_white++;
					}
				}
			}
			printf("검은 돌 개수 : %d\n", data_black);
			printf("흰 돌 개수 : %d\n", data_white);
			printf("\n\n");
			printf("좌표를 입력하시오 예) 14 18\n");
			scanf_s("%d %d%*c", &x, &y);
			system("cls");
			if (bag[x][y] == blank)
			{
				turn++;
				if (turn % 2 == 1)
				{
					bag[x][y] = black;
				}
				else if (turn % 2 == 0)
				{
					bag[x][y] = white;
				}
			}
			else printf("이미 돌이 놓여 있습니다\n");
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ┼  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" ● ");
					}
					else if (bag[i][j] == white)
					{
						printf(" ○ ");
					}
				}
				printf("\n\n");
			}
			data_black = 0, data_white = 0;
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == black)
					{
						data_black++;
					}
					else if (bag[i][j] == white)
					{
						data_white++;
					}
				}
			}
			printf("검은 돌 개수 : %d\n", data_black);
			printf("흰 돌 개수 : %d\n", data_white);
		}
		else if (menu == 1)
		{
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ┼  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" ● ");
					}
					else if (bag[i][j] == white)
					{
						printf(" ○ ");
					}
				}
				printf("\n\n");
			}
			data_black = 0, data_white = 0;
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == black)
					{
						data_black++;
					}
					else if (bag[i][j] == white)
					{
						data_white++;
					}
				}
			}
			printf("검은 돌 개수 : %d\n", data_black);
			printf("흰 돌 개수 : %d\n", data_white);
			for (int X = 0; X <= 18; X++)
			{
				data_black = 0, data_white = 0;
				for (int Y = 0; Y <= 18; Y++)
				{
					if (bag[X][Y] == black)
					{
						data_black++;
					}
					else if (bag[X][Y] == white)
					{
						data_white++;
					}
				}
				if (data_black != 0)
				{
					printf("X 좌표 %d인 세로 줄의 흑돌 개수는 %d개\n", X, data_black);
				}
				if (data_white != 0)
				{
					printf("X 좌표 %d인 세로 줄의 백돌 개수는 %d개\n", X, data_white);
				}
			}
			for (int Y = 0; Y <= 18; Y++)
			{
				data_black = 0, data_white = 0;
				for (int X = 0; X <= 18; X++)
				{
					if (bag[X][Y] == black)
					{
						data_black++;
					}
					else if (bag[X][Y] == white)
					{
						data_white++;
					}
				}
				if (data_black != 0)
				{
					printf("Y 좌표 %d인 가로 줄의 흑돌 개수는 %d개\n", Y, data_black);
				}
				if (data_white != 0)
				{
					printf("Y 좌표 %d인 가로 줄의 백돌 개수는 %d개\n", Y, data_white);
				}
			}
			printf("\n\n");
		}
		else if (menu == 2)
		{
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ┼  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" ● ");
					}
					else if (bag[i][j] == white)
					{
						printf(" ○ ");
					}
				}
				printf("\n\n");
			}
			data_black = 0, data_white = 0;
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == black)
					{
						data_black++;
					}
					else if (bag[i][j] == white)
					{
						data_white++;
					}
				}
			}
			printf("검은 돌 개수 : %d\n", data_black);
			printf("흰 돌 개수 : %d\n", data_white);
			for (int X = 0; X <= 18; X++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int Y = 0; Y <= 18; Y++)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; Y1 < 18; Y1++)
						{
							if (bag[X1][Y1] == bag[X1][Y1 + 1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("X 좌표 %d인 세로 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, 개수는 %d개\n", X, cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("X 좌표 %d인 세로 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, 개수는 %d개\n", X, cmp);
					}
				}
			}
			for (int Y = 0; Y <= 18; Y++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int X = 0; X <= 18; X++)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; X1 < 18; X1++)
						{
							if (bag[X1][Y1] == bag[X1 + 1][Y1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("Y 좌표 %d인 가로 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, 개수는 %d개\n", Y, cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("Y 좌표 %d인 가로 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, 개수는 %d개\n", Y, cmp);
					}
				}
			}
			printf("\n\n");
		}
		else if (menu == 3)
		{
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ┼  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" ● ");
					}
					else if (bag[i][j] == white)
					{
						printf(" ○ ");
					}
				}
				printf("\n\n");
			}
			data_black = 0, data_white = 0;
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == black)
					{
						data_black++;
					}
					else if (bag[i][j] == white)
					{
						data_white++;
					}
				}
			}
			printf("검은 돌 개수 : %d\n", data_black);
			printf("흰 돌 개수 : %d\n", data_white);
			for (int Z = 0; Z <= 18; Z++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int X = 0, Y = Z; X <= 18 - Z && Y <= 18; X++, Y++)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; X1 < 18 - Z && Y1 < 18; X1++, Y1++)
						{
							if (bag[X1][Y1] == bag[X1 + 1][Y1 + 1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("시작 좌표 X : 0, Y : %d 부터 끝 좌표 X : %d, Y : 18인 대각선", Z, 18 - Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, %d개\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("시작 좌표 X : 0, Y : %d 부터 끝 좌표 X : %d, Y : 18인 대각선", Z, 18 - Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, %d개\n", cmp);
					}
				}
			}
			for (int Z = 1; Z <= 18; Z++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int X = Z, Y = 0; X <= 18 && Y <= 18 - Z; X++, Y++)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; X1 < 18 && Y1 < 18 - Z; X1++, Y1++)
						{
							if (bag[X1][Y1] == bag[X1 + 1][Y1 + 1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("시작 좌표 X : %d, Y : 0 부터 끝 좌표 X : 18, Y : %d인 대각선", Z, 18 - Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, %d개\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("시작 좌표 X : %d, Y : 0 부터 끝 좌표 X : 18, Y : %d인 대각선", Z, 18 - Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, %d개\n", cmp);
					}
				}
			}
			for (int Z = 0; Z <= 18; Z++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int X = 0, Y = Z; X <= Z && Y >= 0; X++, Y--)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; X1 <= Z && Y1 >= 0; X1++, Y1--)
						{
							if (bag[X1][Y1] == bag[X1 + 1][Y1 - 1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("시작 좌표 X : 0, Y : %d 부터 끝 좌표 X : %d, Y : 0인 대각선", Z, Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, %d개\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("시작 좌표 X : 0, Y : %d 부터 끝 좌표 X : %d, Y : 0인 대각선", Z, Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, %d개\n", cmp);
					}
				}
			}
			for (int Z = 1; Z <= 18; Z++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int X = Z, Y = 18; X <= 18 && Y >= Z; X++, Y--)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; X1 <= 18 && Y1 >= Z; X1++, Y1--)
						{
							if (bag[X1][Y1] == bag[X1 + 1][Y1 - 1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("시작 좌표 X : %d, Y : 18 부터 끝 좌표 X : 18, Y : %d인 대각선", Z, Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, %d개\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("시작 좌표 X : %d, Y : 18 부터 끝 좌표 X : 18, Y : %d인 대각선", Z, Z);
						printf(" 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, %d개\n", cmp);
					}
				}
			}
			printf("\n\n");
		}
		else if (menu == 4)
		{
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ┼  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" ● ");
					}
					else if (bag[i][j] == white)
					{
						printf(" ○ ");
					}
				}
				printf("\n\n");
			}
			data_black = 0, data_white = 0;
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == black)
					{
						data_black++;
					}
					else if (bag[i][j] == white)
					{
						data_white++;
					}
				}
			}
			printf("검은 돌 개수 : %d\n", data_black);
			printf("흰 돌 개수 : %d\n", data_white);
			for (int Y = 0; Y <= 18; Y++)
			{
				loc_x = 0, loc_y = 0, cmp = 0;
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						data[i][j] = 0;
					}
				}
				for (int X = 0; X <= 18; X++)
				{
					if (bag[X][Y] == black || bag[X][Y] == white)
					{
						data[X][Y]++;
						for (int X1 = X, Y1 = Y; X1 < 18; X1++)
						{
							if (bag[X1][Y1] == bag[X1 + 1][Y1])
							{
								data[X][Y]++;
							}
							else break;
						}
					}
				}
				for (int i = 0; i <= 18; i++)
				{
					for (int j = 0; j <= 18; j++)
					{
						if (data[i][j] > cmp)
						{
							cmp = data[i][j];
							loc_x = i, loc_y = j;
						}
					}
				}
				if (cmp != 0)
				{
					if (bag[loc_x][loc_y] == black)
					{
						printf("Y 좌표 %d인 가로 줄에서 가장 많이 연속으로 놓여진 돌은 흑돌, 개수는 %d개\n", Y, cmp);
						for (int i = loc_x; i <= loc_x + cmp - 1; i++)
						{
							printf("X : %d, Y : %d\n", i, Y);
						}
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("Y 좌표 %d인 가로 줄에서 가장 많이 연속으로 놓여진 돌은 백돌, 개수는 %d개\n", Y, cmp);
						for (int i = loc_x; i <= loc_x + cmp - 1; i++)
						{
							printf("X : %d, Y : %d\n", i, Y);
						}
					}
				}
			}
			printf("\n\n");
		}
		else
		{
			printf("메뉴를 잘못 고르셨습니다. 다시 입력해주십시오\n");
		}
	}
}

void MENU()
{
	printf("0. 좌표를 입력하여 오목판에 돌을 놓는다.\n");
	printf("1. 오목판의 모든 가로, 세로 줄에 대하여 흰돌의 개수와 검은돌의 개수를 출력한다.\n");
	printf("2. 오목판의 모든 가로, 세호 줄에 대하여 그 줄에서 가장 많이 연속으로 놓여진 돌의 종류와 개수를 출력한다.\n");
	printf("3. 오목판의 모든 대각선 줄에 대하여 그 줄에서 가장 많이 연속으로 놓여진 돌의 종류와 개수를 출력한다.\n");
	printf("4. 메뉴 2번에서 모든 가로줄에 대해서는 가장 많이 연속으로 놓여진 돌들의 위치를 좌표로 출력한다.\n");
	printf("위 메뉴에서 원하는 메뉴의 숫자를 입력하시오\n");
}