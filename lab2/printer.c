#include <stdio.h>

int main()
{
	for(int i=0;i<29;i++)
	{
		printf(".e[%d]={{},{}},", i);
	}
	return 0;
}
