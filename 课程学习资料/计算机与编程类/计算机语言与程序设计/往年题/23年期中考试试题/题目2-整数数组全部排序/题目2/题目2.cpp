#include<stdio.h>
#include<string.h>
//冒泡排序>从大到小
void bubblesort(int a[], int n);
void bubblesort(int a[], int n)
{
    int i, j, tem;
    for (i = 0; i < n - 1; i++)
    {
        int count = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] < a[j + 1])
            {
                tem = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tem;
                count = 1;
            }
        }
        if (count == 0) { break; }
    }
}
void SortMatrix(int matrix[50][50], int m, int n)
{
    int temp;
    int  row[2500];
    int i = 0, j = 0,k=0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            row[k++] = matrix[i][j];
        }
    }
    bubblesort(row, m * n);
    k = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrix[i][j]=row[k++];
        }
    }

}
void PrintMatrix(int matrix[50][50],int m,int n)
{
    int i = 0, j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
		printf("\n");
    }
}
int main()
{
    int matrix[50][50] = { {'\0' }};
    int m, n;
    printf("please input m and n:");
    scanf("%d%d", &m, &n);
    printf("please input elements of matrix:\n");
	  int i = 0, j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
	printf("after sorting:\n");
    SortMatrix(matrix, m, n);
    PrintMatrix(matrix,m,n);
    return 0;
}