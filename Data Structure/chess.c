#include <stdio.h>
#include <Windows.h>

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
		scanf_s("%d %d", &x, &y);
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
		int data_black = 0, data_white = 0;
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
}

