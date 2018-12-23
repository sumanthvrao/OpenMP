#include <stdio.h>
#include "matrix.h"

//OpenMP Code to parallelize the computation of C = alpha x A x B + beta x C
// Logic:
// pickup each b X b block and store it in a temp.
// Use block multiplication algorithm to multiply the two matrices
// and store output in C. Add the temp scaled by factor of beta to
// The newly computed C ( also scaled by factor of alpha).
// Block multiplication algo has the advantage of fitting in cache
// as big matrices are split into small chunks of size b for this purpose.
// OpenMP further parallelizes the code by allowing threads to execute first loops.

void MatMul( int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C )
{
	int i,j,k,ii,jj,kk;
	double* Ctemp = (double*)malloc(b*b* sizeof(double));

  #pragma omp parallel for private(i, j, k, ii, jj, kk) collapse(2)
 	for(i = 0;i < m;i += b)
    {
      for(j = 0;j < p;j += b)
      {
        for(ii = i;ii < i+b; ii++)
        {
          for(jj = j;jj < j+b;jj++)
          {
            Ctemp[(ii-i)*b + (jj-j)] = C[ii*p + jj];
            C[ii*p + jj] = 0;
          }
        }
        for(k = 0;k < n;k += b)
        {
          //block multiply of Block_A[i,k] * Block_B[k,j] -> Block_C[i,j]
          for(ii = i;ii < i+b;ii++)
          {
            for(jj = j;jj < j+b;jj++)
            {
              for(kk = k;kk < k+b;kk++)
              {
                C[ii*p+jj] += A[ii*n+kk] * B[kk*p+jj];
              }
            }
          }
        }
        for(ii=i;ii<i+b;ii++)
        {
          for(jj=j;jj<j+b;jj++)
          {
            C[ii*p+jj] = alpha * C[ii*p + jj] + beta * Ctemp[(ii-i)*b + (jj-j)];
          }
        }
      }
    }
}
