#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main()
{
	char key0[1000] = { '\0' };
	char key[1000] = { '\0' };
	char alpha[27];
	char result[1000] = { '\0' };
	char password[1000] = { '\0' };
	int i = 0, a = 1,j=0,k=0,x=0;
	for(i=0;i<26;i++)
	{
		alpha[i] = 'A' + i;
	}
	alpha[26] = '\0';
	scanf("%s", key0);
	scanf("%s", password);
	for (i = 0; i < strlen(key0); i++)
	{
		x = 1;
		for (j = 0; j < i; j++)
		{
			if (key0[i] == key0[j])
			{ 
				x = 0;
				break;
			}
		}
		if (x)
		{
			key[k++] = key0[i];
		}
	}
	key[k] = '\0';
	for (i = 0; i < strlen(key); i++)
	{
		for (j = 0; j < strlen(key); j++)
		{
			if (alpha[i] == key[j])
			{
				for (k = i; alpha[k] != '\0'; k++)
					alpha[k] = alpha[k + 1];
			}
		}
	}
	strcat(key, alpha);
	for (i = 0; i < strlen(password); i++)
	{
		result[i] = key [password[i] - 'A'];
		printf("%c", result[i]);
	}
	return 0;
}