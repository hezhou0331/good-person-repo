#include<stdio.h>
#include<string.h>
int InputStrS(char str1[],char str2[],int* n)
{
	scanf("%s", str1);
	scanf("%s",str2);
	str1[strcspn(str1, "\n")] = 0;
	scanf("%d",n);
	return *n;
}
void MyInverse(char str[])
{
	char a[1000] = {'\0'};
	int i=0,n=strlen(str);
	for(i=0;i<n;i++)
	{
		a[i]=str[n-i-1];
	}
	for(i=0;i<n;i++)
	{
		str[i]=a[i];
	}
}
void MyInsert(char str1[], char str2[], int n)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char temp[1000] = { '\0' };
	if (n <= 0)
	{
		strcat(temp, str2);
		strcat(temp, str1);
		strcpy(str1, temp);
	}
	if (n > 0 && n <= len1)
	{
		for (int i = 0; i < n; i++)
		{
			temp[i] = str1[i];
		}
		for (int i = n; i < n + len2; i++)
		{
			temp[i] = str2[i-n];
		}
		for (int i = n +len2; i < len1+len2; i++)
		{
			temp[i] = str1[i-len2];
		}
		for (int i = 0; i < len1+len2; i++)
		{
			str1[i] = temp[i];
		}
	}
	if (n > len1)
	{
		strcat(str1, str2);
	}
}
int main()
{
	char str1[100]={'\0'},str2[100]={'\0'};
	int n=8;
	InputStrS(str1,str2,&n);
	printf("%s %s %d\n",str1,str2,n);
	MyInverse(str2);
	MyInsert(str1,str2,n);
	printf("str1=%s\nstr2=%s",str1,str2);
	return 0;

}