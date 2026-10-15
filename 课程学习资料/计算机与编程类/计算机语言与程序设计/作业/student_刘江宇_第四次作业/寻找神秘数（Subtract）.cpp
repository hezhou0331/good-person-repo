#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
void bubblesort(char arr[])
{
	int i = 0, j = 0;
	for (i = 0; i < strlen(arr); i++)
	{
		for (j = 0; j < strlen(arr) - i - 1; j++)
		{
			char temp;
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void max(char arr[], char maxnum[])
{
	maxnum[4] = '\0';
	bubblesort(arr);
	for (int i = 0; i < 4; i++)
	{
		maxnum[i] = arr[i];
	}
	maxnum[4] =  '\0' ;
}
void min(char arr[], char minnum[])
{
	bubblesort(arr);
	for (int i = 0; i < 4; i++)
	{
		minnum[i] = arr[3 - i];
	}
	minnum[4] = '\0' ;
}
long  deta(char maxnum[], char minnum[])
{
	long detanum = 0;
	for (int i = 0; i < 4; i++)
	{
		detanum += (maxnum[i] - '0') * pow(10, 3 - i) - (minnum[i] - '0') * pow(10, 3 - i);
	}
	return detanum;
}
int main()
{
	char begin[5] = { '\0' };
	char maxn[5] = { '\0' }, minn[5] = { '\0' };
	long detan, detan0,maxn1=0,minn1=0;
	int i = 0;
	scanf("%s", begin);
	if (begin[0] == begin[1] && begin[1] == begin[2] && begin[3] == begin[2])
	{
		printf("ERROR");
		return 0;
	}
	max(begin, maxn);
	min(begin, minn);
	detan = deta(maxn, minn);
	for (i = 0; i < 4; i++)
	{
		maxn1 += (maxn[i] - '0') * pow(10, 3 - i);
		minn1 += (minn[i] - '0') * pow(10, 3 - i);
	}
	do
	{
		detan0 = detan;
		printf("(%ld,%ld,%ld)\n", maxn1, minn1, detan);
		for (i = 0; i < 4; i++)
		{
			begin[i] = (detan / (int)pow(10, 3 - i))%10+'0';
		}
		begin[4] = '\0';
		max(begin, maxn);
		min(begin, minn);
		maxn1 = 0;
		minn1 = 0;
		for (i = 0; i < 4; i++)
		{
			maxn1 += (maxn[i] - '0') * pow(10, 3 - i);
			minn1 += (minn[i] - '0') * pow(10, 3 - i);
		}
		detan = deta(maxn, minn);
	} while (detan != detan0);
	return 0;
}