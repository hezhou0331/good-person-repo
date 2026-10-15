#include<stdio.h>
#include<string.h>
int main()
{
  char a[200],b[200];
  int count1=0,count2=0,count3=0,count4=0,i;
  fgets(a,200,stdin);
  for(int i =0;i<199;i++ )
  {b[i] = a[i];}
 for(i = 0;a[i]!='.';i++)
 {if(a[i]>='A'&&a[i]<'Z') a[i]=a[i]+32;}
  for(i = 0;a[i]!='.';i++)
  {if(a[i]<=122&&a[i]>=97) count1++;}
  for( i =0;a[i]!='.';i++ )
  {
    if(b[i]<=122&&b[i]>=97) a[i]=a[i]-32; 
  }
  for(i=0;a[i]!=0;i++)
  {if(a[i]==' ') count2++;}
   for(i=0;a[i]!=0;i++)
  {if(a[i]>='0'&&a[i]<='9') count3++;}
 count4 = strlen(a)-count1-count2-count3-1;
  printf("%s",a);
  printf("%d\n",count1);
  printf("%d\n",count2);
  printf("%d\n",count3);
  printf("%d\n",count4);
  return 0;
}