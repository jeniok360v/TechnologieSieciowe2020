#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#define probability 4.999999f

int main(int argc, char **argv) {
	 
	
    char *s;
    if (__builtin_types_compatible_p(__typeof__(probability), float)) {
        puts("float");
    } else if (__builtin_types_compatible_p(__typeof__(probability), char*)) {
        puts("str");
    }
	printf("%d", (int)probability);
    return (0);
}

/*






int** foo();

int main()
{
	printf();
	bool broken = 0;
	for (int i=-2;i<3;i++)
	{
		broken = i;
		if(broken)
			printf("broken!(%d)\n", i);
		if(!broken)
			printf("not broken(%d)\n", i);
	}
	int lost = 5;
	int act = 3;
	float perc = (float)(lost)/(float)(act-lost);
	//float lost_pack = (float)(grptr->e[i].lost)/(float)(grptr->e[i].actual-grptr->e[i].lost);
	
	
	/*
	//time_t t;
	//srand((unsigned) time(&t));
	srand(time(NULL));
	int k = rand();
	printf("%d - rand\n", k);
	
	
	if(0)
		printf("0 ");
	if(-1)
		printf("-1 ");
	if(2)
		printf("2 ");
	if(1)
		printf("1 ");

	int** a = (int**)malloc(sizeof(int*)*30);
	a = foo();
	int size = *a[0];
	int arra[size];
	memcpy(arra, a, sizeof(int*)*30);
	printf("size - %d\n",size);
	for(int i=0;i<5;i++)
	{
		printf("%d, \n", arra[i]);
	}
		
}

int** foo()
{
	int** arr;
	int arra[5];
	arra[0]=4;	//size 
	for(int i=1;i<5;i++)
	{
		arra[i]=i+8;
	}
	for(int i=1;i<5;i++)
	{
		*arr[i] = arra[i];
	}
	return arr;
}

*/
