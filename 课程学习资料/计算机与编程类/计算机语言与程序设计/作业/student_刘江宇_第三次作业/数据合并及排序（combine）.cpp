#include<stdio.h>
#include<string.h>
void bubblesort(int a[],int m)
{
	int i, j,temp;
	for (i = 0; i < m-1; i++)
	{
		for (j=0; j < m-i-1; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}
int main()
{
	int  a[5][20],b[100];
	int m, i,j=0,k=0;
	scanf ("%d",&m);
	for (i = 0; i < m; i++)
	{
		for (j=0;j<20 ; j++)
		{
			scanf ("%d,", &a[i][j]);
			if (a[i][j] == 0) break;
			b[k++] = a[i][j];
	
		}
	}
	bubblesort(b,k);
	for (i = 0; i < k; i++)
	{
		printf("%d", b[i]);
		if (i < k - 1) printf(",");
	}
	return 0;
}