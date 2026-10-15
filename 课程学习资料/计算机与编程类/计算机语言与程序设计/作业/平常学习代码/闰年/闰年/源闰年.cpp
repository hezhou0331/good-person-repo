#include<stdio.h>
int main()
{
  while(1)
 {int year;
  scanf("%d",&year);
  if((year%4==0&&(year%100 != 0)||(year%400==0)))
	  printf("闰年\n");
  else printf("不是闰年\n");
  }
  return 0;
}