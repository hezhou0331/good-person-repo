#include<stdio.h>
#include<math.h>
int main()
{
 int a,b,c;
 float C,S,p;
 scanf("%d %d %d",&a,&b,&c);
 if((a>=b+c)||(b>=a+c)||(c>=a+b)) 
  {printf("Error");return 0;}
 else {
	 C=a+b+c;
	 p=C/2;
	 S=sqrt(p*(p-a)*(p-b)*(p-c));
      }
 printf("%.2f %.2f",C,S);
 return 0;

}