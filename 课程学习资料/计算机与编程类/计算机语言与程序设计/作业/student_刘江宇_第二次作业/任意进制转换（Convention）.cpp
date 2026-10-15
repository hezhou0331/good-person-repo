#include<stdio.h>
#include<math.h>
int main()
{
 long n,a;
 int i;
 long m = 0;
 scanf("%ld %ld",&n,&a);
 for(i =0;n%a < n;n = n/a,i++)
 {
  int b = n%a;
  m = m+b*pow(10.0,i);
 }
 m = m+n*pow(10.0,i);
 printf("%ld",m);
 return 0;
 }