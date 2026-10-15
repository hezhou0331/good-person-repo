#define _CRT_SECURE_NO_WARNINGS 1
//猜数字小游戏
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void menu()
{
	printf("1.play\n");
	printf("0.exit\n");
}

void game()
{
	int ret = (rand()%100)+1;
	int guess = 0;
	while (1)
	{
		printf("猜猜数字吧！（0-100）\n");
		scanf("%d", &guess);
		if (guess < ret)
			{ printf("猜小了！\n"); }
		else if (guess>ret)
		{printf("猜大了！\n"); }
		else {printf("你真是个天才！恭喜你，猜对了！\n"); break;}
	}
}
int main()
{
	//猜数字游戏的进入；
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();//打印菜单
		printf("请选择1/0\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("输入错误！");
			break;

		}
	} while (input);
	return 0;
}

