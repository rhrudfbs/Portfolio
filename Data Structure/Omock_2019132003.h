#pragma once


int GameBoard1[19][19];

void BlackAttack_2019132003(int* XX, int* YY);
void BlackDefend_2019132003(int XX, int YY);

int CheckHorizonRow4(int Board[][19]);
int CheckVerticalRow4(int Board[][19]);
int CheckCrossRow4(int Board[][19]);
int CheckIncrossRow4(int Board[][19]);

int ATTCheckHorizonRow4(int Board[][19]);
int ATTCheckVerticalRow4(int Board[][19]);
int ATTCheckCrossRow4(int Board[][19]);
int ATTCheckIncrossRow4(int Board[][19]);

#define BLANK 0
#define BLACK -1
#define WHITE 1

#define BLACK_TURN 0
#define WHITE_TURN 1

void BlackDefend_2019132003(int XX, int YY)
{
	GameBoard1[XX][YY] = WHITE;
}

void BlackAttack_2019132003(int* XX, int* YY)
{
	int fakeBoard[19][19];
	{
		for (int j = 0; j < 19; j++)
		{
			for (int i = 0; i < 19; i++)
			{
				fakeBoard[i][j] = GameBoard1[i][j];
			}
		}

		CheckHorizonRow4(fakeBoard), CheckVerticalRow4(fakeBoard), CheckCrossRow4(fakeBoard), CheckIncrossRow4(fakeBoard);
		ATTCheckHorizonRow4(fakeBoard), ATTCheckVerticalRow4(fakeBoard), ATTCheckCrossRow4(fakeBoard), ATTCheckIncrossRow4(fakeBoard);

		int q = 0, w = 0, tmp = 0;
		for (int j = 0; j < 19; j++)
		{
			for (int i = 0; i < 19; i++)
			{
				if (tmp < fakeBoard[i][j] && GameBoard1[i][j] == BLANK)
				{
					tmp = fakeBoard[i][j];
					q = i, w = j;
				}
			}
		}
		if (tmp == 0)
		{
			q = 9, w = 9;
		}
		GameBoard1[q][w] = BLACK;
		*XX = q, * YY = w;
	}
}

int CheckHorizonRow4(int Board[][19])
{
	for (int nY = 0; nY <= 18; nY++)
	{
		for (int nX = 0; nX <= 18; nX++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoo = nX;
				int endcoo = nX;
				int flag = 0;
				int index = 0;
				int block = 0;
				for (int cX = nX + 1, cY = nY; cX < 19; cX++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != WHITE && Board[cX][cY] != BLACK && flag == 0 && Board[cX + 1][cY] == WHITE && cX + 1 != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 600;
						Board[endcoo + 1][nY] += 600;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 60;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 60;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 600;
						Board[endcoo + 1][nY] += 600;
						Board[index][nY] += 600;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 60;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 60;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 1500;
						Board[endcoo + 1][nY] += 1500;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 1700;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 1700;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 1500;
						Board[endcoo + 1][nY] += 1500;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 400;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 400;
					}
					Board[index][nY] += 2000;
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 40;
						Board[endcoo + 1][nY] += 40;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 30;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 30;
					}
				}
				else if (endcoo - startcoo + 1 == 1)
				{
					if (Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 2;
					}
					if (Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 2;
					}
				}
			}
		}
	}
	return 0;
}

int CheckVerticalRow4(int Board[][19])
{
	for (int nX = 0; nX <= 18; nX++)
	{
		for (int nY = 0; nY <= 18; nY++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoo = nY;
				int endcoo = nY;
				int flag = 0;
				int index = 0;
				for (int cX = nX, cY = nY + 1; cY <= 18; cY++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX][cY + 1] == WHITE && cY != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 600;
						Board[nX][endcoo + 1] += 600;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 60;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 60;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 600;
						Board[nX][endcoo + 1] += 600;
						Board[nX][index] += 600;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 60;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 60;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 1500;
						Board[nX][endcoo + 1] += 1500;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 1700;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 1700;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 1500;
						Board[nX][endcoo + 1] += 1500;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 400;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 400;
					}
					Board[nX][index] += 2000;
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 40;
						Board[nX][endcoo + 1] += 40;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 30;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 30;
					}
				}
				else if (endcoo - startcoo + 1 == 1)
				{
					if (Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 2;
					}
					if (Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 2;
					}
				}
			}
		}
	}
	return 0;
}

int CheckCrossRow4(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int startcooy = nY;
				int endcoox = nX;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == WHITE && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
						Board[indexx][indexy] = 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] = 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 40;
						Board[endcoox + 1][endcooy + 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2;
					}
					if (Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 2;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 0; nX <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == WHITE && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
						Board[indexx][indexy] = 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] = 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 40;
						Board[endcoox + 1][endcooy + 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2;
					}
					if (Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 2;
					}
				}
			}
		}
	}
	return 0;
}

int CheckIncrossRow4(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY >= 0; nX++, nY--)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == WHITE && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
						Board[indexx][indexy] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] += 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 40;
						Board[endcoox + 1][endcooy - 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2;
					}
					if (Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 2;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 18; nX <= 18; nX++, nY--)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == WHITE && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
						Board[indexx][indexy] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] += 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 40;
						Board[endcoox + 1][endcooy - 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2;
					}
					if (Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 2;
					}
				}
			}
		}
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


int ATTCheckHorizonRow4(int Board[][19])
{
	for (int nY = 0; nY <= 18; nY++)
	{
		for (int nX = 0; nX <= 18; nX++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoo = nX;
				int endcoo = nX;
				int flag = 0;
				int index = 0;
				int block = 0;
				for (int cX = nX + 1, cY = nY; cX < 19; cX++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY] == BLACK && cX + 1 != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 2000;
						Board[endcoo + 1][nY] += 2000;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 25;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 25;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[index][nY] += 2000;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 25;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 25;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 2000;
						Board[endcoo + 1][nY] += 2000;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 2000;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 2000;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (Board[index][nY] != BLACK && Board[index][nY] != WHITE)
					{
						Board[index][nY] += 2000;
					}
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 35;
						Board[endcoo + 1][nY] += 35;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 25;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 25;
					}
				}
			}
		}
	}
	return 0;
}

int ATTCheckVerticalRow4(int Board[][19])
{
	for (int nX = 0; nX <= 18; nX++)
	{
		for (int nY = 0; nY <= 18; nY++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoo = nY;
				int endcoo = nY;
				int flag = 0;
				int index = 0;
				for (int cX = nX, cY = nY + 1; cY <= 18; cY++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX][cY + 1] == BLACK && cY + 1 != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 2000;
						Board[nX][endcoo + 1] += 2000;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 25;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 25;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][index] += 2000;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 25;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 25;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 2000;
						Board[nX][endcoo + 1] += 2000;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 2000;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 2000;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (Board[nX][index] != BLACK && Board[nX][index] != WHITE)
					{
						Board[nX][index] += 3000;
					}
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 35;
						Board[nX][endcoo + 1] += 35;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 25;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 25;
					}
				}
			}
		}
	}
	return 0;
}

int ATTCheckCrossRow4(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int startcooy = nY;
				int endcoox = nX;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == BLACK && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2000;
						Board[endcoox + 1][endcooy + 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[indexx][indexy] = 2000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (Board[indexx][indexy] != BLACK && Board[indexx][indexy] != WHITE)
					{
						Board[indexx][indexy] = 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 35;
						Board[endcoox + 1][endcooy + 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 0; nX <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == BLACK && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2000;
						Board[endcoox + 1][endcooy + 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[indexx][indexy] = 300;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (Board[indexx][indexy] != BLACK && Board[indexx][indexy] != WHITE)
					{
						Board[indexx][indexy] = 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 35;
						Board[endcoox + 1][endcooy + 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	return 0;
}

int ATTCheckIncrossRow4(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY >= 0; nX++, nY--)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == BLACK && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2000;
						Board[endcoox + 1][endcooy - 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[indexx][indexy] += 2000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (Board[indexx][indexy] != BLACK && Board[indexx][indexy] != WHITE)
					{
						Board[indexx][indexy] += 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 35;
						Board[endcoox + 1][endcooy - 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 18; nX <= 18; nX++, nY--)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == BLACK && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2000;
						Board[endcoox + 1][endcooy - 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[indexx][indexy] += 300;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (Board[indexx][indexy] != BLACK && Board[indexx][indexy] != WHITE)
					{
						Board[indexx][indexy] += 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 35;
						Board[endcoox + 1][endcooy - 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	return 0;
}



int GameBoard[19][19];

void WhiteAttack_2019132003(int* XX, int* YY);
void WhiteDefend_2019132003(int XX, int YY);

int CheckHorizonRow3(int Board[][19]);
int CheckVerticalRow3(int Board[][19]);
int CheckCrossRow3(int Board[][19]);
int CheckIncrossRow3(int Board[][19]);

int ATTCheckHorizonRow3(int Board[][19]);
int ATTCheckVerticalRow3(int Board[][19]);
int ATTCheckCrossRow3(int Board[][19]);
int ATTCheckIncrossRow3(int Board[][19]);

void WhiteDefend_2019132003(int XX, int YY)
{
	GameBoard[XX][YY] = BLACK;
}

void WhiteAttack_2019132003(int* XX, int* YY)
{
	int fakeBoard[19][19];
	{
		for (int j = 0; j < 19; j++)
		{
			for (int i = 0; i < 19; i++)
			{
				fakeBoard[i][j] = GameBoard[i][j];
			}
		}

		CheckHorizonRow3(fakeBoard), CheckVerticalRow3(fakeBoard), CheckCrossRow3(fakeBoard), CheckIncrossRow3(fakeBoard);
		ATTCheckHorizonRow3(fakeBoard), ATTCheckVerticalRow3(fakeBoard), ATTCheckCrossRow3(fakeBoard), ATTCheckIncrossRow3(fakeBoard);

		int q = 0, w = 0, tmp = 0;
		for (int j = 0; j < 19; j++)
		{
			for (int i = 0; i < 19; i++)
			{
				if (tmp < fakeBoard[i][j] && GameBoard[i][j] == BLANK)
				{
					tmp = fakeBoard[i][j];
					q = i, w = j;
				}
			}
		}
		GameBoard[q][w] = WHITE;
		*XX = q, * YY = w;
	}
}

int CheckHorizonRow3(int Board[][19])
{
	for (int nY = 0; nY <= 18; nY++)
	{
		for (int nX = 0; nX <= 18; nX++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoo = nX;
				int endcoo = nX;
				int flag = 0;
				int index = 0;
				int block = 0;
				for (int cX = nX + 1, cY = nY; cX < 19; cX++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY] == BLACK && cX + 1 != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 600;
						Board[endcoo + 1][nY] += 600;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 60;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 60;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 600;
						Board[endcoo + 1][nY] += 600;
						Board[index][nY] += 600;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 60;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 60;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 1500;
						Board[endcoo + 1][nY] += 1500;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 1700;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 1700;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 1500;
						Board[endcoo + 1][nY] += 1500;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 400;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 400;
					}
					Board[index][nY] += 2000;
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 40;
						Board[endcoo + 1][nY] += 40;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == WHITE))
					{
						Board[startcoo - 1][nY] += 30;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == WHITE) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 30;
					}
				}
				else if (endcoo - startcoo + 1 == 1)
				{
					if (Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 2;
					}
					if (Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 2;
					}
				}
			}
		}
	}
	return 0;
}

int CheckVerticalRow3(int Board[][19])
{
	for (int nX = 0; nX <= 18; nX++)
	{
		for (int nY = 0; nY <= 18; nY++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoo = nY;
				int endcoo = nY;
				int flag = 0;
				int index = 0;
				for (int cX = nX, cY = nY + 1; cY <= 18; cY++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX][cY + 1] == BLACK && cY != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 600;
						Board[nX][endcoo + 1] += 600;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 60;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 60;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 600;
						Board[nX][endcoo + 1] += 600;
						Board[nX][index] += 600;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 60;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 60;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 1500;
						Board[nX][endcoo + 1] += 1500;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 1700;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 1700;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 1500;
						Board[nX][endcoo + 1] += 1500;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 400;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 400;
					}
					Board[nX][index] += 2000;
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 40;
						Board[nX][endcoo + 1] += 40;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == WHITE))
					{
						Board[nX][startcoo - 1] += 30;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == WHITE) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 30;
					}
				}
				else if (endcoo - startcoo + 1 == 1)
				{
					if (Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 2;
					}
					if (Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 2;
					}
				}
			}
		}
	}
	return 0;
}

int CheckCrossRow3(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int startcooy = nY;
				int endcoox = nX;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == BLACK && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
						Board[indexx][indexy] = 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] = 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 40;
						Board[endcoox + 1][endcooy + 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2;
					}
					if (Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 2;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 0; nX <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == BLACK && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 600;
						Board[endcoox + 1][endcooy + 1] += 600;
						Board[indexx][indexy] = 600;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 1500;
						Board[endcoox + 1][endcooy + 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] = 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 40;
						Board[endcoox + 1][endcooy + 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == WHITE))
					{
						Board[startcoox - 1][startcooy - 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == WHITE) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2;
					}
					if (Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 2;
					}
				}
			}
		}
	}
	return 0;
}

int CheckIncrossRow3(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY >= 0; nX++, nY--)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == BLACK && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
						Board[indexx][indexy] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] += 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 40;
						Board[endcoox + 1][endcooy - 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2;
					}
					if (Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 2;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 18; nX <= 18; nX++, nY--)
		{
			if (Board[nX][nY] == BLACK)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == BLACK)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == BLACK && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 600;
						Board[endcoox + 1][endcooy - 1] += 600;
						Board[indexx][indexy] += 600;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 60;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 60;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 1700;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 1700;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 1500;
						Board[endcoox + 1][endcooy - 1] += 1500;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 400;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 400;
					}
					Board[indexx][indexy] += 2000;
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 40;
						Board[endcoox + 1][endcooy - 1] += 40;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == WHITE))
					{
						Board[startcoox - 1][startcooy + 1] += 30;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == WHITE) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 30;
					}
				}
				else if (endcoox - startcoox + 1 == 1)
				{
					if (Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2;
					}
					if (Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 2;
					}
				}
			}
		}
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


int ATTCheckHorizonRow3(int Board[][19])
{
	for (int nY = 0; nY <= 18; nY++)
	{
		for (int nX = 0; nX <= 18; nX++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoo = nX;
				int endcoo = nX;
				int flag = 0;
				int index = 0;
				int block = 0;
				for (int cX = nX + 1, cY = nY; cX < 19; cX++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY] == WHITE && cX + 1 != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 2000;
						Board[endcoo + 1][nY] += 2000;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 25;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 25;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[index][nY] += 2000;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 25;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 25;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 2000;
						Board[endcoo + 1][nY] += 2000;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 2000;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 2000;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (Board[index][nY] != BLACK && Board[index][nY] != WHITE)
					{
						Board[index][nY] += 2000;
					}
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[startcoo - 1][nY] += 35;
						Board[endcoo + 1][nY] += 35;
					}
					else if (startcoo != 0 && Board[startcoo - 1][nY] != BLACK && Board[startcoo - 1][nY] != WHITE && (endcoo == 18 || Board[endcoo + 1][nY] == BLACK))
					{
						Board[startcoo - 1][nY] += 25;
					}
					else if ((startcoo == 0 || Board[startcoo - 1][nY] == BLACK) && endcoo != 18 && Board[endcoo + 1][nY] != BLACK && Board[endcoo + 1][nY] != WHITE)
					{
						Board[endcoo + 1][nY] += 25;
					}
				}
			}
		}
	}
	return 0;
}

int ATTCheckVerticalRow3(int Board[][19])
{
	for (int nX = 0; nX <= 18; nX++)
	{
		for (int nY = 0; nY <= 18; nY++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoo = nY;
				int endcoo = nY;
				int flag = 0;
				int index = 0;
				for (int cX = nX, cY = nY + 1; cY <= 18; cY++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoo++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX][cY + 1] == WHITE && cY + 1 != 18)
					{
						endcoo++;
						index = endcoo;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoo - startcoo + 1 == 3 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 2000;
						Board[nX][endcoo + 1] += 2000;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 25;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 25;
					}
				}
				else if (endcoo - startcoo == 3 && flag == 1)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][index] += 2000;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 25;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 25;
					}
				}
				else if (endcoo - startcoo + 1 == 4 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 2000;
						Board[nX][endcoo + 1] += 2000;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 2000;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 2000;
					}
				}
				else if (endcoo - startcoo == 4 && flag == 1)
				{
					if (Board[nX][index] != BLACK && Board[nX][index] != WHITE)
					{
						Board[nX][index] += 3000;
					}
				}
				else if (endcoo - startcoo + 1 == 2 && flag == 0)
				{
					if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][startcoo - 1] += 35;
						Board[nX][endcoo + 1] += 35;
					}
					else if (startcoo != 0 && Board[nX][startcoo - 1] != BLACK && Board[nX][startcoo - 1] != WHITE && (endcoo == 18 || Board[nX][endcoo + 1] == BLACK))
					{
						Board[nX][startcoo - 1] += 25;
					}
					else if ((startcoo == 0 || Board[nX][startcoo - 1] == BLACK) && endcoo != 18 && Board[nX][endcoo + 1] != BLACK && Board[nX][endcoo + 1] != WHITE)
					{
						Board[nX][endcoo + 1] += 25;
					}
				}
			}
		}
	}
	return 0;
}

int ATTCheckCrossRow3(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int startcooy = nY;
				int endcoox = nX;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == WHITE && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2000;
						Board[endcoox + 1][endcooy + 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[indexx][indexy] = 2000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (Board[indexx][indexy] != BLACK && Board[indexx][indexy] != WHITE)
					{
						Board[indexx][indexy] = 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 35;
						Board[endcoox + 1][endcooy + 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 0; nX <= 18; nX++, nY++)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY + 1; cY <= 18; cX++, cY++)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy++;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY + 1] == WHITE && cX + 1 != 18 && cY + 1 != 18)
					{
						endcoox++;
						endcooy++;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 2000;
						Board[endcoox + 1][endcooy + 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[indexx][indexy] = 300;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (Board[indexx][indexy] != BLACK && Board[indexx][indexy] != WHITE)
					{
						Board[indexx][indexy] = 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[startcoox - 1][startcooy - 1] += 35;
						Board[endcoox + 1][endcooy + 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 0 && Board[startcoox - 1][startcooy - 1] != BLACK && Board[startcoox - 1][startcooy - 1] != WHITE && (endcoox == 18 || endcooy == 18 || Board[endcoox + 1][endcooy + 1] == BLACK))
					{
						Board[startcoox - 1][startcooy - 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 0 || Board[startcoox - 1][startcooy - 1] == BLACK) && endcoox != 18 && endcooy != 18 && Board[endcoox + 1][endcooy + 1] != BLACK && Board[endcoox + 1][endcooy + 1] != WHITE)
					{
						Board[endcoox + 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	return 0;
}

int ATTCheckIncrossRow3(int Board[][19])
{
	for (int Z = 0; Z <= 18; Z++)
	{
		for (int nX = 0, nY = Z; nY >= 0; nX++, nY--)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == WHITE && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2000;
						Board[endcoox + 1][endcooy - 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[indexx][indexy] += 2000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[indexx][indexy] += 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 35;
						Board[endcoox + 1][endcooy - 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	for (int Z = 1; Z <= 18; Z++)
	{
		for (int nX = Z, nY = 18; nX <= 18; nX++, nY--)
		{
			if (Board[nX][nY] == WHITE)
			{
				int startcoox = nX;
				int endcoox = nX;
				int startcooy = nY;
				int endcooy = nY;
				int flag = 0;
				int indexx = 0;
				int indexy = 0;
				for (int cX = nX + 1, cY = nY - 1; cY >= 0; cX++, cY--)
				{
					if (Board[cX][cY] == WHITE)
					{
						endcoox++;
						endcooy--;
					}
					else if (Board[cX][cY] != BLACK && Board[cX][cY] != WHITE && flag == 0 && Board[cX + 1][cY - 1] == WHITE && cX + 1 != 18 && cY - 1 != 0)
					{
						endcoox += 1;
						endcooy -= 1;
						indexx = endcoox;
						indexy = endcooy;
						flag = 1;
					}
					else
					{
						break;
					}
				}
				if (endcoox - startcoox + 1 == 3 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 2000;
						Board[endcoox + 1][endcooy - 1] += 2000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox == 3 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[indexx][indexy] += 300;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 25;
					}
				}
				else if (endcoox - startcoox + 1 == 4 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 3000;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox + 1][endcooy - 1] += 3000;
					}
				}
				else if (endcoox - startcoox == 4 && flag == 1)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[indexx][indexy] += 3000;
					}
				}
				else if (endcoox - startcoox + 1 == 2 && flag == 0)
				{
					if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[startcoox - 1][startcooy + 1] += 35;
						Board[endcoox + 1][endcooy - 1] += 35;
					}
					else if (startcoox != 0 && startcooy != 18 && Board[startcoox - 1][startcooy + 1] != BLACK && Board[startcoox - 1][startcooy + 1] != WHITE && (endcoox == 18 || endcooy == 0 || Board[endcoox + 1][endcooy - 1] == BLACK))
					{
						Board[startcoox - 1][startcooy + 1] += 25;
					}
					else if ((startcoox == 0 || startcooy == 18 || Board[startcoox - 1][startcooy + 1] == BLACK) && endcoox != 18 && endcooy != 0 && Board[endcoox + 1][endcooy - 1] != BLACK && Board[endcoox + 1][endcooy - 1] != WHITE)
					{
						Board[endcoox - 1][endcooy + 1] += 25;
					}
				}
			}
		}
	}
	return 0;
}