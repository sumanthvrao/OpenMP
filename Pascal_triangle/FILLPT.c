#include <stdio.h>
#include "main.h"

extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;

void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{
    int i, j ;

    for( i = 0 ; i <  MAXDIM ; i++ )
      for( j = 0 ; j <=  i ; j++ )
        if ( ( j == 0 ) || ( j == i ) || ( i== 0 ) )
          #pragma omp task depend( out: arr[i][j] )
          PTUpdateEntry( arr, i, j, 1 ) ;
        else
          #pragma omp task depend( in: arr[i-1][j-1], arr[i-1][j] ) depend( out: arr[i][j] )
          PTUpdateEntry( arr, i, j, arr[i-1][j-1]+arr[i-1][j] ) ;
}