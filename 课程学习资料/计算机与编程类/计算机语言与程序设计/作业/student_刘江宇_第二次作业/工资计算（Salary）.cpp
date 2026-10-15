#include<stdio.h>
int main()
{
	float a,salary;
	scanf("%f",&a);
	if(a<=8) salary = a*62.5;
	else salary = 8*62.5+62.5*1.5*(a-8);
	printf("%.2f",salary);
	return 0;

}