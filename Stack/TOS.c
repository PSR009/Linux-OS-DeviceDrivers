#include "glob.h"

void TOS()
{
	if(top == -1)
		{printf("Stack Underflow\n");return;}
	else
		printf("TOS value = %d\n\n",buff[top]);
}