#include<stdio.h>
#include<string.h>

int strdelete(char *s1, char *s2)
{
	char result[100]={'\0'};
    int i=0,j=0,k=0;
    int temp=1;
     
    for(i=0;i<strlen(s1);i++)
    {
        if(*(s1+i)!=*(s2))
            result[k++]=s1[i];
        else for(j=0;j<strlen(s2);j++)
        {
            if(s1[i+j]!=s2[j])
            {result[k++]=s1[i];break;}
            else {
                i=i+strlen(s2);
            }
        }
    }
	for(i=0;i<100;i++)
	{
		*(s1+i)=result[i];
	}
    return strlen(s1);
}
int main()
{
    char s1[100]={'\0'},s2[100]={'\0'};
    scanf("%s %s",s1,s2);
    int k=strdelete(s1,s2);
    printf("%s %d",s1,k);
    return 0;
}