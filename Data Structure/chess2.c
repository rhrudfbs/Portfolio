#include <stdio.h>
#include <Windows.h>

const int blank = 0;
const int black = 1;
const int white = 2;

void ResetBag();
void Display();
void Play();

int main()
{
	system("color 70");
	int bag[19][19], turn = 0;
	ResetBag(bag);
	while (1)
	{
		Display(bag);
		Play(bag, &turn);
	}
	return 0;
}

void ResetBag(int* bag)//�ٵ��� �ʱ�ȭ �Լ�
{
	for (int i = 0; i <= 360; i++)
	{
		*(bag + i) = blank;
	}
}

void Display(int* bag)//�ٵ��� ��� �Լ�
{
	int data_black = 0, data_white = 0;
	for (int j = 0; j <= 18; j++)
	{
		for (int i = 0; i <= 18; i++)
		{
			if ((*bag) == blank)
			{
				printf(" ��  ");
			}
			else if ((*bag) == black)
			{
				printf(" �� ");
				data_black++;
			}
			else if ((*bag) == white)
			{
				printf(" �� ");
				data_white++;
			}
			bag++;
		}
		printf("\n\n");
	}
	printf("�浹�� ���� : %d\n", data_black);
	printf("�鵹�� ���� : %d\n", data_white);
}

void Play(int* bag, int* turn)
{
	int x, y;
	scanf_s("%d %d%*c", &x, &y);
	bag = bag + 19 * y + x;
	if ((*bag) == blank)
	{
		if ((*turn) % 2 == 0)
		{
			(*bag) = black;
		}
		else if ((*turn) % 2 == 1)
		{
			(*bag) = white;
		}
		(*turn)++;
	}
	else printf("�̹� ���� ������ �ֽ��ϴ�\n");
}