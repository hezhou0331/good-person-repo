#include<stdio.h>
#include<string.h>
int Longest_substring(char s1[256], char s2[256], char s3[256])
{
	char same[256] = {'\0'};
	int len_max = 0, i = 0, j = 0, k = 0;
	int num1 = 0, num2 = 0, num3 = 0;
	fgets(s1, 256, stdin);
	s1[strcspn(s1, "\n")] = 0;
	fgets(s2, 256, stdin);
	s2[strcspn(s2, "\n")] = 0;
	fgets(s3, 256, stdin);
	s3[strcspn(s3, "\n")] = 0;
	int len1 = strlen(s1), len2 = strlen(s2), len3 = strlen(s3);
	//save;
	char word1[20][20] = { {'\0'} }, word2[20][20] = { {'\0'} }, word3[20][20] = { {'\0'} };
	for (i = 0; k < len1; i++)
	{
		for (j = 0; k < len1; j++)
		{
			if (s1[k] != ' ')
				word1[i][j] = s1[k++];
			else { k++; break; }
		}
	}num1 = i;
	k = 0;
	for (i = 0; k < len2; i++)
	{
		for (j = 0; k < len2; j++)
		{
			if (s2[k] != ' ')
				word2[i][j] = s2[k++];
			else { k++; break; }
		}
	}num2 = i;
	k = 0;
	for (i = 0; k < len3; i++)
	{
		for (j = 0; k < len3; j++)
		{
			if (s3[k] != ' ')
				word3[i][j] = s3[k++];
			else { k++; break; }
		}
	}num3 = i; k = 0;
	int temp = 0;
	for (i = 0; i < num1; i++)
	{
		temp = 0;
		for (j = 0; j < num2; j++)
		{
			if (strcmp(word1[i], word2[j]) == 0) { temp = 1; break; }
		}
		for (j = 0; j < num3; j++)
		{
			if (strcmp(word1[i], word3[j]) == 0) { temp = temp+1; break; }
		}
		if (temp==2)
		{
			strcat(same, word1[i]);
			strcat(same, " ");
			if (strlen(word1[i]) > len_max)
			{
				len_max = strlen(word1[i]);
			}
		}
	}
	if (strlen(same) == 0)
	{
		printf("NULL");
		return 0;
     }
	printf("%s%d", same, len_max);
	return len_max;
}
int main()
{
	char s1[256] = { '\0' }, s2[256] = { '\0' }, s3[256] = { '\0' };
	int len = Longest_substring(s1, s2, s3);
	return 0;
}