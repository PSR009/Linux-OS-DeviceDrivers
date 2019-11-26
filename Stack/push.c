#include "glob.h"

void push(int val)
{
	if(top == MAX-1)
		{printf("Stack Overflow\n");return;}
	else
		buff[++top] = val;
}