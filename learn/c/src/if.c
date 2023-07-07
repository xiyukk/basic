#include<stdio.h>
int main()
{
	int x = 2;
	printf("x value:%d\n",x);
	printf("code:'x==2'\nvalue:%d\n" ,x==2);
	printf("code:'x!=2'\nvalue:%d\n" ,x!=2);
	printf("code:'x=3'\nvalue:%d\n" ,x=3);
	printf("code:'x-1'\nvalue:%d\n" ,x-1);
	printf("code:'!x'\nvalue:%d\n" ,!x);
	printf("code:'!1'\nvalue:%d\n" ,!1);
	printf("code:'!0'\nvalue:%d\n" ,!0);
	printf("code:'x'\nvalue:%d\n" ,x);
 
	printf("\n");
	if(0)
	{
		printf("if(0) is running!\n");
	}
	if(1)
	{
		printf("if(1) is running!\n");
	}
	if(x)
	{
		printf("if(x) is running!\n");
	}
	if(x = 0)
	{
		printf("if(x = 0) is running!\n");
	}
	if(x = 1)
	{
		printf("if(x = 1) is running!\n");
	}
	return 0;
}