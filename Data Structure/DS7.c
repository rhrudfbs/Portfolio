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
				printf(" ��  ");
			}
			else if (bag[i][j] == black)
			{
				printf(" �� ");
			}
			else if (bag[i][j] == white)
			{
				printf(" �� ");
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
						printf(" ��  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" �� ");
					}
					else if (bag[i][j] == white)
					{
						printf(" �� ");
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
			printf("���� �� ���� : %d\n", data_black);
			printf("�� �� ���� : %d\n", data_white);
			printf("\n\n");
			printf("��ǥ�� �Է��Ͻÿ� ��) 14 18\n");
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
			else printf("�̹� ���� ���� �ֽ��ϴ�\n");
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ��  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" �� ");
					}
					else if (bag[i][j] == white)
					{
						printf(" �� ");
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
			printf("���� �� ���� : %d\n", data_black);
			printf("�� �� ���� : %d\n", data_white);
		}
		else if (menu == 1)
		{
			for (int j = 0; j <= 18; j++)
			{
				for (int i = 0; i <= 18; i++)
				{
					if (bag[i][j] == blank)
					{
						printf(" ��  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" �� ");
					}
					else if (bag[i][j] == white)
					{
						printf(" �� ");
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
			printf("���� �� ���� : %d\n", data_black);
			printf("�� �� ���� : %d\n", data_white);
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
					printf("X ��ǥ %d�� ���� ���� �浹 ������ %d��\n", X, data_black);
				}
				if (data_white != 0)
				{
					printf("X ��ǥ %d�� ���� ���� �鵹 ������ %d��\n", X, data_white);
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
					printf("Y ��ǥ %d�� ���� ���� �浹 ������ %d��\n", Y, data_black);
				}
				if (data_white != 0)
				{
					printf("Y ��ǥ %d�� ���� ���� �鵹 ������ %d��\n", Y, data_white);
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
						printf(" ��  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" �� ");
					}
					else if (bag[i][j] == white)
					{
						printf(" �� ");
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
			printf("���� �� ���� : %d\n", data_black);
			printf("�� �� ���� : %d\n", data_white);
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
						printf("X ��ǥ %d�� ���� �ٿ��� ���� ���� �������� ������ ���� �浹, ������ %d��\n", X, cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("X ��ǥ %d�� ���� �ٿ��� ���� ���� �������� ������ ���� �鵹, ������ %d��\n", X, cmp);
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
						printf("Y ��ǥ %d�� ���� �ٿ��� ���� ���� �������� ������ ���� �浹, ������ %d��\n", Y, cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("Y ��ǥ %d�� ���� �ٿ��� ���� ���� �������� ������ ���� �鵹, ������ %d��\n", Y, cmp);
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
						printf(" ��  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" �� ");
					}
					else if (bag[i][j] == white)
					{
						printf(" �� ");
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
			printf("���� �� ���� : %d\n", data_black);
			printf("�� �� ���� : %d\n", data_white);
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
						printf("���� ��ǥ X : 0, Y : %d ���� �� ��ǥ X : %d, Y : 18�� �밢��", Z, 18 - Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �浹, %d��\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("���� ��ǥ X : 0, Y : %d ���� �� ��ǥ X : %d, Y : 18�� �밢��", Z, 18 - Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �鵹, %d��\n", cmp);
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
						printf("���� ��ǥ X : %d, Y : 0 ���� �� ��ǥ X : 18, Y : %d�� �밢��", Z, 18 - Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �浹, %d��\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("���� ��ǥ X : %d, Y : 0 ���� �� ��ǥ X : 18, Y : %d�� �밢��", Z, 18 - Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �鵹, %d��\n", cmp);
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
						printf("���� ��ǥ X : 0, Y : %d ���� �� ��ǥ X : %d, Y : 0�� �밢��", Z, Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �浹, %d��\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("���� ��ǥ X : 0, Y : %d ���� �� ��ǥ X : %d, Y : 0�� �밢��", Z, Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �鵹, %d��\n", cmp);
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
						printf("���� ��ǥ X : %d, Y : 18 ���� �� ��ǥ X : 18, Y : %d�� �밢��", Z, Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �浹, %d��\n", cmp);
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("���� ��ǥ X : %d, Y : 18 ���� �� ��ǥ X : 18, Y : %d�� �밢��", Z, Z);
						printf(" �ٿ��� ���� ���� �������� ������ ���� �鵹, %d��\n", cmp);
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
						printf(" ��  ");
					}
					else if (bag[i][j] == black)
					{
						printf(" �� ");
					}
					else if (bag[i][j] == white)
					{
						printf(" �� ");
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
			printf("���� �� ���� : %d\n", data_black);
			printf("�� �� ���� : %d\n", data_white);
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
						printf("Y ��ǥ %d�� ���� �ٿ��� ���� ���� �������� ������ ���� �浹, ������ %d��\n", Y, cmp);
						for (int i = loc_x; i <= loc_x + cmp - 1; i++)
						{
							printf("X : %d, Y : %d\n", i, Y);
						}
					}
					else if (bag[loc_x][loc_y] == white)
					{
						printf("Y ��ǥ %d�� ���� �ٿ��� ���� ���� �������� ������ ���� �鵹, ������ %d��\n", Y, cmp);
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
			printf("�޴��� �߸� ���̽��ϴ�. �ٽ� �Է����ֽʽÿ�\n");
		}
	}
}

void MENU()
{
	printf("0. ��ǥ�� �Է��Ͽ� �����ǿ� ���� ���´�.\n");
	printf("1. �������� ��� ����, ���� �ٿ� ���Ͽ� ���� ������ �������� ������ ����Ѵ�.\n");
	printf("2. �������� ��� ����, ��ȣ �ٿ� ���Ͽ� �� �ٿ��� ���� ���� �������� ������ ���� ������ ������ ����Ѵ�.\n");
	printf("3. �������� ��� �밢�� �ٿ� ���Ͽ� �� �ٿ��� ���� ���� �������� ������ ���� ������ ������ ����Ѵ�.\n");
	printf("4. �޴� 2������ ��� �����ٿ� ���ؼ��� ���� ���� �������� ������ ������ ��ġ�� ��ǥ�� ����Ѵ�.\n");
	printf("�� �޴����� ���ϴ� �޴��� ���ڸ� �Է��Ͻÿ�\n");
}