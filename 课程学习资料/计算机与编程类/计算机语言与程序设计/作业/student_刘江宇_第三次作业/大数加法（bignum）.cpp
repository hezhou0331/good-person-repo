#include<stdio.h>
#include<string.h>
int main()
{
	char char_a[100], char_b[100], char_c[101];
	int a[101] = { 0 };
	int b[101] = { 0 };
	int c[101] = { 0 };
	int i = 0, len_a, len_b, len_c, temp, len;
	fgets(char_a, 100, stdin);
	fgets(char_b, 100, stdin);
	len_a = strlen(char_a) - 1, len_b = strlen(char_b) - 1;
	for (i = 0; i < len_a; i++)
	{
		a[i] = char_a[i] - '0';
	}
	for (i = 0; i < len_b; i++)
	{
		b[i] = char_b[i] - '0';
	}
	for (i = len_a; i < 100; i++)
	{
		a[i] = 0;
	}
	for (i = 0; i < len_a / 2; i++)
	{
		temp = a[i];
		a[i] = a[len_a - i - 1];
		a[len_a - i - 1] = temp;
	}
	for (i = 0; i < len_b / 2; i++)
	{
		temp = b[i];
		b[i] = b[len_b - i - 1];
		b[len_b - i - 1] = temp;
	}
	len = len_a > len_b ? len_a : len_b;
	len_c = len;
	for (i = 0; i < len; i++)
	{
		c[i] = a[i] + b[i] + c[i];
		if (c[i] > 9)
		{
			c[i] = c[i] - 10;
			c[i + 1] = c[i+1]+1;
			if (i == len - 1)
			{
				len_c = len + 1;
			}
		}
	}
	for (i = 0; i < len_c / 2; i++)
	{
		temp = c[i];
		c[i] = c[len_c - i - 1];
		c[len_c - i - 1] = temp;
	}
	for (i = 0; i < len_c; i++)
	{
		printf("%d", c[i]);
	}
	return 0;
}