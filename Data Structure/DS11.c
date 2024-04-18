#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct UNIT {
	char POSITION[20];
	char NAME[20];
	int HP;
	int ATT;
	int DEF;
	struct UNIT* NEXT;
}UNIT;


void MENU();
struct UNIT* Make_SL();
void PrintAll_SL();
void FindTarget_SL();
void QuickSort();
int Partition();
struct UNIT* SortByName_SL();


int main()
{
	UNIT* start = NULL;
	while (1)
	{
		MENU();
		int menu;
		scanf_s("%d%*c", &menu);
		if (menu == 1)
		{
			start = Make_SL(start);
		}
		else if (menu == 2)
		{
			PrintAll_SL(start);
		}
		else if (menu == 3)
		{
			start = SortByName_SL(start);
		}
		else if (menu == 4)
		{
			FindTarget_SL(start);
		}
	}
	return 0;
}

void MENU()
{
	printf("1. Make_SL\n");
	printf("2. PrintAll_SL\n");
	printf("3. SortByName_SL\n");
	printf("4. FindTarget_SL\n");
}

struct UNIT* Make_SL(UNIT* start)
{
	time_t time_start, time_end;
	double result;
	time_start = time(NULL);

	if (start == NULL)
	{
		UNIT* end = NULL;
		FILE* fp = NULL;
		fopen_s(&fp, "DS_Large.txt", "r");
		if (fp == NULL)
		{
			printf("failed\n");
		}
		else
		{
			while (!feof(fp))
			{
				UNIT* new = (UNIT*)malloc(sizeof(UNIT));
				fscanf_s(fp, "%s %s %d %d %d", &new->POSITION, sizeof(new->POSITION), &new->NAME, sizeof(new->NAME), &new->HP, &new->ATT, &new->DEF);
				if (start == NULL)
				{
					start = new;
					end = new;
				}
				else
				{
					end->NEXT = new;
					end = new;
				}
				new->NEXT = NULL;
			}
			fclose(fp);
		}
	}


	time_end = time(NULL);
	result = (double)(time_end - time_start);
	printf("수행시간 : %f초\n", result);
	return start;
}

void PrintAll_SL(UNIT* start)
{
	time_t time_start, time_end;
	double result;
	time_start = time(NULL);

	while (start->NEXT != NULL)
	{
		printf("%s %s %d %d %d\n", start->POSITION, start->NAME, start->HP, start->ATT, start->DEF);
		for (int i = 0; i < 1000; i++)
		{
			if (start->NEXT == NULL)
			{
				break;
			}
			else start = start->NEXT;
		}
		if (start->NEXT == NULL)
		{
			break;
		}
	}

	time_end = time(NULL);
	result = (double)(time_end - time_start);
	printf("수행시간 : %f초\n", result);
}

void FindTarget_SL(UNIT* start)
{
	char name[20];
	scanf_s("%s", name, sizeof(name));

	time_t time_start, time_end;
	double result;
	time_start = time(NULL);

	while (start->NEXT != NULL)
	{
		if (strcmp(name, start->NAME) == 0)
		{
			printf("%s %s %d %d %d\n", start->POSITION, start->NAME, start->HP, start->ATT, start->DEF);
			break;
		}
		else start = start->NEXT;
	}
	if (start->NEXT == NULL)
	{
		if (strcmp(name, start->NAME) == 0)
		{
			printf("%s %s %d %d %d\n", start->POSITION, start->NAME, start->HP, start->ATT, start->DEF);
		}
	}

	time_end = time(NULL);
	result = (double)(time_end - time_start);
	printf("수행시간 : %f초\n", result);
}

void QuickSort(UNIT** start, int left, int right)
{
	if (left < right)
	{
		int p = Partition(start, left, right);

		QuickSort(start, left, p - 1);
		QuickSort(start, p + 1, right);
	}
}

int Partition(UNIT** start, int left, int right)
{
	char* pivot = start[right]->NAME;
	int i = left - 1;
	for (int j = left; j < right; j++)
	{
		if (strcmp(pivot, start[j]->NAME) == 1)
		{
			i++;
			UNIT* temp = start[i];
			start[i] = start[j];
			start[j] = temp;
		}
	}
	UNIT* temp = start[i + 1];
	start[i + 1] = start[right];
	start[right] = temp;
	return i + 1;
}

struct UNIT* SortByName_SL(UNIT* start)
{
	time_t time_start, time_end;
	double result;
	time_start = time(NULL);


	int count = 0;
	UNIT* remember = start;
	while (remember->NEXT != NULL)
	{
		remember = remember->NEXT;
		count++;
	}
	if (remember->NEXT == NULL)
	{
		count++;
	}
	int left = 0;
	int right = count - 1;
	remember = start;
	UNIT** index = (UNIT*)malloc(sizeof(UNIT*) * count);
	for (int i = 0; i < count; i++, remember = remember->NEXT)
	{
		index[i] = remember;
	}
	QuickSort(index, left, right);
	for (int i = 0; i < count - 1; i++)
	{
		index[i]->NEXT = index[i + 1];
	}
	index[count - 1]->NEXT = NULL;
	return index[0];

	time_end = time(NULL);
	result = (double)(time_end - time_start);
	printf("수행시간 : %f초\n", result);
}