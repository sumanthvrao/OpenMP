#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "main.h"

extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;

void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{
  #pragma omp parallel
    {
  for(int i = 0 ; i<MAXDIM ; i++ )
  {
      #pragma omp for 
      for(int j = 0 ; j<=i; j++)
      {
        //printf("%d of %d\n",omp_get_thread_num(),omp_get_num_threads());
      	
        int value = 0;
      		if(j==0 || (i==j))
 		  	{
 		  		value=1;
 		  		PTUpdateEntry( arr, i, j, value ) ;
 		  		continue;
 		  	}

 		  	#pragma omp task
 		  	{
          //printf("%d of %d\n",omp_get_thread_num(),omp_get_num_threads());
      		value = arr[i-1][j-1] + arr[i-1][j];
      		PTUpdateEntry( arr, i, j, value ) ;
        }
       	
          // Compute the value of the i, j th entry. Use tasks as appropriate
          // Update the entry in the table using the function PTUpdateEntry
      }
  	}	
  }
}

