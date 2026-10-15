#include<stdio.h>
#include<string.h>
void MyReplace(char str[])
{
	int i=0;
	for(i=0;i<strlen(str);i++)
	{
		if(!((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')))
			str[i]=' ';
	}
	printf("Thr replaced str is %s\n",str);
}
int LongestWord(char str[])
{	char word[100][100]={{'\0'}};
	int i = 0,j=0,k=0;
			int count=0,max=1;
		for(i=0;i<strlen(str);i++)
	{
		for(j=0;j<100&&k<100;j++)
		{
			if(str[k]==' ')
			{k++;break;}
			else
			{word[i][j]=str[k];
			k++;}
		}
	}
    for(i=0;i<100;i++)
	{
		if(strlen(word[i])>max)
		{max =strlen(word[i]);}
	}
	return max;
}
int main()
{
	char str[100]={'\0'};
	fgets(str,100,stdin);
	MyReplace(str);
	int max=LongestWord(str);
	printf("%d",max);
	return 0;

}
