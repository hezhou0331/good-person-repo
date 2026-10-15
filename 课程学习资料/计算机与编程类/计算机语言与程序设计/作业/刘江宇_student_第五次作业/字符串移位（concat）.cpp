#include<stdio.h>
#include<string.h>
char *strcattype(char *s1, char *s2, int type)
{
   char result[1000]={'\0'};
    int i=0;
    if(type==1)
    {
        for(i=0;i<strlen(s1);i++)
        {result[i]=*(s1+i);}
        for(i=strlen(s1);i<strlen(s1)+strlen(s2);i++)
        {result[i]=*(s2-strlen(s1)+i);}
    }if(type==2)
    {
        for(i=0;i<strlen(s2);i++)
        {result[i]=*(s2+i);}
        for(i=strlen(s2);i<strlen(s1)+strlen(s2);i++)
        {result[i]=*(s1-strlen(s2)+i);}
    }
	for(i=0;i<1000;i++)
	{
		*(s1+i)=result[i];
	}
        return s1;
}
 
int main()
{
    int type=0;
    char s1[1000],s2[1000];
    scanf("%s %s",s1,s2);
    scanf("%d",&type);
    char *p=strcattype(s1,s2,type);
    printf("%s ",p);
    printf("%d",strlen(p));
    return 0;
}