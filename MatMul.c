#include <omp.h>
#include <stdio.h>


// void MatMul( int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C )
// {
//     int i, j, k, ii, jj, kk ;

//     #pragma omp parallel default(shared) private( j, ii, jj, kk )
//     #pragma omp for collapse(2)
//     for( i = 0 ; i < m ; i++ )
//       for( k = 0 ; k < p ; k++ )
//       {
//         #pragma omp atomic
//         C[i*p+k] *= beta ;
//         for( j = 0 ; j < n ; j++ )
//           #pragma omp atomic
//           C[i*p+k] += alpha * A[i*n+j]*B[j*p+k] ;
//       }
// }

//Routine should compute C = alpha x A x B + beta x C


void MatMul( int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C )
{
  //printf("Entered\n");
  int i,j,k,i1,j1;
  // here m = n = p therefore any of these can be used throughout. 
  //2 outer blocks here for iterating throughout the block
  #pragma omp for collapse(2)
  for(i=0;i<m;i++)
  {
    for(j=0;j<p;j++)
    {
      #pragma omp atomic
      C[i*p+j] *= beta;
    }
  }
  #pragma omp barrier


  for(i=0;i<m;i+=b) 
  {
    for(j=0;j<p;j+=b)
    {
      #pragma omp parallel for collapse(3) schedule(static,1000)//parallelizing the most computationallly intensive part
      for(k=0;k<m;k++)//These 3 inner blocks to multiply elements in that block
      {
        for(i1=i;i1<((i+b)>n?n:(i+b));i1++)
        {
          for(j1=j;j1<((j+b)>n?n:(j+b));j1++)
          {
            #pragma omp atomic
            C[k*p+i1] += alpha* A[k*n+j1]* B[j1*p+i1]; //tried using a temp and updating i tin the end. came out to be slower.
          }
        }
      }
    }
  }
  //printf("Exited\n");
}


