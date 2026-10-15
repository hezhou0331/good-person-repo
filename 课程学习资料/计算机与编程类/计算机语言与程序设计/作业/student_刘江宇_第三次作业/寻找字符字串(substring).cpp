#include<stdio.h>
int main()
{
 char a[1000];
 scanf("%s",a);
 int i,count = 0;
 for(i=0;i<=998;i++)
 {
  if(a[i]=='a'&&a[i+1]=='b'&&a[i+2]=='a')
	  count++;
 }
 printf("%d",count);
 return 0;
}