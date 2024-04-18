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
			else printf("더 이상 무르기를 할 수 없습니다.\n");
		}
		else if (menu == 4)
		{
			if (stack2 != NULL)
			{
				stack1 = Stack(stack1, (*stack2).X, (*stack2).Y, (*stack2).COLOR);
				stack2 = ReGoBack(stack2, bag, &turn);
			}
			else printf("더 이상 무르기 취소를 할 수 없습니다.\n");
		}
	}
	return 0;
}

void MENU()
{
	printf("0. 게임을 진행하기 위해 돌을 놓습니다.\n");
	printf("1. 현재 상태를 파일로 저장합니다.\n");
	printf("2. 저장된 파일을 읽어 오목을 둡니다. (전에 불러오기 전 바둑판은 없어집니다.)\n");
	printf("3. 무르기\n");
	printf("4. 무르기 취소\n");
	printf("무르기 이후 돌을 놓으면 무르기 취소가 불가합니다\n");
	printf("무르기 이후 돌을 놓기 전까지만 무르기 취소가 가능합니다\n");
	printf("위 메뉴 중 진행할 사항을 고르세요\n");
}

void ResetBag(int* bag)//바둑판 초기화 함수
{
	for (int i = 0; i <= 360; i++)
	{
		*(bag + i) = blank;
	}
}

void Display(int* bag)//바둑판 출력 함수
{
	int data_black = 0, data_white = 0;
	for (int j = 0; j <= 18; j++)
	{
		for (int i = 0; i <= 18; i++)
		{
			if ((*bag) == blank)
			{
				printf(" ┼  ");
			}
			else if ((*bag) == black)
			{
				printf(" ● ");
				data_black++;
			}
			else if ((*bag) == white)
			{
				printf(" ○ ");
				data_white++;
			}
			bag++;
		}
		printf("\n\n");
	}
	printf("흑돌의 개수 : %d\n", data_black);
	printf("백돌의 개수 : %d\n", data_white);
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
	else printf("이미 돌이 놓여져 있습니다\n");
	return start;
}

void SaveData(int* bag, int turn)
{
	FILE* new = NULL;
	fopen_s(&new, "SaveData.c", "w");
	if (new == NULL)
	{
		printf("데이터 저장에 실패했습니다.\n");
	}
	else
	{
		for (int i = 0; i <= 360; i++)
		{
			fprintf_s(new, "%d\n", *(bag + i));
		}
		fprintf_s(new, "%d\n", turn);
		printf("파일 저장에 성공했습니다\n");
		fclose(new);
	}
}

void LoadData(int* bag, int* turn)
{
	FILE* old = NULL;
	fopen_s(&old, "SaveData.c", "r");
	if (old == NULL)
	{
		printf("데이터 불러오기에 실패했습니다.\n");
	}
	else
	{
		for (int i = 0; i <= 360; i++)
		{
			fscanf_s(old, "%d", (bag + i));
		}
		fscanf_s(old, "%d", turn);
		printf("파일 불러오기에 성공했습니다\n");
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
		printf("스택 저장에 실패했습니다.\n");
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
		printf("스택 저장에 성공했습니다\n");
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
		printf("스택 불러오기에 실패했습니다.\n");
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
		printf("스택 불러오기에 실패했습니다.\n");
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
		printf("파일 불러오기에 성공했습니다\n");
		fclose(old);
		return new;
	}
}