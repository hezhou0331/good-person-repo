#include<stdio.h>
#include<string.h>
#include<math.h>
float f(float x, float a, float b, float c, float d, float e);
float finalroot(float x1,float x2,float a, float b, float c, float d, float e);
float xpoint(float x1,float x2,float a, float b, float c, float d, float e);
int main()
{
	float a,b,c,d,e;
	float x1,x2;
	scanf("%f,%f,%f,%f,%f", &a, &b, &c, &d, &e);
	scanf("%f,%f", &x1, &x2);
	printf("%.3f",finalroot(x1, x2, a, b, c, d, e));
	return 0;
}

float f(float x, float a, float b, float c, float d, float e)
{
	return pow(x,5)+a*pow(x,4)+b*pow(x,3)+c*pow(x,2)+d*pow(x,1)+e;
}
float xpoint(float x1,float x2,float a, float b, float c, float d, float e)
{
	float k=(f(x1,a,b,c,d,e)-f(x2,a,b,c,d,e))/(x1-x2);
	return x2-f(x2,a,b,c,d,e)/k;
}
float finalroot(float x1, float x2, float a, float b, float c, float d, float e)
{
	float x3;
	float epsilon = 1e-6;
	do
	{
		x3 = xpoint(x1, x2, a, b, c, d, e);
		if (f(x1, a, b, c, d, e) * f(x3, a, b, c, d, e) < 0)
		{
			x2 = x3;
		}
		else {
			x1 = x3;
		}
		printf("x1=%f\n", x1);
		printf("x2=%f\n", x2);
		printf("x3=%f\n",x3);
	} while (fabs(x2 - x1) > epsilon&&fabs(f(x3,a,b,c,d,e))>epsilon);
	return x3;



    return x3;
}