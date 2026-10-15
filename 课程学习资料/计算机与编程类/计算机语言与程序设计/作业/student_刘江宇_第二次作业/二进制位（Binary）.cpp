#include<stdio.h>
#include<math.h>
int main()
{
  int a,b,i;
  b = 0;
  scanf("%d",&a);
  for(i=1;a>0;i++)
  {
   if(a%2 ==1)b++;
   a = a/2;
  }
  printf("%d",b);
  return 0;
}