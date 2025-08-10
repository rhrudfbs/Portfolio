#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct UNIT {
	char POSITION[20], NAME[20];
	int HP, ATT, DEF;
	struct UNIT* NEXT, * LEFT, * RIGHT;
}UNIT;

void MENU();
UNIT* Make_BT();
UNIT* insert();
void PrintAll_BT();
UNIT* Insert_BT();
void SearchByName_BT();
UNIT* Delete_BT();
UNIT* FindMinNode();
void SortByName_BT();
void PrintAll_SL();
UNIT* SortByName_SL();
void QuickSort();
int Partition();

int main(void)
{
	UNIT* root = NULL;
	UNIT* start = NULL;
	while (1)
	{
		int menu;
		printf("----------------------------------------------------------------------------------\n\n\n");
		MENU();
		scanf_s("%d%*c", &menu);
		if (menu == 1)
		{
			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			start = SortByName_SL(start);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 2)
		{
			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			root = Make_BT(root, &start);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 3)
		{
			char name[20];
			printf("Type The Name To Find\n");
			scanf_s("%s%*c", name, sizeof(name));



			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			SearchByName_BT(root, name);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 4)
		{
			UNIT* new = (UNIT*)malloc(sizeof(UNIT));
			printf("--------Type Information--------\n");
			printf("Position : ");
			scanf_s("%s%*c", &new->POSITION, sizeof(new->POSITION));
			printf("Name : ");
			scanf_s("%s%*c", &new->NAME, sizeof(new->NAME));
			printf("HP : ");
			scanf_s("%d%*c", &new->HP);
			printf("ATT : ");
			scanf_s("%d%*c", &new->ATT);
			printf("DEF : ");
			scanf_s("%d%*c", &new->DEF);
			new->NEXT = NULL;
			new->LEFT = NULL;
			new->RIGHT = NULL;



			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			root = Insert_BT(root, new);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 5)
		{
			UNIT* new = (UNIT*)malloc(sizeof(UNIT));
			printf("Type The Name To Delete\n");
			scanf_s("%s%*c", &new->NAME, sizeof(new->NAME));



			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			root = Delete_BT(root, new);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 6)
		{
			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			PrintAll_BT(root);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 7)
		{
			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			SortByName_BT(root);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
		else if (menu == 8)
		{
			time_t start_time, end_time;
			double result;
			start_time = time(NULL);



			PrintAll_SL(start);



			end_time = time(NULL);
			result = (double)(end_time - start_time);
			printf("%f Sec\n", result);
		}
	}
	return 0;
}

void MENU()
{
	printf("1. SortByName_SL\n");
	printf("2. Make_BT\n");
	printf("3. SearchByName_BT\n");
	printf("4. Insert_BT\n");
	printf("5. Delete_BT\n");
	printf("6. PrintAll_BT\n");
	printf("7. SortByName_BT\n");
	printf("8. PrintAll_SL To Check SortByName_SL\n");
	printf("부가 설명 : 먼저 프로그램을 실행하게 되면 파일의 데이터를 불러온 것이 아닙니다.\n");
	printf("부가 설명 : 실행하고 2번 메뉴를 선택해서 이진 탐색 트리 구조와 단방향 연결리스트를 만들게 합니다.\n");
	printf("부가 설명 : 2번 메뉴를 눌렀으면 이제 다른 메뉴를 선택해서 실행해 보실 수 있습니다.\n");
	printf("부가 설명 : 8번 메뉴를 추가해서 구현했는데 이는 연결리스트를 10000번째 노드마다 출력 하는 함수이고 1번 메뉴의 동작을 편하게 확인하실 수 있도록 구현해 놓았습니다.\n");
}

UNIT* Make_BT(UNIT* root, UNIT** start)
{
	int count = 0;
	UNIT* end = NULL;
	FILE* fp = NULL;
	fopen_s(&fp, "DS_Large.txt", "r");
	if (fp == NULL)
	{
		printf("Failed\n");
	}
	else
	{
		while (!feof(fp))
		{
			UNIT* new = (UNIT*)malloc(sizeof(UNIT));
			fscanf_s(fp, "%s %s %d %d %d", &new->POSITION, sizeof(new->POSITION), &new->NAME, sizeof(new->NAME), &new->HP, &new->ATT, &new->DEF);
			if (*start == NULL)
			{
				*start = new;
			}
			else
			{
				end->NEXT = new;
			}
			end = new;
			new->NEXT = NULL;
			new->LEFT = NULL;
			new->RIGHT = NULL;
			count++;
		}
		fclose(fp);
	}
	end = *start;
	UNIT** index = (UNIT*)malloc(sizeof(UNIT*) * count);
	for (int i = 0; i < count; i++, end = end->NEXT)
	{
		index[i] = end;
	}
	for (int i = 0; i < count; i++)
	{
		root = insert(root, index[i]);
	}
	return root;
}

UNIT* insert(UNIT* root, UNIT* index)
{
	if (root != NULL)
	{
		if (strcmp(root->NAME, index->NAME) > 0)
		{
			root->LEFT = insert(root->LEFT, index);
		}
		else if (strcmp(root->NAME, index->NAME) < 0)
		{
			root->RIGHT = insert(root->RIGHT, index);
		}
		return root;
	}
	else if (root == NULL)
	{
		root = index;
		return root;
	}
}

void PrintAll_BT(UNIT* root)
{
	if (root != NULL)
	{
		printf("%s %s %d %d %d\n", root->POSITION, root->NAME, root->HP, root->ATT, root->DEF);
		PrintAll_BT(root->LEFT);
		PrintAll_BT(root->RIGHT);
	}
}

UNIT* Insert_BT(UNIT* root, UNIT* index)
{
	if (root != NULL)
	{
		if (strcmp(root->NAME, index->NAME) > 0)
		{
			root->LEFT = Insert_BT(root->LEFT, index);
		}
		else if (strcmp(root->NAME, index->NAME) < 0)
		{
			root->RIGHT = Insert_BT(root->RIGHT, index);
		}
		return root;
	}
	else if (root == NULL)
	{
		root = index;
		return root;
	}
}

void SearchByName_BT(UNIT* root, char* name)
{
	if (root == NULL)
	{
		printf("No DAtA\n");
		return 0;
	}

	if (strcmp(root->NAME, name) != 0)
	{
		if (strcmp(root->NAME, name) > 0)
		{
			SearchByName_BT(root->LEFT, name);
		}
		else if (strcmp(root->NAME, name) < 0)
		{
			SearchByName_BT(root->RIGHT, name);
		}
	}
	else if (strcmp(root->NAME, name) == 0)
	{
		printf("%s %s %d %d %d\n", root->POSITION, root->NAME, root->HP, root->ATT, root->DEF);
		return 0;
	}
}

UNIT* Delete_BT(UNIT* root, UNIT* del)
{
	if (strcmp(root->NAME, del->NAME) != 0)
	{
		if (strcmp(root->NAME, del->NAME) > 0)
		{
			root->LEFT = Delete_BT(root->LEFT, del);
		}
		else if (strcmp(root->NAME, del->NAME) < 0)
		{
			root->RIGHT = Delete_BT(root->RIGHT, del);
		}
		return root;
	}
	else if (strcmp(root->NAME, del->NAME) == 0)
	{
		UNIT* deletenode = root;
		if (root->LEFT == NULL && root->RIGHT == NULL)
		{
			root = NULL;
		}
		else if (root->LEFT != NULL && root->RIGHT == NULL)
		{
			root = root->LEFT;
		}
		else if (root->LEFT == NULL && root->RIGHT != NULL)
		{
			root = root->RIGHT;
		}
		else
		{
			UNIT* minnode = NULL;
			root->RIGHT = FindMinNode(root->RIGHT, &minnode);
			minnode->LEFT = deletenode->LEFT;
			minnode->RIGHT = deletenode->RIGHT;
			root = minnode;
		}
		free(deletenode);
		return root;
	}
}

UNIT* FindMinNode(UNIT* root, UNIT** minnode)
{
	if (root->LEFT != NULL)
	{
		root->LEFT = FindMinNode(root->LEFT, minnode);
		return root;
	}
	else if (root->LEFT == NULL)
	{
		*minnode = root;
		root = root->RIGHT;
		return root;
	}
}

void SortByName_BT(UNIT* root)
{
	if (root != NULL)
	{
		SortByName_BT(root->LEFT);
		printf("%s %s %d %d %d\n", root->POSITION, root->NAME, root->HP, root->ATT, root->DEF);
		SortByName_BT(root->RIGHT);
	}
}

UNIT* SortByName_SL(UNIT* start)
{
	int count = 0;
	UNIT* rem = start;
	while (rem != NULL)
	{
		rem = rem->NEXT;
		count++;
	}
	UNIT** index = (UNIT*)malloc(sizeof(UNIT*) * count);
	rem = start;
	for (int i = 0; i < count; i++, rem = rem->NEXT)
	{
		index[i] = rem;
	}
	QuickSort(index, 0, count - 1);
	for (int i = 0; i < count - 1; i++)
	{
		index[i]->NEXT = index[i + 1];
	}
	index[count - 1]->NEXT = NULL;
	return index[0];
}

void QuickSort(UNIT** index, int left, int right)
{
	if (left < right)
	{
		int p = Partition(index, left, right);

		QuickSort(index, left, p - 1);
		QuickSort(index, p + 1, right);
	}
}

int Partition(UNIT** index, int left, int right)
{
	char* pivot = index[right]->NAME;
	int i = left - 1;
	for (int j = left; j < right; j++)
	{
		if (strcmp(pivot, index[j]->NAME) > 0)
		{
			i++;
			UNIT* temp = index[i];
			index[i] = index[j];
			index[j] = temp;
		}
	}
	UNIT* temp = index[i + 1];
	index[i + 1] = index[right];
	index[right] = temp;
	return i + 1;
}

void PrintAll_SL(UNIT* start)
{
	if (start != NULL)
	{
		printf("%s %s %d %d %d\n", start->POSITION, start->NAME, start->HP, start->ATT, start->DEF);
		for (int i = 0; i < 10000; i++)
		{
			start = start->NEXT;
			if (start == NULL)
			{
				break;
			}
		}
		if (start != NULL)
		{
			PrintAll_SL(start->NEXT);
		}
	}
}