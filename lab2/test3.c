#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void change(int **array, int length)
{
    *array = malloc(length * sizeof(int));
    if (*array == NULL)
        return;
    for (int i = 0 ; i < length ; i++)
        (*array)[i] = i;
}


int main()
{
	int length = 7;
	int *array;
	array = NULL;
	change(&array, length);
	//change(&array, length);
	//change(&array, length);
	//change(&array, length);
	
	for(int i = 0;i<7;i++)
	{
		printf("%d, ", array[i]);
	}
	free(array);	
	return 0;
}