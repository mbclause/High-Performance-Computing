/*
File: exercise_2.cu
Description: This CUDA program uses a global function to compute the square of a given NxN matrix, N being 16.
For example, if the matrix given is A with 16x16 elements, the host function will compute the matrix AxA.
*/

#include <stdio.h>
#include <cuda.h>

using namespace std;


#define N 16



/*
Function: InitMatrix
Description: A global function which initializes an unsigned matrix.
*/
__global__ void InitMatrix(unsigned *matrix)
{

        unsigned id = blockIdx.x * blockDim.x + threadIdx.x;

        matrix[id] = id;

} // end "InitMatrix"



/*
Function: square
Description: Takes an NxN matrix A and computes its square AxA.
*/
__global__ void square ( unsigned *matrix, unsigned *result, unsigned matrixsize)
{

        unsigned id = blockIdx.x * blockDim.x + threadIdx.x;

        unsigned ii = id / matrixsize;

        unsigned jj = id % matrixsize;

        for (unsigned kk = 0; kk < matrixsize; ++kk)
        {

                result[ii * matrixsize + jj] += matrix[ii * matrixsize + kk] * matrix[kk * matrixsize + jj];
        }

} // end "square"



/*
main
*/
int main()
{

        unsigned *matrix, *hmatrix, *resultMatrix;

        int matrixSize = N;

        cudaMalloc(&matrix, N * N * sizeof(unsigned));

        cudaMalloc(&resultMatrix, N * N * sizeof(unsigned));

        hmatrix = (unsigned *)malloc(N * N * sizeof(unsigned));

        InitMatrix<<<N, N>>>(matrix);

        cudaMemcpy(hmatrix, matrix, N * N * sizeof(unsigned), cudaMemcpyDeviceToHost);

        printf("Original Matrix\n");

        // display the original matrix
        for (unsigned ii = 0; ii < N; ++ii)
        {

                for (unsigned jj = 0; jj < N; ++jj)
                {

                        printf("%2d ", hmatrix[ii * N + jj]);

                }

                printf("\n");

        }

        square<<<N, N>>>(matrix, resultMatrix, matrixSize);

        cudaMemcpy(hmatrix, resultMatrix, N * N * sizeof(unsigned), cudaMemcpyDeviceToHost);

        printf("\nSquared Matrix\n");

        // display the squared matrix
        for (unsigned ii = 0; ii < N; ++ii)
        {

                for (unsigned jj = 0; jj < N; ++jj)
                {

                        printf("%2d ", hmatrix[ii * N + jj]);

                }

                printf("\n");

        }

        return 0;

} // end "main"