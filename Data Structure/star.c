#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

void MENU();
void error();
int Produce();
int Select();
int SelectAll();
int Destroy();
int FindTarget();

typedef struct
{
	int HP, MP, MOVE, CRD, ATT, UMP, RANGE, ACT, X, Y;
	char* ID;
}HYDRA, QUEEN, DEFILER, MARIN, TANK, VESSEL;

int main()
{
	int XY[41][21], Hea = 6, Qea = 2, Dea = 2, Mea = 6, Tea = 2, Vea = 2, ea = 20;
	char* idarr[240][10];
	char* IDarr;
	HYDRA hydra[100];
	QUEEN queen[100];
	DEFILER defiler[100];
	MARIN marin[100];
	TANK tank[100];
	VESSEL vessel[100];

	for (int i = 0; i <= 40; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			XY[i][j] = ' ';
		}
	}

	for (int i = 0; i <= 99; i++)
	{
		hydra[i].HP = 50, hydra[i].MP = 0, hydra[i].MOVE = 3, hydra[i].CRD = 5, hydra[i].ATT = 25, hydra[i].UMP = 0, hydra[i].RANGE = 1, hydra[i].ACT = 1, hydra[i].X = 0, hydra[i].Y = 0;
		queen[i].HP = 70, queen[i].MP = 150, queen[i].MOVE = 6, queen[i].CRD = 15, queen[i].ATT = 1000, queen[i].UMP = 45, queen[i].RANGE = 1, queen[i].ACT = 2, queen[i].X = 0, queen[i].Y = 0;
		defiler[i].HP = 60, defiler[i].MP = 200, defiler[i].MOVE = 6, defiler[i].CRD = 10, defiler[i].ATT = -1, defiler[i].UMP = 60, defiler[i].RANGE = 5, defiler[i].ACT = 2, defiler[i].X = 0, defiler[i].Y = 0;
		marin[i].HP = 30, marin[i].MP = 0, marin[i].MOVE = 3, marin[i].CRD = 4, marin[i].ATT = 20, marin[i].UMP = 0, marin[i].RANGE = 1, marin[i].ACT = 1, marin[i].X = 0, marin[i].Y = 0;
		tank[i].HP = 120, tank[i].MP = 0, tank[i].MOVE = 4, tank[i].CRD = 17, tank[i].ATT = 40, tank[i].UMP = 0, tank[i].RANGE = 1, tank[i].ACT = 2, tank[i].X = 0, tank[i].Y = 0;
		vessel[i].HP = 80, vessel[i].MP = 140, vessel[i].MOVE = 5, vessel[i].CRD = 12, vessel[i].ATT = 50, vessel[i].UMP = 35, vessel[i].RANGE = 3, vessel[i].ACT = 2, vessel[i].X = 0, vessel[i].Y = 0;
	}
	hydra[1].X = 40, hydra[1].Y = 15, hydra[1].ID = "H0001", idarr[0][0] = "H0001";
	hydra[2].X = 39, hydra[2].Y = 16, hydra[2].ID = "H0002", idarr[1][0] = "H0002";
	hydra[3].X = 39, hydra[3].Y = 17, hydra[3].ID = "H0003", idarr[2][0] = "H0003";
	hydra[4].X = 38, hydra[4].Y = 18, hydra[4].ID = "H0004", idarr[3][0] = "H0004";
	hydra[5].X = 40, hydra[5].Y = 19, hydra[5].ID = "H0005", idarr[4][0] = "H0005";
	hydra[6].X = 40, hydra[6].Y = 20, hydra[6].ID = "H0006", idarr[5][0] = "H0006";
	queen[1].X = 39, queen[1].Y = 18, queen[1].ID = "Q0001", idarr[6][0] = "Q0001";
	queen[2].X = 40, queen[2].Y = 18, queen[2].ID = "Q0002", idarr[7][0] = "Q0002";
	defiler[1].X = 40, defiler[1].Y = 16, defiler[1].ID = "D0001", idarr[8][0] = "D0001";
	defiler[2].X = 40, defiler[2].Y = 17, defiler[2].ID = "D0002", idarr[9][0] = "D0002";
	marin[1].X = 1, marin[1].Y = 1, marin[1].ID = "M0001", idarr[10][0] = "M0001";
	marin[2].X = 1, marin[2].Y = 2, marin[2].ID = "M0002", idarr[11][0] = "M0002";
	marin[3].X = 1, marin[3].Y = 3, marin[3].ID = "M0003", idarr[12][0] = "M0003";
	marin[4].X = 2, marin[4].Y = 4, marin[4].ID = "M0004", idarr[13][0] = "M0004";
	marin[5].X = 2, marin[5].Y = 5, marin[5].ID = "M0005", idarr[14][0] = "M0005";
	marin[6].X = 1, marin[6].Y = 6, marin[6].ID = "M0006", idarr[15][0] = "M0006";
	tank[1].X = 1, tank[1].Y = 4, tank[1].ID = "T0001", idarr[16][0] = "T0001";
	tank[2].X = 1, tank[2].Y = 5, tank[2].ID = "T0002", idarr[17][0] = "T0002";
	vessel[1].X = 2, vessel[1].Y = 3, vessel[1].ID = "V0001", idarr[18][0] = "V0001";
	vessel[2].X = 3, vessel[2].Y = 3, vessel[2].ID = "V0002", idarr[19][0] = "V0002";
	XY[40][15] = 'H', XY[39][16] = 'H', XY[39][17] = 'H', XY[38][18] = 'H', XY[40][19] = 'H', XY[40][20] = 'H';
	XY[1][1] = 'M', XY[1][2] = 'M', XY[1][3] = 'M', XY[2][4] = 'M', XY[2][5] = 'M', XY[1][6] = 'M';
	XY[39][18] = 'Q', XY[40][18] = 'Q', XY[40][16] = 'M', XY[40][17] = 'M';
	XY[1][4] = 'T', XY[1][5] = 'T', XY[2][3] = 'V', XY[3][3] = 'V';
	for (int j = 1; j <= 20; j++)
	{
		for (int i = 1; i <= 40; i++)
		{
			printf("%c", XY[i][j]);
		}
		printf("\n");
	}

	while (1)
	{
		int menu, msg, obj, x, y, x1, y1, finallength = 100, length;
		char* id[240][10];
		MENU();
		scanf_s("%d%*c", &menu);
		system("cls");
		if (menu == 1)
		{
			for (int j = 1; j <= 20; j++)
			{
				for (int i = 1; i <= 40; i++)
				{
					printf("%c", XY[i][j]);
				}
				printf("\n");
			}
		}
		else if (menu == 2)
		{
			msg = Produce();
			obj = msg / 10000;
			msg = msg - (msg / 10000) * 10000;
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				if (obj == 1)
				{
					Hea++;
					hydra[Hea].X = x, hydra[Hea].Y = y;
					XY[x][y] = 'H';
					printf("10자 안으로 유닛의 아이디를 입력하시오.\n");
					printf("예) H0007\n");
					scanf_s("%s%*c", id[ea], (unsigned char)sizeof(char) * 10);
					hydra[Hea].ID = &id[ea][0];
					idarr[ea][0] = &id[ea][0];
					ea++;
				}
				else if (obj == 2)
				{
					Qea++;
					queen[Qea].X = x, queen[Qea].Y = y;
					XY[x][y] = 'Q';
					printf("10자 안으로 유닛의 아이디를 입력하시오.\n");
					printf("예) H0007\n");
					scanf_s("%s%*c", id[ea], (unsigned char)sizeof(char) * 10);
					queen[Qea].ID = &id[ea][0];
					idarr[ea][0] = &id[ea][0];
					ea++;
				}
				else if (obj == 3)
				{
					Dea++;
					defiler[Dea].X = x, defiler[Dea].Y = y;
					XY[x][y] = 'D';
					printf("10자 안으로 유닛의 아이디를 입력하시오.\n");
					printf("예) H0007\n");
					scanf_s("%s%*c", id[ea], (unsigned char)sizeof(char) * 10);
					defiler[Dea].ID = &id[ea][0];
					idarr[ea][0] = &id[ea][0];
					ea++;
				}
				else if (obj == 4)
				{
					Mea++;
					marin[Mea].X = x, marin[Mea].Y = y;
					XY[x][y] = 'M';
					printf("10자 안으로 유닛의 아이디를 입력하시오.\n");
					printf("예) H0007\n");
					scanf_s("%s%*c", id[ea], (unsigned char)sizeof(char) * 10);
					marin[Mea].ID = &id[ea][0];
					idarr[ea][0] = &id[ea][0];
					ea++;
				}
				else if (obj == 5)
				{
					Tea++;
					tank[Tea].X = x, tank[Tea].Y = y;
					XY[x][y] = 'T';
					printf("10자 안으로 유닛의 아이디를 입력하시오.\n");
					printf("예) H0007\n");
					scanf_s("%s%*c", id[ea], (unsigned char)sizeof(char) * 10);
					tank[Tea].ID = &id[ea][0];
					idarr[ea][0] = &id[ea][0];
					ea++;
				}
				else if (obj == 6)
				{
					Vea++;
					vessel[Vea].X = x, vessel[Vea].Y = y;
					XY[x][y] = 'V';
					printf("10자 안으로 유닛의 아이디를 입력하시오.\n");
					printf("예) H0007\n");
					scanf_s("%s%*c", id[ea], (unsigned char)sizeof(char) * 10);
					vessel[Vea].ID = &id[ea][0];
					idarr[ea][0] = &id[ea][0];
					ea++;
				}
			}
			else
			{
				printf("좌표계의 범위를 벗어났습니다.\n");
				printf("다시 입력해주십시오\n");
			}
		}
		else if (menu == 3)
		{
			msg = Select();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X == x && hydra[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
					}
					else if (queen[i].X == x && queen[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
					}
					else if (defiler[i].X == x && defiler[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
					}
					else if (marin[i].X == x && marin[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
					}
					else if (tank[i].X == x && tank[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
					}
					else if (vessel[i].X == x && vessel[i].Y == y)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
					}
				}
			}
			else
			{
				printf("좌표계의 범위를 벗어났습니다.\n");
				printf("다시 입력해주십시오\n");
			}
		}
		else if (menu == 4)
		{
			msg = SelectAll();
			x = msg / 1000000;
			msg = msg - (msg / 1000000) * 1000000;
			y = msg / 10000;
			msg = msg - (msg / 10000) * 10000;
			x1 = msg / 100;
			msg = msg - (msg / 100) * 100;
			y1 = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20 && x1 >= 1 && x1 <= 40 && y1 >= 1 && y1 <= 20)
			{
				if (x >= x1 && y >= y1)
				{
					for (int i = 0; i <= 99; i++)
					{
						if (hydra[i].X <= x && hydra[i].X >= x1 && hydra[i].Y <= y && hydra[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
						}
						if (queen[i].X <= x && queen[i].X >= x1 && queen[i].Y <= y && queen[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
						}
						if (defiler[i].X <= x && defiler[i].X >= x1 && defiler[i].Y <= y && defiler[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
						}
						if (marin[i].X <= x && marin[i].X >= x1 && marin[i].Y <= y && marin[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
						}
						if (tank[i].X <= x && tank[i].X >= x1 && tank[i].Y <= y && tank[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
						}
						if (vessel[i].X <= x && vessel[i].X >= x1 && vessel[i].Y <= y && vessel[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
						}
					}
				}
				else if (x < x1 && y >= y1)
				{
					for (int i = 0; i <= 99; i++)
					{
						if (hydra[i].X >= x && hydra[i].X <= x1 && hydra[i].Y <= y && hydra[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
						}
						if (queen[i].X >= x && queen[i].X <= x1 && queen[i].Y <= y && queen[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
						}
						if (defiler[i].X >= x && defiler[i].X <= x1 && defiler[i].Y <= y && defiler[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
						}
						if (marin[i].X >= x && marin[i].X <= x1 && marin[i].Y <= y && marin[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
						}
						if (tank[i].X >= x && tank[i].X <= x1 && tank[i].Y <= y && tank[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
						}
						if (vessel[i].X >= x && vessel[i].X <= x1 && vessel[i].Y <= y && vessel[i].Y >= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
						}
					}
				}
				else if (x >= x1 && y < y1)
				{
					for (int i = 0; i <= 99; i++)
					{
						if (hydra[i].X <= x && hydra[i].X >= x1 && hydra[i].Y >= y && hydra[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
						}
						if (queen[i].X <= x && queen[i].X >= x1 && queen[i].Y >= y && queen[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
						}
						if (defiler[i].X <= x && defiler[i].X >= x1 && defiler[i].Y >= y && defiler[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
						}
						if (marin[i].X <= x && marin[i].X >= x1 && marin[i].Y >= y && marin[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
						}
						if (tank[i].X <= x && tank[i].X >= x1 && tank[i].Y >= y && tank[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
						}
						if (vessel[i].X <= x && vessel[i].X >= x1 && vessel[i].Y >= y && vessel[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
						}
					}
				}
				else if (x < x1 && y < y1)
				{
					for (int i = 0; i <= 99; i++)
					{
						if (hydra[i].X >= x && hydra[i].X <= x1 && hydra[i].Y >= y && hydra[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
						}
						if (queen[i].X >= x && queen[i].X <= x1 && queen[i].Y >= y && queen[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
						}
						if (defiler[i].X >= x && defiler[i].X <= x1 && defiler[i].Y >= y && defiler[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
						}
						if (marin[i].X >= x && marin[i].X <= x1 && marin[i].Y >= y && marin[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
						}
						if (tank[i].X >= x && tank[i].X <= x1 && tank[i].Y >= y && tank[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
						}
						if (vessel[i].X >= x && vessel[i].X <= x1 && vessel[i].Y >= y && vessel[i].Y <= y1)
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
						}
					}
				}
			}
			else
			{
				printf("좌표계의 범위를 벗어났습니다.\n");
				printf("다시 입력해주십시오\n");
			}
		}
		else if (menu == 5)
		{
			msg = Destroy();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X == x && hydra[i].Y == y)
					{
						hydra[i].X = 0, hydra[i].Y = 0;
						XY[x][y] = ' ';
						for (int j = 0; j < ea; j++)
						{
							if (hydra[i].ID == idarr[j][0])
							{
								idarr[j][0] = "";
							}
						}
						hydra[i].ID = "";
					}
					else if (queen[i].X == x && queen[i].Y == y)
					{
						queen[i].X = 0, queen[i].Y = 0;
						XY[x][y] = ' ';
						for (int j = 0; j < ea; j++)
						{
							if (queen[i].ID == idarr[j][0])
							{
								idarr[j][0] = "";
							}
						}
						queen[i].ID = "";
					}
					else if (defiler[i].X == x && defiler[i].Y == y)
					{
						defiler[i].X = 0, defiler[i].Y = 0;
						XY[x][y] = ' ';
						for (int j = 0; j < ea; j++)
						{
							if (defiler[i].ID == idarr[j][0])
							{
								idarr[j][0] = "";
							}
						}
						defiler[i].ID = "";
					}
					else if (marin[i].X == x && marin[i].Y == y)
					{
						marin[i].X = 0, marin[i].Y = 0;
						XY[x][y] = ' ';
						for (int j = 0; j < ea; j++)
						{
							if (marin[i].ID == idarr[j][0])
							{
								idarr[j][0] = "";
							}
						}
						marin[i].ID = "";
					}
					else if (tank[i].X == x && tank[i].Y == y)
					{
						tank[i].X = 0, tank[i].Y = 0;
						XY[x][y] = ' ';
						for (int j = 0; j < ea; j++)
						{
							if (tank[i].ID == idarr[j][0])
							{
								idarr[j][0] = "";
							}
						}
						tank[i].ID = "";
					}
					else if (vessel[i].X == x && vessel[i].Y == y)
					{
						vessel[i].X = 0, vessel[i].Y = 0;
						XY[x][y] = ' ';
						for (int j = 0; j < ea; j++)
						{
							if (vessel[i].ID == idarr[j][0])
							{
								idarr[j][0] = "";
							}
						}
						vessel[i].ID = "";
					}
				}
			}
			else
			{
				printf("좌표계의 범위를 벗어났습니다.\n");
				printf("다시 입력해주십시오\n");
			}
		}
		else if (menu == 6)
		{
			msg = FindTarget();
			x = msg / 100;
			msg = msg - (msg / 100) * 100;
			y = msg;
			if (x >= 1 && x <= 40 && y >= 1 && y <= 20)
			{
				for (int i = 1; i <= 40; i++)
				{
					for (int j = 1; j <= 20; j++)
					{
						if (XY[i][j] != ' ')
						{
							length = abs(x - i) + abs(y - j);
							if (finallength > length)
							{
								finallength = length;
								x1 = i, y1 = j;
							}
						}
					}
				}
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X == x1 && hydra[i].Y == y1)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
					}
					else if (queen[i].X == x1 && queen[i].Y == y1)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
					}
					else if (defiler[i].X == x1 && defiler[i].Y == y1)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
					}
					else if (marin[i].X == x1 && marin[i].Y == y1)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
					}
					else if (tank[i].X == x1 && tank[i].Y == y1)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
					}
					else if (vessel[i].X == x1 && vessel[i].Y == y1)
					{
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
					}
				}
			}
			else
			{
				printf("좌표계의 범위를 벗어났습니다.\n");
				printf("다시 입력해주십시오\n");
			}
		}
		else if (menu == 7)
		{
			for (int i = 0; i < ea - 1; i++)
			{
				for (int j = 0; j < ea - 1; j++)
				{
					if (strcmp(idarr[j][0], idarr[j + 1][0]) > 0)
					{
						IDarr = idarr[j][0];
						idarr[j][0] = idarr[j + 1][0];
						idarr[j + 1][0] = IDarr;
					}
				}
			}

			for (int k = 0; k <= ea - 1; k++)
			{
				if (idarr[k][0] != "")
				{
					for (int i = 0; i <= 99; i++)
					{
						if (hydra[i].ID == idarr[k][0])
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
						}
						else if (queen[i].ID == idarr[k][0])
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
						}
						else if (defiler[i].ID == idarr[k][0])
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
						}
						else if (marin[i].ID == idarr[k][0])
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
						}
						else if (tank[i].ID == idarr[k][0])
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
						}
						else if (vessel[i].ID == idarr[k][0])
						{
							printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
						}
					}
				}
			}
		}
		else
		{
			error();
		}
	}
	return 0;
}

void MENU()
{
	printf("1. Display\n");
	printf("2. Produce\n");
	printf("3. Select\n");
	printf("4. SelectAll\n");
	printf("5. Destroy\n");
	printf("6. FindTarget\n");
	printf("7. SortByID\n");
	printf("메뉴를 선택하시오. 예) 3(엔터)\n");
}

void error()
{
	printf("잘못된 입력입니다.\n");
	printf("다시 입력해주십시오.\n");
}

int Produce()
{
	int cmd, obj, x11, x12, y11, y12;
	printf("유닛 생성 명령어를 입력하시오\n");
	printf("예) 히드라 x : 14, y : 18 생성 : 명령어'p H 14 18'\n");
	char* msg = (char*)malloc(sizeof(char) * 20);
	gets_s(msg, (unsigned char)sizeof(char) * 20);
	if (*(msg + 2) == 'H')
	{
		obj = 1;
	}
	else if (*(msg + 2) == 'Q')
	{
		obj = 2;
	}
	else if (*(msg + 2) == 'D')
	{
		obj = 3;
	}
	else if (*(msg + 2) == 'M')
	{
		obj = 4;
	}
	else if (*(msg + 2) == 'T')
	{
		obj = 5;
	}
	else if (*(msg + 2) == 'V')
	{
		obj = 6;
	}

	if (*(msg + 5) >= '0' && *(msg + 5) <= '9')
	{
		x11 = *(msg + 4) - 48;
		x12 = *(msg + 5) - 48;
		if (*(msg + 8) >= '0' && *(msg + 8) <= '9')
		{
			y11 = *(msg + 7) - 48;
			y12 = *(msg + 8) - 48;
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 7) - 48;
		}
	}
	else
	{
		x11 = 0;
		x12 = *(msg + 4) - 48;
		if (*(msg + 7) >= '0' && *(msg + 7) <= '9')
		{
			y11 = *(msg + 6) - 48;
			y12 = *(msg + 7) - 48;
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 6) - 48;
		}
	}
	cmd = obj * 10000 + x11 * 1000 + x12 * 100 + y11 * 10 + y12;
	free(msg);
	return cmd;
}

int Select()
{
	int cmd, x11, x12, y11, y12;
	printf("확인하고 싶은 유닛의 좌료를 입력하시오.\n");
	printf("예) s 18 14\n");
	char* msg = (char*)malloc(sizeof(char) * 20);
	gets_s(msg, (unsigned char)sizeof(char) * 20);

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

int SelectAll()
{
	int cmd, x11, x12, x21, x22, y11, y12, y21, y22;
	printf("확인하고 싶은 유닛들의 범위를 입력하시오\n");
	printf("예) 1 1 부터 40 20안에 있는 유닛들 : 명령어 'S 1 1 40 20'\n");
	char* msg = (char*)malloc(sizeof(char) * 20);
	gets_s(msg, (unsigned char)sizeof(char) * 20);

	if (*(msg + 3) >= '0' && *(msg + 3) <= '9')
	{
		x11 = *(msg + 2) - 48;
		x12 = *(msg + 3) - 48;
		if (*(msg + 6) >= '0' && *(msg + 6) <= '9')
		{
			y11 = *(msg + 5) - 48;
			y12 = *(msg + 6) - 48;
			if (*(msg + 9) >= '0' && *(msg + 9) <= '9')
			{
				x21 = *(msg + 8) - 48;
				x22 = *(msg + 9) - 48;
				if (*(msg + 12) >= '0' && *(msg + 12) <= '9')
				{
					y21 = *(msg + 11) - 48;
					y22 = *(msg + 12) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 11) - 48;
				}
			}
			else
			{
				x21 = 0;
				x22 = *(msg + 8) - 48;
				if (*(msg + 11) >= '0' && *(msg + 11) <= '9')
				{
					y21 = *(msg + 10) - 48;
					y22 = *(msg + 11) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 10) - 48;
				}
			}
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 5) - 48;
			if (*(msg + 8) >= '0' && *(msg + 8) <= '9')
			{
				x21 = *(msg + 7) - 48;
				x22 = *(msg + 8) - 48;
				if (*(msg + 11) >= '0' && *(msg + 11) <= '9')
				{
					y21 = *(msg + 10) - 48;
					y22 = *(msg + 11) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 10) - 48;
				}
			}
			else
			{
				x21 = 0;
				x22 = *(msg + 7) - 48;
				if (*(msg + 10) >= '0' && *(msg + 10) <= '9')
				{
					y21 = *(msg + 9) - 48;
					y22 = *(msg + 10) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 9) - 48;
				}
			}
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
			if (*(msg + 8) >= '0' && *(msg + 8) <= '9')
			{
				x21 = *(msg + 7) - 48;
				x22 = *(msg + 8) - 48;
				if (*(msg + 11) >= '0' && *(msg + 11) <= '9')
				{
					y21 = *(msg + 10) - 48;
					y22 = *(msg + 11) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 10) - 48;
				}
			}
			else
			{
				x21 = 0;
				x22 = *(msg + 7) - 48;
				if (*(msg + 10) >= '0' && *(msg + 10) <= '9')
				{
					y21 = *(msg + 9) - 48;
					y22 = *(msg + 10) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 9) - 48;
				}
			}
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 4) - 48;
			if (*(msg + 7) >= '0' && *(msg + 7) <= '9')
			{
				x21 = *(msg + 6) - 48;
				x22 = *(msg + 7) - 48;
				if (*(msg + 10) >= '0' && *(msg + 10) <= '9')
				{
					y21 = *(msg + 9) - 48;
					y22 = *(msg + 10) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 9) - 48;
				}
			}
			else
			{
				x21 = 0;
				x22 = *(msg + 6) - 48;
				if (*(msg + 9) >= '0' && *(msg + 9) <= '9')
				{
					y21 = *(msg + 8) - 48;
					y22 = *(msg + 9) - 48;
				}
				else
				{
					y21 = 0;
					y22 = *(msg + 8) - 48;
				}
			}
		}
	}
	cmd = x11 * 10000000 + x12 * 1000000 + y11 * 100000 + y12 * 10000 + x21 * 1000 + x22 * 100 + y21 * 10 + y22;
	free(msg);
	return cmd;
}

int Destroy()
{
	int cmd, x11, x12, y11, y12;
	printf("삭제하고 싶은 유닛의 좌표를 입력하시오\n");
	printf("예) 명령어 'D 18 14'\n");
	char* msg = (char*)malloc(sizeof(char) * 20);
	gets_s(msg, (unsigned char)sizeof(char) * 20);

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

int FindTarget()
{
	int cmd, x11, x12, y11, y12;
	printf("좌표를 입력하시오\n");
	printf("예) 명령어 'F 18 14'\n");
	char* msg = (char*)malloc(sizeof(char) * 20);
	gets_s(msg, (unsigned char)sizeof(char) * 20);

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