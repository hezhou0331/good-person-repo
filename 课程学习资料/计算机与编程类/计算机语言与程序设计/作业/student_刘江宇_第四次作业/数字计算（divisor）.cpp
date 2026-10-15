#include<stdio.h>
#include<string.h>
int maxdivisor(int x,int y, int z)
{
	int i=1,divisor=1;
	for(i=1;i<=x&&i<=y&&i<=z;i++)
	{
	   if(x%i==0&&y%i==0&&z%i==0)
		   divisor=i;
	}
	return divisor;
}
void bubblesort(int arr[],int n)
{
	int temp;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j]<arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

int main()
{
	int p,q,r,i=0;
	int divisor[100]={1};
	int n=1;
	do
	{   save:
		scanf("%d%d%d",&p,&q,&r);
		if(p>=0&&q>=0&&r>=0)
		{divisor[i]=maxdivisor(p,q,r);
		n++;
		i++;}
		else {printf("error\n");goto save;}
	}while(p!=0&&q!=0&&r!=0);
	bubblesort(divisor,n);
		int count=0;
	for(i=0;i<n&&divisor[i]!='\0';i++)
	{
		if(divisor[i]==divisor[0])
			count++;
	}
	printf("%d %d",divisor[0],count);
	return 0;
}