#include<stdio.h>
#include<math.h>

int main()
{
	float data[12],datas[6];
	for(int i = 0;i<12;i++)
	{scanf("%f",&data[i]);}
	for(int k=0;k<6;k++)
	{datas[k] = (float)((int)(data[k]*1000))/1000;}
	printf("%-6.3f %-6.3f\n",datas[0],datas[1]);
	printf("%-6.3f %-6.3f\n",datas[2],datas[3]);
	printf("%-6.3f %-6.3f\n",datas[4],datas[5]);
	printf("%6.2f %6.2f %6.2f\n",data[6],data[7],data[8]);
	printf("%6.2f %6.2f %6.2f\n",data[9],data[10],data[11]);
	return 0;
}
