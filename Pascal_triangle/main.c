#include <stdio.h>
#include "main.h"
#define SLOW_THREAD 2
int twork[16] ;

// The routine will be tested with varying number of threads (e.g. 1, 2, 4, 8, 16, 32) and different validations to ensure that tasks have been used properly.

//PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value) is the function that updates the entry of the matrix.

// FillPascalTriangle( int arr[][] ) fills the array with values. Its input is only an array.

extern void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] ) ;

void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value)
{
  int tnum = omp_get_thread_num() ;
  #pragma omp critical
  twork[tnum]++ ;

  arr[i][j] = value ;

  if ( ( (tnum == SLOW_THREAD) && (rand()%1 == 0) ) || ( (tnum != SLOW_THREAD) && (rand()%100 == 0) ) )
  {
     double timex = time(NULL) ;
     while ( time(NULL) < (timex+.01) ) ;
  }
}

int main( int argc, char **argv )
{
    int arr[MAXDIM][MAXDIM+1] ;
    int row, col, numt=4, i ;

    double time1, time2;
    char status[100] ;
    int pf ;

    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
            arr[row][col] = 0 ;

    for( numt = 1 ; numt < 8 ; numt *= 2 )
    {
       omp_set_num_threads( numt ) ;

        for( i = 0 ; i < 16 ; i++ )
            twork[i] = 0 ;

        #pragma omp parallel
        {
          time1 = time(NULL) ;

          #pragma omp single
          FillPascalTriangle( arr ) ;

          #pragma omp barrier
          time2 = time(NULL) ;
        }

        pf = 1 ;
        for( row = 0 ; row < MAXDIM ; row++ )
        {
            for( col = 0 ; col <= row ; col++ )
            {
                int ans = 1 ;
                for( i = row ; i > (row-col) ; i-- )
                  ans *= i ;
                for( i = col ; i > 0 ; i-- )
                  ans /= i ;

                if ( ans != arr[row][col] )
                   pf = 0;
            }
        }

        if(pf == 0)
            strcpy( status, "Failed" ) ;
        else
            strcpy( status, "Passed" ) ;

        printf( "numt=%d, status=%s, workload=[%d", numt, status, twork[0] ) ;
        for( i = 1 ; i < numt ; i++ )
            printf( ",%d", twork[i] ) ;
        printf( "],time=%g\n", time2-time1 ) ;
    }
}

