#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* function to generate and return random numbers */
int** getRandom(int **p ) {

  int  r[10];
   
	*p = malloc(10 * sizeof(int));
   /* set the seed */
  srand(time(NULL));
  
   for (int i = 0; i < 10; ++i) {
      (*p)[i] = rand()%13;
      printf( "*p[%d] = %d\n", i, *p[i]);
   }

   //return p;
}

/* main function to call above defined function */
int main () {

   /* a pointer to an int */
   int *p;
   int i;
	p = NULL;
   getRandom(&p);
	
   for ( i = 0; i < 10; i++ ) {
      printf( "*(p + %d) : %d\n", i, *(p + i));
   }
   free(p);

   return 0;
}