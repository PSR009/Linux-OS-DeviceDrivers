#include "glob.h"

void display_stack()
{
	int x = top;
	while(x != -1)
	{
		printf("%d\n",buff[x--]);
	}
	printf("\n");
}