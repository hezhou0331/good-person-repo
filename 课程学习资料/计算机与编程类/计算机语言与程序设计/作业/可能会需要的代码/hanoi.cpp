#include<stdio.h>
void hanoi(int n, char a, char b, char help)
{
	if (n == 1)
	{
		printf("move 1 from %c to %c\n", a, b);
		return;
	}
	hanoi(n - 1, a, help, b);
	printf("move %d from %c to %c\n", n, a, b);
	hanoi(n - 1, help, b, a);
}
int main()
{
	int n = 0;
	char a = 'A', b = 'C', help = 'B';
	scanf_s("%d", &n);
	hanoi(n, a, b, help);
}