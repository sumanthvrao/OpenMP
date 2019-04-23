# OpenMP
Optimized codes to achieve parallelism using OpenMP

[![OpenMP](https://img.shields.io/badge/OpenMP-3.0-red.svg)](https://www.openmp.org/)

Matrix Multiplication
-----
An openMP implementation of matrix multiplication using block algorithm.<br>
### Files:<br>
* **main.c** - Tests the speed of program by using matrices
of varying dimesions from 1024 X 1024 to 1536 X 1536 in steps of 256.
Each time it launches different threads from 1 till 4 in steps of 2.
* **block_multiply.c** - Uses block multiplication algorithm to multiply 
the two matrices and store output in matrix C. Block multiplication algo 
has the advantage of fitting in cache as big matrices are split into small
chunks of size b for this purpose.
* **MatMul_omp.c** - Implemets the block multiplication algorithm with OpenMP
further parallelizing the code by allowing threads to execute first loops interchangably.
* **matrix.h** - header files including required packages.
* **Makefile** - makefile to be run.

### Run program:
1. clone repository and `cd` into repository.
2. `cd Matrix Multiplication` 
3. run make - `make`
4. execute after compilation- `./main`

### Output:
```
{m=1024,n=1024,p=1024,numt=1,b=16,time=9,status=Passed},  {m=1024,n=1024,p=1024,numt=2,b=16,time=4,status=Passed},  {m=1024,n=1024,p=1024,numt=4,b=4,time=5,status=Passed},  {m=1024,n=1024,p=1024,numt=4,b=16,time=3,status=Passed},  {m=1024,n=1024,p=1024,numt=4,b=64,time=5,status=Passed},  {m=1280,n=1280,p=1280,numt=1,b=16,time=16,status=Passed},  {m=1280,n=1280,p=1280,numt=2,b=16,time=8,status=Passed},  {m=1280,n=1280,p=1280,numt=4,b=4,time=7,status=Passed},  {m=1280,n=1280,p=1280,numt=4,b=16,time=7,status=Passed},  {m=1280,n=1280,p=1280,numt=4,b=64,time=7,status=Passed},  {m=1536,n=1536,p=1536,numt=1,b=16,time=27,status=Passed},  {m=1536,n=1536,p=1536,numt=2,b=16,time=15,status=Passed},  {m=1536,n=1536,p=1536,numt=4,b=4,time=14,status=Passed},  {m=1536,n=1536,p=1536,numt=4,b=16,time=12,status=Passed},  {m=1536,n=1536,p=1536,numt=4,b=64,time=14,status=Passed}
```

The time increases with increase in thread but decreases with dimensional increase

Pascal Triangle
-----
An openMP implementation of pascal triangle using tasks.<br>
### Files:<br>
* **main.c** - Tests the speed of program by varying number of threads
(e.g. 1, 2, 4, 8, 16, 32) and different validations to ensure that tasks 
have been used properly.
* **FILLPT.c** - Uses tasks and their interdependencies to call `PTUpdateEntry`
function for the specific cell to be filled.
* **matrix.h** - header files including required packages.
* **Makefile** - makefile to be run.

### Run program:
1. clone repository and `cd` into repository.
2. `cd Pascal Triangle` 
3. run make - `make`
4. execute after compilation- `./main`

### Output:
```
numt=1, status=Passed, workload=[210],time=1
numt=2, status=Passed, workload=[210,0],time=1
numt=4, status=Passed, workload=[210,0,0,0],time=5
```

