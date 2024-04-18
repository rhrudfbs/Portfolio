#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct STACK {
	int X;
	int Y;
	int COLOR;
	struct STACK* NEXT;
}STACK;

const int blank = 0;
const int black = 1;
const int white = 2;

void MENU();
void ResetBag();
void Display();
struct STACK* Play();
void SaveData();
void LoadData();
struct STACK* Stack();
struct STACK* GoBack();
struct STACK* ReGoBack();
void SaveStack();
struct STACK* LoadStack();

int main()
{
	system("color 70");
	int bag[19][19], turn = 0;
	STACK* stack1 = NULL;
	STACK* stack2 = NULL;
	ResetBag(bag);
	Display(bag);
	while (1)
	{
		int menu;
		Display(bag);
		MENU();
		scanf_s("%d%*c", &menu);
		if (menu == 0)
		{
			stack2 = NULL;
			stack1 = Play(stack1, bag, &turn);
		}
		else if (menu == 1)
		{
			SaveData(bag, turn);
			SaveStack(stack1);
		}
		else if (menu == 2)
		{
			stack1 = NULL;
			stack2 = NULL;
			ResetBag(bag);
			LoadData(bag, &turn);
			stack1 = LoadStack(stack1);
		}
		else if (menu == 3)
		{
			if (stack1 != NULL)
			{
				stack2 = Stack(stack2, (*stack1).X, (*stack1).Y, (*stack1).COLOR);
				stack1 = GoBack(stack1, bag, &turn);
			}
			else printf("�� �̻� �����⸦ �� �� �����ϴ�.\n");
		}
		else if (menu == 4)
		{
			if (stack2 != NULL)
			{
				stack1 = Stack(stack1, (*stack2).X, (*stack2).Y, (*stack2).COLOR);
				stack2 = ReGoBack(stack2, bag, &turn);
			}
			else printf("�� �̻� ������ ��Ҹ� �� �� �����ϴ�.\n");
		}
	}
	return 0;
}

void MENU()
{
	printf("0. ������ �����ϱ� ���� ���� �����ϴ�.\n");
	printf("1. ���� ���¸� ���Ϸ� �����մϴ�.\n");
	printf("2. ����� ������ �о� ������ �Ӵϴ�. (���� �ҷ����� �� �ٵ����� �������ϴ�.)\n");
	printf("3. ������\n");
	printf("4. ������ ���\n");
	printf("������ ���� ���� ������ ������ ��Ұ� �Ұ��մϴ�\n");
	printf("������ ���� ���� ���� �������� ������ ��Ұ� �����մϴ�\n");
	printf("�� �޴� �� ������ ������ ������\n");
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

struct STACK* Play(STACK* start, int* bag, int* turn)
{
	int x, y;
	scanf_s("%d %d%*c", &x, &y);
	bag = bag + 19 * y + x;
	if ((*bag) == blank)
	{
		if ((*turn) % 2 == 0)
		{
			(*bag) = black;
			start = Stack(start, x, y, black);
		}
		else if ((*turn) % 2 == 1)
		{
			(*bag) = white;
			start = Stack(start, x, y, white);
		}
		(*turn)++;
	}
	else printf("�̹� ���� ������ �ֽ��ϴ�\n");
	return start;
}

void SaveData(int* bag, int turn)
{
	FILE* new = NULL;
	fopen_s(&new, "SaveData.c", "w");
	if (new == NULL)
	{
		printf("������ ���忡 �����߽��ϴ�.\n");
	}
	else
	{
		for (int i = 0; i <= 360; i++)
		{
			fprintf_s(new, "%d\n", *(bag + i));
		}
		fprintf_s(new, "%d\n", turn);
		printf("���� ���忡 �����߽��ϴ�\n");
		fclose(new);
	}
}

void LoadData(int* bag, int* turn)
{
	FILE* old = NULL;
	fopen_s(&old, "SaveData.c", "r");
	if (old == NULL)
	{
		printf("������ �ҷ����⿡ �����߽��ϴ�.\n");
	}
	else
	{
		for (int i = 0; i <= 360; i++)
		{
			fscanf_s(old, "%d", (bag + i));
		}
		fscanf_s(old, "%d", turn);
		printf("���� �ҷ����⿡ �����߽��ϴ�\n");
		fclose(old);
	}
}

struct STACK* Stack(STACK* start, int x, int y, int color)
{
	STACK* new = malloc(sizeof(STACK));
	(*new).X = x;
	(*new).Y = y;
	(*new).COLOR = color;
	if (start == NULL)
	{
		(*new).NEXT = NULL;
		start = new;
		return start;
	}
	else
	{
		(*new).NEXT = start;
		start = new;
		return start;
	}
}

struct STACK* GoBack(STACK* start, int* bag, int* turn)
{
	bag = bag + (*start).X + (*start).Y * 19;
	*bag = blank;
	(*turn)--;
	start = (*start).NEXT;
	return start;
}

struct STACK* ReGoBack(STACK* start, int* bag, int* turn)
{
	bag = bag + (*start).X + (*start).Y * 19;
	*bag = (*start).COLOR;
	(*turn)++;
	start = (*start).NEXT;
	return start;
}

void SaveStack(STACK* start)
{
	FILE* new = NULL;
	fopen_s(&new, "SaveStack.c", "w");
	if (new == NULL)
	{
		printf("���� ���忡 �����߽��ϴ�.\n");
	}
	else
	{
		while (start != NULL)
		{
			fprintf_s(new, "%d\n", (*start).X);
			fprintf_s(new, "%d\n", (*start).Y);
			fprintf_s(new, "%d\n", (*start).COLOR);
			start = (*start).NEXT;
		}
		printf("���� ���忡 �����߽��ϴ�\n");
		fclose(new);
	}
}

struct STACK* LoadStack(STACK* start)
{
	int tmp, count = 0;
	FILE* trash = NULL;
	fopen_s(&trash, "SaveStack.c", "r");
	if (trash == NULL)
	{
		printf("���� �ҷ����⿡ �����߽��ϴ�.\n");
	}
	else
	{
		while (fscanf_s(trash, "%d", &tmp) != EOF)
		{
			count++;
		}
		fclose(trash);
	}
	count = count / 3;
	FILE* old = NULL;
	fopen_s(&old, "SaveStack.c", "r");
	if (old == NULL)
	{
		printf("���� �ҷ����⿡ �����߽��ϴ�.\n");
	}
	else
	{
		STACK* new = (STACK*)malloc(sizeof(STACK*) * count);
		for (int i = 0; i < count; i++)
		{
			fscanf_s(old, "%d", &new[i].X);
			fscanf_s(old, "%d", &new[i].Y);
			fscanf_s(old, "%d", &new[i].COLOR);
		}
		for (int i = 0; i < count - 1; i++)
		{
			new[i].NEXT = new + i + 1;
		}
		new[count - 1].NEXT = NULL;
		start = new;
		printf("���� �ҷ����⿡ �����߽��ϴ�\n");
		fclose(old);
		return new;
	}
}