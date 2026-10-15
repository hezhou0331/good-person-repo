#include<stdio.h>
#include<math.h>
int main()
{
 long n,a;
 long m = 0;
 scanf("%ld %ld",&n,&a);
 for(int i =1;n/a>0;n = n/a,i++)
 {
  int b = n%a;
  m = m+b*pow(10.0,i);
 }
 printf("%ld",m);
 return 0;
 }