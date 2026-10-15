#include<stdio.h>
#include<string.h>
void Turn(char str[])
{
	char i=0,temp;
	for(i=0;i<strlen(str)/2;i++)
	{
		temp=str[i];
		str[i]=str[strlen(str)-1-i];
		str[strlen(str)-1-i]=temp;
	}
}
void Eliminate(char str[])
{
	int i = 0,j=0;
	char str1[1000];
	int count=0;
	strcpy(str1,str);
	Turn(str);
		for (i = 0; i < strlen(str)-2; i++)
		{
			count = 0;
			for(j=i;j<strlen(str);j++)
			{
				if(str[i]==str[j])
					count++;
				if(str[i]!=str[j])
				break;
			}
			if(count>=3)
			{
				for (j = i; j < strlen(str); j++)
			{
				str[j] = str[j + count];
			}
			}
		}
		Turn(str);
		if(strcmp(str1,str)!=0)
		{ Eliminate(str);}
}
int main()
{
	char str[1000] = { '\0' };
	scanf("%s", str);
	printf("0:%s\n", str);
	Eliminate(str);
	printf("1:%s\n", str);
	return 0;
}