#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void MENU();
int decode1();
int decode2();
int decode3();

typedef struct
{
	int HP, MP, MOVE, CRD, ATT, UMP, RANGE, ACT, X, Y, IDENTITY;
	char* ID;
}HYDRA, QUEEN, DEFILER, MARIN, TANK, VESSEL;

int main()
{
	int XY[41][21], Hea = 6, Qea = 2, Dea = 2, Mea = 6, Tea = 2, Vea = 2, ea = 20, order = 0;
	char* idarr[240][10];
	char* IDarr;
	char* ORDER[30][20];
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
		hydra[i].HP = 50, hydra[i].MP = 0, hydra[i].MOVE = 3, hydra[i].CRD = 5, hydra[i].ATT = 25, hydra[i].UMP = 0, hydra[i].RANGE = 1, hydra[i].ACT = 1, hydra[i].X = 0, hydra[i].Y = 0, hydra[i].IDENTITY = 0;
		queen[i].HP = 70, queen[i].MP = 150, queen[i].MOVE = 6, queen[i].CRD = 15, queen[i].ATT = 1000, queen[i].UMP = 45, queen[i].RANGE = 1, queen[i].ACT = 2, queen[i].X = 0, queen[i].Y = 0, queen[i].IDENTITY = 0;
		defiler[i].HP = 60, defiler[i].MP = 200, defiler[i].MOVE = 6, defiler[i].CRD = 10, defiler[i].ATT = -1, defiler[i].UMP = 60, defiler[i].RANGE = 5, defiler[i].ACT = 2, defiler[i].X = 0, defiler[i].Y = 0, defiler[i].IDENTITY = 0;
		marin[i].HP = 30, marin[i].MP = 0, marin[i].MOVE = 3, marin[i].CRD = 4, marin[i].ATT = 20, marin[i].UMP = 0, marin[i].RANGE = 1, marin[i].ACT = 1, marin[i].X = 0, marin[i].Y = 0, marin[i].IDENTITY = 1;
		tank[i].HP = 120, tank[i].MP = 0, tank[i].MOVE = 4, tank[i].CRD = 17, tank[i].ATT = 40, tank[i].UMP = 0, tank[i].RANGE = 1, tank[i].ACT = 2, tank[i].X = 0, tank[i].Y = 0, tank[i].IDENTITY = 1;
		vessel[i].HP = 80, vessel[i].MP = 140, vessel[i].MOVE = 5, vessel[i].CRD = 12, vessel[i].ATT = 50, vessel[i].UMP = 35, vessel[i].RANGE = 3, vessel[i].ACT = 2, vessel[i].X = 0, vessel[i].Y = 0, vessel[i].IDENTITY = 1;
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
		int menu, cmd1, cmd2, cmd3, msg, x1, y1, x2, y2, x3, y3, x4, y4, length, change, distance, ixy = 0;
		int xy[800];
		MENU();
		scanf_s("%d%*c", &menu);
		system("cls");
		if (menu == 1)
		{
			for (int i = 0; i <= order - 1; i++)
			{
				printf("%s\n", ORDER[i]);
			}
		}
		else if (menu == 2)
		{
			gets_s(ORDER[order], sizeof(ORDER[order]));
			order++;
		}
		else if (menu == 3)
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
		else if (menu == 4)
		{
			msg = decode2();
			x1 = msg / 1000000;
			msg = msg - (msg / 1000000) * 1000000;
			y1 = msg / 10000;
			msg = msg - (msg / 10000) * 10000;
			x2 = msg / 100;
			msg = msg - (msg / 100) * 100;
			y2 = msg;
			if (x1 >= x2 && y1 >= y2)
			{
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X <= x1 && hydra[i].X >= x2 && hydra[i].Y <= y1 && hydra[i].Y >= y2)
					{
						XY[hydra[i].X][hydra[i].Y] = ' ';
						hydra[i].X = 0, hydra[i].Y = 0;
						hydra[i].ID = "";
					}
					if (queen[i].X <= x1 && queen[i].X >= x2 && queen[i].Y <= y1 && queen[i].Y >= y2)
					{
						XY[queen[i].X][queen[i].Y] = ' ';
						queen[i].X = 0, queen[i].Y = 0;
						queen[i].ID = "";
					}
					if (defiler[i].X <= x1 && defiler[i].X >= x2 && defiler[i].Y <= y1 && defiler[i].Y >= y2)
					{
						XY[defiler[i].X][defiler[i].Y] = ' ';
						defiler[i].X = 0, defiler[i].Y = 0;
						defiler[i].ID = "";
					}
					if (marin[i].X <= x1 && marin[i].X >= x2 && marin[i].Y <= y1 && marin[i].Y >= y2)
					{
						XY[marin[i].X][marin[i].Y] = ' ';
						marin[i].X = 0, marin[i].Y = 0;
						marin[i].ID = "";
					}
					if (tank[i].X <= x1 && tank[i].X >= x2 && tank[i].Y <= y1 && tank[i].Y >= y2)
					{
						XY[tank[i].X][tank[i].Y] = ' ';
						tank[i].X = 0, tank[i].Y = 0;
						tank[i].ID = "";
					}
					if (vessel[i].X <= x1 && vessel[i].X >= x2 && vessel[i].Y <= y1 && vessel[i].Y >= y2)
					{
						XY[vessel[i].X][vessel[i].Y] = ' ';
						vessel[i].X = 0, vessel[i].Y = 0;
						vessel[i].ID = "";
					}
				}
			}
			else if (x1 < x2 && y1 >= y2)
			{
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X >= x1 && hydra[i].X <= x2 && hydra[i].Y <= y1 && hydra[i].Y >= y2)
					{
						XY[hydra[i].X][hydra[i].Y] = ' ';
						hydra[i].X = 0, hydra[i].Y = 0;
						hydra[i].ID = "";
					}
					if (queen[i].X >= x1 && queen[i].X <= x2 && queen[i].Y <= y1 && queen[i].Y >= y2)
					{
						XY[queen[i].X][queen[i].Y] = ' ';
						queen[i].X = 0, queen[i].Y = 0;
						queen[i].ID = "";
					}
					if (defiler[i].X >= x1 && defiler[i].X <= x2 && defiler[i].Y <= y1 && defiler[i].Y >= y2)
					{
						XY[defiler[i].X][defiler[i].Y] = ' ';
						defiler[i].X = 0, defiler[i].Y = 0;
						defiler[i].ID = "";
					}
					if (marin[i].X >= x1 && marin[i].X <= x2 && marin[i].Y <= y1 && marin[i].Y >= y2)
					{
						XY[marin[i].X][marin[i].Y] = ' ';
						marin[i].X = 0, marin[i].Y = 0;
						marin[i].ID = "";
					}
					if (tank[i].X >= x1 && tank[i].X <= x2 && tank[i].Y <= y1 && tank[i].Y >= y2)
					{
						XY[tank[i].X][tank[i].Y] = ' ';
						tank[i].X = 0, tank[i].Y = 0;
						tank[i].ID = "";
					}
					if (vessel[i].X >= x1 && vessel[i].X <= x2 && vessel[i].Y <= y1 && vessel[i].Y >= y2)
					{
						XY[vessel[i].X][vessel[i].Y] = ' ';
						vessel[i].X = 0, vessel[i].Y = 0;
						vessel[i].ID = "";
					}
				}
			}
			else if (x1 >= x2 && y1 < y2)
			{
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X <= x1 && hydra[i].X >= x2 && hydra[i].Y >= y1 && hydra[i].Y <= y2)
					{
						XY[hydra[i].X][hydra[i].Y] = ' ';
						hydra[i].X = 0, hydra[i].Y = 0;
						hydra[i].ID = "";
					}
					if (queen[i].X <= x1 && queen[i].X >= x2 && queen[i].Y >= y1 && queen[i].Y <= y2)
					{
						XY[queen[i].X][queen[i].Y] = ' ';
						queen[i].X = 0, queen[i].Y = 0;
						queen[i].ID = "";
					}
					if (defiler[i].X <= x1 && defiler[i].X >= x2 && defiler[i].Y >= y1 && defiler[i].Y <= y2)
					{
						XY[defiler[i].X][defiler[i].Y] = ' ';
						defiler[i].X = 0, defiler[i].Y = 0;
						defiler[i].ID = "";
					}
					if (marin[i].X <= x1 && marin[i].X >= x2 && marin[i].Y >= y1 && marin[i].Y <= y2)
					{
						XY[marin[i].X][marin[i].Y] = ' ';
						marin[i].X = 0, marin[i].Y = 0;
						marin[i].ID = "";
					}
					if (tank[i].X <= x1 && tank[i].X >= x2 && tank[i].Y >= y1 && tank[i].Y <= y2)
					{
						XY[tank[i].X][tank[i].Y] = ' ';
						tank[i].X = 0, tank[i].Y = 0;
						tank[i].ID = "";
					}
					if (vessel[i].X <= x1 && vessel[i].X >= x2 && vessel[i].Y >= y1 && vessel[i].Y <= y2)
					{
						XY[vessel[i].X][vessel[i].Y] = ' ';
						vessel[i].X = 0, vessel[i].Y = 0;
						vessel[i].ID = "";
					}
				}
			}
			else if (x1 < x2 && y1 < y2)
			{
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X >= x1 && hydra[i].X <= x2 && hydra[i].Y >= y1 && hydra[i].Y <= y2)
					{
						XY[hydra[i].X][hydra[i].Y] = ' ';
						hydra[i].X = 0, hydra[i].Y = 0;
						hydra[i].ID = "";
					}
					if (queen[i].X >= x1 && queen[i].X <= x2 && queen[i].Y >= y1 && queen[i].Y <= y2)
					{
						XY[queen[i].X][queen[i].Y] = ' ';
						queen[i].X = 0, queen[i].Y = 0;
						queen[i].ID = "";
					}
					if (defiler[i].X >= x1 && defiler[i].X <= x2 && defiler[i].Y >= y1 && defiler[i].Y <= y2)
					{
						XY[defiler[i].X][defiler[i].Y] = ' ';
						defiler[i].X = 0, defiler[i].Y = 0;
						defiler[i].ID = "";
					}
					if (marin[i].X >= x1 && marin[i].X <= x2 && marin[i].Y >= y1 && marin[i].Y <= y2)
					{
						XY[marin[i].X][marin[i].Y] = ' ';
						marin[i].X = 0, marin[i].Y = 0;
						marin[i].ID = "";
					}
					if (tank[i].X >= x1 && tank[i].X <= x2 && tank[i].Y >= y1 && tank[i].Y <= y2)
					{
						XY[tank[i].X][tank[i].Y] = ' ';
						tank[i].X = 0, tank[i].Y = 0;
						tank[i].ID = "";
					}
					if (vessel[i].X >= x1 && vessel[i].X <= x2 && vessel[i].Y >= y1 && vessel[i].Y <= y2)
					{
						XY[vessel[i].X][vessel[i].Y] = ' ';
						vessel[i].X = 0, vessel[i].Y = 0;
						vessel[i].ID = "";
					}
				}
			}
		}
		else if (menu == 5)
		{
			msg = decode2();
			x1 = msg / 1000000;
			msg = msg - (msg / 1000000) * 1000000;
			y1 = msg / 10000;
			msg = msg - (msg / 10000) * 10000;
			x2 = msg / 100;
			msg = msg - (msg / 100) * 100;
			y2 = msg;
			if (abs(x1 - x2) >= abs(y1 - y2))
			{
				printf("거리는 : %d\n", abs(x1 - x2));
			}
			else
			{
				printf("거리는 : %d\n", abs(y1 - y2));
			}
		}
		else if (menu == 6)
		{
			msg = decode3();
			x1 = msg / 10000;
			msg = msg - (msg / 10000) * 10000;
			y1 = msg / 100;
			msg = msg - (msg / 100) * 100;
			distance = msg;
			for (int i = 1; i <= 40; i++)
			{
				for (int j = 1; j <= 20; j++)
				{
					if (XY[i][j] != ' ')
					{
						if (abs(x1 - i) >= abs(y1 - j))
						{
							length = abs(x1 - i);
						}
						else
						{
							length = abs(y1 - j);
						}
						if (length <= distance)
						{
							xy[ixy] = length * 10000 + i * 100 + j;
							ixy++;
						}
					}
				}
			}
			for (int i = 0; i < ixy - 1; i++)
			{
				for (int j = 0; j < ixy - 1; j++)
				{
					int p, q;
					cmd1 = xy[j];
					cmd1 = cmd1 - (cmd1 / 10000) * 10000;
					x2 = cmd1 / 100;
					cmd1 = cmd1 - (cmd1 / 100) * 100;
					y2 = cmd1;
					cmd2 = xy[j + 1];
					cmd2 = cmd2 - (cmd2 / 10000) * 10000;
					x3 = cmd2 / 100;
					cmd2 = cmd2 - (cmd2 / 100) * 100;
					y3 = cmd2;
					for (int k = 0; k <= 99; k++)
					{
						if (hydra[k].X == x2 && hydra[k].Y == y2)
						{
							p = hydra[k].HP;
						}
						if (queen[k].X == x2 && queen[k].Y == y2)
						{
							p = queen[k].HP;
						}
						if (defiler[k].X == x2 && defiler[k].Y == y2)
						{
							p = defiler[k].HP;
						}
						if (marin[k].X == x2 && marin[k].Y == y2)
						{
							p = marin[k].HP;
						}
						if (tank[k].X == x2 && tank[k].Y == y2)
						{
							p = tank[k].HP;
						}
						if (vessel[k].X == x2 && vessel[k].Y == y2)
						{
							p = vessel[k].HP;
						}
					}
					for (int k = 0; k <= 99; k++)
					{
						if (hydra[k].X == x3 && hydra[k].Y == y3)
						{
							q = hydra[k].HP;
						}
						if (queen[k].X == x3 && queen[k].Y == y3)
						{
							q = queen[k].HP;
						}
						if (defiler[k].X == x3 && defiler[k].Y == y3)
						{
							q = defiler[k].HP;
						}
						if (marin[k].X == x3 && marin[k].Y == y3)
						{
							q = marin[k].HP;
						}
						if (tank[k].X == x3 && tank[k].Y == y3)
						{
							q = tank[k].HP;
						}
						if (vessel[k].X == x3 && vessel[k].Y == y3)
						{
							q = vessel[k].HP;
						}
					}
					if (p > q)
					{
						change = xy[j];
						xy[j] = xy[j + 1];
						xy[j + 1] = change;
					}
				}
			}
			for (int i = 0; i < ixy - 1; i++)
			{
				int p, q;
				cmd1 = xy[i];
				cmd1 = cmd1 - (cmd1 / 10000) * 10000;
				x2 = cmd1 / 100;
				cmd1 = cmd1 - (cmd1 / 100) * 100;
				y2 = cmd1;
				cmd2 = xy[i + 1];
				cmd2 = cmd2 - (cmd2 / 10000) * 10000;
				x3 = cmd2 / 100;
				cmd2 = cmd2 - (cmd2 / 100) * 100;
				y3 = cmd2;
				for (int k = 0; k <= 99; k++)
				{
					if (hydra[k].X == x2 && hydra[k].Y == y2)
					{
						p = hydra[k].HP;
					}
					if (queen[k].X == x2 && queen[k].Y == y2)
					{
						p = queen[k].HP;
					}
					if (defiler[k].X == x2 && defiler[k].Y == y2)
					{
						p = defiler[k].HP;
					}
					if (marin[k].X == x2 && marin[k].Y == y2)
					{
						p = marin[k].HP;
					}
					if (tank[k].X == x2 && tank[k].Y == y2)
					{
						p = tank[k].HP;
					}
					if (vessel[k].X == x2 && vessel[k].Y == y2)
					{
						p = vessel[k].HP;
					}
				}
				for (int k = 0; k <= 99; k++)
				{
					if (hydra[k].X == x3 && hydra[k].Y == y3)
					{
						q = hydra[k].HP;
					}
					if (queen[k].X == x3 && queen[k].Y == y3)
					{
						q = queen[k].HP;
					}
					if (defiler[k].X == x3 && defiler[k].Y == y3)
					{
						q = defiler[k].HP;
					}
					if (marin[k].X == x3 && marin[k].Y == y3)
					{
						q = marin[k].HP;
					}
					if (tank[k].X == x3 && tank[k].Y == y3)
					{
						q = tank[k].HP;
					}
					if (vessel[k].X == x3 && vessel[k].Y == y3)
					{
						q = vessel[k].HP;
					}
				}
				if (p != q)
				{
					ixy = i + 1;
				}
			}
			for (int i = 0; i <= ixy - 1; i++)
			{
				cmd3 = xy[i];
				distance = cmd3 / 10000;
				cmd3 = cmd3 - (cmd3 / 10000) * 10000;
				x4 = cmd3 / 100;
				cmd3 = cmd3 - (cmd3 / 100) * 100;
				y4 = cmd3;
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X == x4 && hydra[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
					}
					if (queen[i].X == x4 && queen[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
					}
					if (defiler[i].X == x4 && defiler[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
					}
					if (marin[i].X == x4 && marin[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
					}
					if (tank[i].X == x4 && tank[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
					}
					if (vessel[i].X == x4 && vessel[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
					}
				}
			}
		}
		else if (menu == 7)
		{
			char* p = NULL;
			char* q = NULL;
			msg = decode1();
			x1 = msg / 100;
			msg = msg - (msg / 100) * 100;
			y1 = msg;
			for (int i = 1; i <= 40; i++)
			{
				for (int j = 1; j <= 20; j++)
				{
					if (XY[i][j] != ' ')
					{
						if (abs(x1 - i) >= abs(y1 - j))
						{
							length = abs(x1 - i);
						}
						else
						{
							length = abs(y1 - j);
						}
						xy[ixy] = length * 10000 + i * 100 + j;
						ixy++;
					}
				}
			}
			for (int i = 0; i < ixy - 1; i++)
			{
				for (int j = 0; j < ixy - 1; j++)
				{
					if (xy[j] / 10000 > xy[j + 1] / 10000)
					{
						change = xy[j];
						xy[j] = xy[j + 1];
						xy[j + 1] = change;
					}
				}
			}
			for (int i = 0; i < ixy - 1; i++)
			{
				for (int j = 0; j < ixy - 1; j++)
				{
					if (xy[j] / 10000 == xy[j + 1] / 10000)
					{
						cmd1 = xy[j];
						cmd1 = cmd1 - (cmd1 / 10000) * 10000;
						x2 = cmd1 / 100;
						cmd1 = cmd1 - (cmd1 / 100) * 100;
						y2 = cmd1;
						cmd2 = xy[j + 1];
						cmd2 = cmd2 - (cmd2 / 10000) * 10000;
						x3 = cmd2 / 100;
						cmd2 = cmd2 - (cmd2 / 100) * 100;
						y3 = cmd2;
						for (int i = 0; i <= 99; i++)
						{
							if (hydra[i].X == x2 && hydra[i].Y == y2)
							{
								p = hydra[i].ID;
							}
							if (queen[i].X == x2 && queen[i].Y == y2)
							{
								p = queen[i].ID;
							}
							if (defiler[i].X == x2 && defiler[i].Y == y2)
							{
								p = defiler[i].ID;
							}
							if (marin[i].X == x2 && marin[i].Y == y2)
							{
								p = marin[i].ID;
							}
							if (tank[i].X == x2 && tank[i].Y == y2)
							{
								p = tank[i].ID;
							}
							if (vessel[i].X == x2 && vessel[i].Y == y2)
							{
								p = vessel[i].ID;
							}
						}
						for (int i = 0; i <= 99; i++)
						{
							if (hydra[i].X == x3 && hydra[i].Y == y3)
							{
								q = hydra[i].ID;
							}
							if (queen[i].X == x3 && queen[i].Y == y3)
							{
								q = queen[i].ID;
							}
							if (defiler[i].X == x3 && defiler[i].Y == y3)
							{
								q = defiler[i].ID;
							}
							if (marin[i].X == x3 && marin[i].Y == y3)
							{
								q = marin[i].ID;
							}
							if (tank[i].X == x3 && tank[i].Y == y3)
							{
								q = tank[i].ID;
							}
							if (vessel[i].X == x3 && vessel[i].Y == y3)
							{
								q = vessel[i].ID;
							}
						}
						if (strcmp(p, q) > 0)
						{
							change = xy[j];
							xy[j] = xy[j + 1];
							xy[j + 1] = change;
						}
					}
				}
			}
			for (int i = 0; i <= ixy - 1; i++)
			{
				cmd3 = xy[i];
				distance = cmd3 / 10000;
				cmd3 = cmd3 - (cmd3 / 10000) * 10000;
				x4 = cmd3 / 100;
				cmd3 = cmd3 - (cmd3 / 100) * 100;
				y4 = cmd3;
				for (int i = 0; i <= 99; i++)
				{
					if (hydra[i].X == x4 && hydra[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", hydra[i].HP, hydra[i].MP, hydra[i].X, hydra[i].Y, hydra[i].ID);
					}
					if (queen[i].X == x4 && queen[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", queen[i].HP, queen[i].MP, queen[i].X, queen[i].Y, queen[i].ID);
					}
					if (defiler[i].X == x4 && defiler[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", defiler[i].HP, defiler[i].MP, defiler[i].X, defiler[i].Y, defiler[i].ID);
					}
					if (marin[i].X == x4 && marin[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", marin[i].HP, marin[i].MP, marin[i].X, marin[i].Y, marin[i].ID);
					}
					if (tank[i].X == x4 && tank[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", tank[i].HP, tank[i].MP, tank[i].X, tank[i].Y, tank[i].ID);
					}
					if (vessel[i].X == x4 && vessel[i].Y == y4)
					{
						printf("Distance : %d\n", distance);
						printf("HP : %d, MP : %d, X : %d, Y : %d, ID : %s\n", vessel[i].HP, vessel[i].MP, vessel[i].X, vessel[i].Y, vessel[i].ID);
					}
				}
			}
		}
	}
}

void MENU()
{
	printf("1. ShowOrderList\n");
	printf("2. Order\n");
	printf("3. Display\n");
	printf("4. DestroyAll\n");
	printf("5. GetDistance\n");
	printf("6. FindWeakEnemy\n");
	printf("7. SortByDistance\n");
}

int decode1()
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

int decode2()
{
	int cmd, x11, x12, x21, x22, y11, y12, y21, y22;
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

int decode3()
{
	int cmd, x11, x12, y11, y12, distance11, distance12;
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
			if (*(msg + 9) >= '0' && *(msg + 9) <= '9')
			{
				distance11 = *(msg + 8) - 48;
				distance12 = *(msg + 9) - 48;
			}
			else
			{
				distance11 = 0;
				distance12 = *(msg + 8) - 48;
			}
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 5) - 48;
			if (*(msg + 8) >= '0' && *(msg + 8) <= '9')
			{
				distance11 = *(msg + 7) - 48;
				distance12 = *(msg + 8) - 48;
			}
			else
			{
				distance11 = 0;
				distance12 = *(msg + 7) - 48;
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
				distance11 = *(msg + 7) - 48;
				distance12 = *(msg + 8) - 48;
			}
			else
			{
				distance11 = 0;
				distance12 = *(msg + 7) - 48;
			}
		}
		else
		{
			y11 = 0;
			y12 = *(msg + 4) - 48;
			if (*(msg + 7) >= '0' && *(msg + 7) <= '9')
			{
				distance11 = *(msg + 6) - 48;
				distance12 = *(msg + 7) - 48;
			}
			else
			{
				distance11 = 0;
				distance12 = *(msg + 6) - 48;
			}
		}
	}
	cmd = x11 * 100000 + x12 * 10000 + y11 * 1000 + y12 * 100 + distance11 * 10 + distance12;
	free(msg);
	return cmd;
}