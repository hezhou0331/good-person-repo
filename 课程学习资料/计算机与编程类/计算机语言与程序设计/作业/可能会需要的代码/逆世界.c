#include<stdio.h>
#include<string.h>
void Turn(char arr[])
{
	char temp;
	int i;
	for (i = 0; i < strlen(arr) / 2; i++)
	{
		temp = arr[i];
		arr[i] = arr[strlen(arr) - 1 - i];
		arr[strlen(arr) - 1 - i] = temp;
	}
}
int main()
{
	char sentence[1000] = { '\0' };
	char word[100][100] = { {'\0'} };
	fgets(sentence, 1000, stdin);
	int i = 0, j = 0, k = 0;
	for (i = 0; i < 1000&&sentence[k]!='\0'; i++)
	{
		for (j = 0; (sentence[k] >= 'A' && sentence[k] <= 'Z') || (sentence[k] >= 'a' && sentence[k] <='z'); j++)
		{
			word[i][j] = sentence[k++];
		}
		k++;
	}
	for (j = 0; j < i + 1; j++)
	{
		Turn(word[j]);
	}
	int count = i;
	k = 0;
	for (i = 0; i < count;i++)
	{
		for (j = 0; j < strlen(word[i]); j++)
		{
			if ((sentence[k] >= 'A' && sentence[k] <= 'Z') || (sentence[k] >= 'a' && sentence[k] <= 'z'))
			{
				sentence[k++] = word[i][j];
			}
		}
		k++;
	}
	printf("%s", sentence);
	return 0;
}