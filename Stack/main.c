#include <stdio.h>
#include <stdlib.h>
#include "glob.h"

top = -1;
buff[MAX-1];

int main()
{
	int ch,val;
	while(1)
	{
		printf("enter your choice\n1 - push\n2 - pop\n3 - TOS\n4 - display_stack\n5 - exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	val=1;
					while(val>0)
					{	printf("enter value to push:");
						scanf("%d",&val);
						if(val == 0) {break;}
						else push(val);
					}	break;
			case 2: pop();printf("\n");break;
			case 3: TOS();break;
			case 4: display_stack();break;
			case 5: exit(0);break;
			default:exit(0);
		}
	}
	return 0;
}