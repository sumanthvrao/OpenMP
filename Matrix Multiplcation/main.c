#include <stdio.h>
#include "matrix.h"

// Input contains three matrices A,B,C and alpha and Beta.
// A of dimensions m X n.
// B of dimensions n X p.
// C of dimensions m X p.
// Output is a matrix D of dimensions m X p.
// Task is to write a routine which computes a NEW matrix C such that:
// C = alpha x A x B + beta x C

// This main functions tests the speed of program by using matrices
// of varying dimesions from 1024 X 1024 to 1536 X 1536 in steps of 256.
// Each time it launches different threads from 1 till 4 in steps of 2.

//MatMul( m, n, p, b, alpha, beta, A, B, C ) is the function that solves computes the matrix C.

int main( int argc, char **argv )
{
    double *A, *B, *C, *Corg, alpha, beta, time1, time2;
    int m, n, p, b, bb, bbmin, bbmax ;
    int row, col, numt ;
    char status[100] ;

    alpha = (double) 1.3 ;
    beta  = (double) 2.9 ;

    A = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    B = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    C = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    Corg = (double *) malloc( sizeof(double) * MAXDIM * MAXDIM ) ;
    if ( ( A == NULL ) || ( B == NULL ) || ( C == NULL ) || ( Corg == NULL ) )
    {
        printf( "Out of Memory\n" ) ;
        exit(1) ;
    }

    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
            A[row*MAXDIM+col] = rand() ;

    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
            B[row*MAXDIM+col] = rand() ;

    for( row = 0 ; row < MAXDIM ; row++ )
        for( col = 0 ; col < MAXDIM ; col++ )
            Corg[row*MAXDIM+col] = rand() ;

    for( m = MINDIM ; m <= MAXDIM ; m += 256 )
    {
             n = p = m ;
             for( numt = 1 ; numt <= 4 ; numt *= 2 )
             {
                if ( numt == 4 )
                {
                    bbmin = 4 ;
                    bbmax = 64 ;
                }
                else
                    bbmin = bbmax = 16 ;
                for( bb = bbmin ; bb <= bbmax ; bb *= 4 )
                {
                    for( row = 0 ; row < m ; row++ )
                        for( col = 0 ; col < p ; col++ )
                            C[row*p+col] = Corg[row*p+col] ;
                    b = bb ;
                    if ( b > m ) b = m ;
                    if ( b > n ) b = n ;
                    if ( b > p ) b = p ;

                    omp_set_num_threads( numt ) ;
                    time1 = time(NULL) ;
                    MatMul( m, n, p, b, alpha, beta, A, B, C ) ;
                    time2 = time(NULL) ;

                    /* Validate random entries */
                    int success = 1, r ;
                    for(  r = 0 ; r < NUM_VALIDATES ; r++ )
                    {
                        double min, max, err, ans ;

                        row = ( rand() % m ) ;
                        col = ( rand() % p ) ;

                        int k ;
                        ans = Corg[row*p+col] * beta ;
                        for( k = 0 ; k < n ; k++ )
                            ans += alpha * A[row*n+k]*B[k*p+col] ;

                        if (ans > C[row*p+col])
                        {
                            min = C[row*p+col] ;
                            max = ans ;
                        }
                        else
                        {
                            min = ans ;
                            max = C[row*p+col] ;
                        }
                        err = (double) (max-min)/ (double) max ;

                        if ( ( min > (double) 0.0001 ) && ( err > (double) 0.01 ) )
                            success = 0 ;
                    }

                    if ( success == 0 )
                        strcpy( status, "Failed" ) ;
                    else
                        strcpy( status, "Passed" ) ;

                    printf( "{m=%d,n=%d,p=%d,numt=%d,b=%d,time=%g,status=%s},  ",
                              m, n, p, numt, b, (double) difftime(time2,time1), status ) ;
                    fflush( stdout ) ;
                }
             }
    }
    return 0;
}

