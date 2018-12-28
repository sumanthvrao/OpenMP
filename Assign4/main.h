#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define MAXDIM 20
extern void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] ) ;
extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;
