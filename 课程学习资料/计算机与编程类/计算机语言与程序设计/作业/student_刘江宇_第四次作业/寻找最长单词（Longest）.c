#include<stdio.h>
#include<string.h>
void max(char all[]);
int main()
{
	char all[1000] = {'\0'};
	fgets(all,1000,stdin);
    max(all);
	return 0;
}
void max(char all[])
{
	char word[100][100]={{'\0'}};
	int i = 0,j=0,k=0;
			int count=0,max=1,max_=0;
		for(i=0;i<strlen(all);i++,k++)
	{
		for(j=0;j<100&&k<100&&all[k]!=32&&all[k]!=','&&all[k]!='.';j++)
		{
			word[i][j]=all[k];
			k++;
		}
	}
    for(i=0;i<count;i++)
	{
		if(strlen(word[i])>max)
			{max =strlen(word[i]);
		max_=i;}
	}
	for(i=0;i<max;i++)
	{
	printf("%c",word[max_][i]);
	}
}