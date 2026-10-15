#include<stdio.h>
int main()
{
	float a,b,c,d;
	scanf("%f%fi %f%fi",&a,&b,&c,&d);
	float m,n;
	m = a*c-b*d;
	n = b*c+a*d;
	printf("%.3f%+.3fi",m,n);
	return 0;
}