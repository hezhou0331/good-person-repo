#include<stdio.h>
#include<string.h>
void order(int m, int n, int a[100][100])
{
    int  row[100];
    int i = 0, j = 0, k = 0, temp, sum[100] = { 0 };
    for (i = 0; i < n; i++)
    {
        row[i] = i;
    }
    for (j = 0; j < n; j++)
    {
        for (k = 0; k < m - 1; k++)
        {
            for (i = 0; i < m - 1; i++)
                if (a[i][j] > a[i + 1][j])
                {
                    temp = a[i][j];
                    a[i][j] = a[i + 1][j];
                    a[i + 1][j] = temp;
                }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++) { sum[i] = a[j][i] + sum[i]; }
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
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
            printf("%d ", a[i][row[j]]);
        }
        printf("\n");
    }
}
int main()
{
    int m, n, x;
    scanf("%d%d", &m, &n);
    if (!((m > 0 && m < 100) && (n > 0 && n < 100)))
    {
        printf("ERROR"); return 0;
    }
    int a[100][100];
    int i = 0, j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    order(m, n, a);
    return 0;
}