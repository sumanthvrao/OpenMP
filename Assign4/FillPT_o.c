#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "main.h"

extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;

void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{
    int i, j ;

    for( i = 0 ; i<MAXDIM ; i++ )
      for( j = 0 ; j<=i; j++ )
      {
      	  int value = 0 ;
 		  if(j==0 || (i==j))
 		  {
 		  	value=1;
 		  	PTUpdateEntry( arr, i, j, value ) ;
 		  	continue;
 		  }
 		  value = arr[i-1][j-1] + arr[i-1][j];
          // Compute the value of the i, j th entry. Use tasks as appropriate
          // Update the entry in the table using the function PTUpdateEntry
          PTUpdateEntry( arr, i, j, value ) ;
      }
}

