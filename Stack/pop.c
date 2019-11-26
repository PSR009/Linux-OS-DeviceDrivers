#include "glob.h"

void pop()
{
	if(top == -1)
		{printf("Stack Underflow\n");return;}
	else
		printf("popped value = %d\n\n",buff[top--]);
}