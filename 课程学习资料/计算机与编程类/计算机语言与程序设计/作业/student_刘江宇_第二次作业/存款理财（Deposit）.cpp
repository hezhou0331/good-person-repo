#include<stdio.h>
#include<math.h>
int main()
{
	int i,r;
	float m,n;
	scanf("%f %d",&m,&i);
	switch(i)
	{
	case 1:n = m*(1+5*0.055);break;
	case 2:n = m*(1+2*0.044);n = n*(1+3*0.05);break;
	case 3:n = m*(1+3*0.05);n = n*(1+2*0.044);break;
	case 4:for(n = m;i<5;i++){n=n*(1+0.035);};break;
	case 5:for(n=m;i<20;i++){n = n*(1+0.005/4);}break;
	default:n = m;
	}
	printf("%.2f",n);
	return 0;
}