#include<stdio.h>
#include<string.h>
int main()
{
	char all[1000];
	char word[1000][1000] = { {'\0'}};
	int count[1000] = { 0 },row[1000],len[1000];
	fgets(all, 1000, stdin);
	int i, j, k = 0,temp;
	int max = 0;
	for (i = 0; i < 1000; i++,k++)
	{
		for (j = 0; all[k] != 32 && all[k] != '\t' && all[k] != '\n'&&all[k]!='\0'; j++)
		{
			word[i][j] = all[k];
			k++;
		}
		if (strcmp(word[i],"end")==0)
		{
			break;
		}
		len[i] = strlen(word[i]);
	}
	for (i = 0; i < 1000; i++)
	{
		for (j = i; j < 1000 && strlen(word[j])!=0; j++)
		{
			if (strcmp(word[i], word[j]) == 0)
			{
				count[i]++;
			}
		}
	}
	for(i=0;i<1000;i++)
	{
		row[i] = i;
	}
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 1000 - i - 1; j++)
		{
			if (count[j] < count[j + 1])
			{
				temp = count[j];
				count[j] = count[j + 1];
				count[j + 1] = temp;
				temp = row[j];
				row[j] = row[j + 1];
				row[j + 1] = temp;
			}
		}
	}
	j = 0;
do
{
		for (i = 0; i < strlen(word[row[j]]); i++)
		{
			printf("%c", word[row[j]][i]);
		}
		printf(" %d", count[0]);
		printf("\n");
		j++;

} while (count[j] != count[j + 1]);

	return 0;
}