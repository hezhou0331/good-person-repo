#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct STUDENT
{
	int num;
	struct STUDENT* next;
}STU;



int main()
{
	int N = 0, m = 0,i=0;
	scanf("%d %d", &N, &m);
	STU* header = (STU*)malloc(sizeof(STU));
	header->next = NULL;
	header->num = -1;
	STU* pprev = header;
	STU* pcurrent = header;
	STU* p = NULL;
	for (i = 1; i <= N; i++)
	{
		p = (STU*)malloc(sizeof(STU));
		p->num = i;
		pcurrent->next=p;
		pcurrent = pcurrent->next;
	}
	pcurrent->next = header->next;
	pcurrent = header->next;
	if (m == 1) { printf("%d", N); }
	else
	{
		while (pcurrent->next != pcurrent)
		{
			for (i = 1; i < m; i++)
			{
				pprev = pprev->next;
				pcurrent = pcurrent->next;
			}
			pprev->next = pcurrent->next;
			pcurrent = pcurrent->next;
		}
		printf("%d", pprev->num);
	}
	
	free(header);
	header = NULL;
	return 0;
}