#include<stdio.h>
long absolute(long num)
{
    if (num < 0) {
        return -num;
    } else 
		{return num;}
}

int main()
{
	int t1[3],t2[3],t3[3];
	long cha,t;
	scanf("%d:%d:%d",&t1[0],&t1[1],&t1[2]);
	scanf("%d:%d:%d",&t2[0],&t2[1],&t2[2]);
	cha = (t1[0]*3600+t1[1]*60+t1[2])-(t2[0]*3600+t2[1]*60+t2[2]);
	t = absolute(cha);
	t3[0] = t/3600;
	t3[1] = (t-t3[0]*3600)/60;
	t3[2] = (t-t3[0]*3600-t3[1]*60);
	printf("%02d:%02d:%02d",t3[0],t3[1],t3[2]);
	return 0;
}



