#include<stdio.h>
int main()
{
	int number,n;
	float prize,pay,discount;
	scanf("%d %f",&number,&prize);
	n = (number*prize)/100;
	discount = 20*n;
	pay = number*prize-discount;
	printf("%.2f %.2f",discount,pay);
	return 0;
}
