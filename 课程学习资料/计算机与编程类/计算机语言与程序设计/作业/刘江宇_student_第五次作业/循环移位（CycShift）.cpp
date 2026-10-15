#include<stdio.h>
#include<string.h>
void shift_vector(int m,int *vector, int number)
{
	if (!(0 < m && m < 100)) {
        printf("ERROR\n");
        return;
    }
	int i=0,n=number%m;
	if(n<0) n=n+m;
	//往左移动n位即可
	int temp[100]={0};
	for(i=0;i<m;i++)
	{
		temp[(i + n) % m] = *(vector+i);
	}
	for(i=0;i<m;i++)
	{
		printf("%d ",temp[i]);
	}
}
int main()
{
	int i=0,m,vector[100]={0};
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		scanf("%d",&vector[i]);
	}
	int number;
	scanf("%d",&number);
	shift_vector(m,vector,number);
	return 0;
}