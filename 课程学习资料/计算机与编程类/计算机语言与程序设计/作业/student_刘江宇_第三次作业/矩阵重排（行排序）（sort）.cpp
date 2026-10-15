#include<stdio.h>
#include<string.h>
//冒泡排序
void bubblesort(int a[], int n);
void bubblesort(int a[], int n)
{
    int i, j, tem;
    for (i = 0; i < n - 1; i++)
    {
        int count = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
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
int main()
{
    int m, n, temp;
    scanf("%d%d", &m, &n);
    int a[20][20], row[20];
    int sum[20] = { 0 };
    if (m > 20 || m <= 0 || n > 20 || n <= 0) { printf("error"); return 0; }

    int i = 0, j = 0;
    for (i = 0; i < m; i++)
    {
        row[i] = i;
        for (j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for (i = 0; i < m; i++)
    {
        bubblesort(a[i], n);
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++) { sum[i] = a[i][j] + sum[i]; }
    }
    for (i = 0; i < m - 1; i++)
    {
        for (j = 0; j < m - 1 - i; j++)
        {
            if (sum[j] > sum[j + 1])
            {
                temp = sum[j];
                sum[j] = sum[j + 1];
                sum[j + 1] = temp;
                temp = row[j];
                row[j] = row[j + 1];
                row[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", a[row[i]][j]);
        }
        printf("\n");
    }
    return 0;
}