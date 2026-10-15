#include<iostream>
#include"Complex.h"
using namespace std;

Complex::Complex(float r, float i)
{
	re=r;
	im=i;
}
void Complex::add(Complex com)
{
	re=re+com.re;
	im=im+com.im;
}
void Complex::show()
{
printf("%.2f + %.2fi",re,im);	
}
