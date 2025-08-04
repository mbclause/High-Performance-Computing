// Project 2 [Parallelized Shear Sort]
// Michael Clausen, Jayson Doty, Youssef Hegazy
// Professor Doina Bein
// CPSC 479
// File: Project2.cu
// 
// Description: Program to sort an n x n matrix using Parallel Shear Sort. It is
// implimented in CUDA. The user inputs the value of n and the n x n matrix is 
// filled with random values ranging from -100 to 900. This
// matrix is then displayed. The sorting is then
// accomplished in two stages. In the Odd Stage, each odd row is sorted
// from left to right and each even row is sorted from right to left.
// In the Even Stage, each column is sorted from top to bottom.
// The sorting of the rows and columns is done using Bubble Sort.
// The resulting matrix is sorted in a "snake like" pattern and 
// then displayed.

#include <stdio.h>
#include <iostream>
#include <cuda.h>
#include <iomanip>

using namespace std;



/*
Function: ShearSortRow
Description: Kernel function to sort each row of the matrix using Bubble Sort.
Odd rows are sorted from left to right and odd rows are sorted from right to left.
*/
__global__ void ShearSortRow(int* matrix, int n) 
{
    // calculate thread ID
    int threadID = blockIdx.x * blockDim.x + threadIdx.x;

    // check that the thread ID is in bounds
    if (threadID < n) 
    {
        // loop over the matrix rows
        for (int i = 0; i < n; i++) 
        {
            // loop over the matrix columns
            for (int j = 0; j < n - 1; j++) 
            {
                // Calculate the index in the matrix based on the threadID and column index
                int index = threadID * n + j;

                // odd rows swap so that they are sorted left to right
                // even rows swap so that they are sorted right to left
                if ((threadID % 2 == 0 && matrix[index] > matrix[index + 1]) ||
                    (threadID % 2 == 1 && matrix[index] < matrix[index + 1])) 
                {
                    // Swap
                    int temp = matrix[index];
                    matrix[index] = matrix[index + 1];
                    matrix[index + 1] = temp;
                }
            }
        }
    }
} // end "ShearSortRow"



/*
Function: ShearSortColumn
Description: Kernel function to sort each column of the matrix using Bubble Sort.
Columns are sorted normally, from top to bottom.
*/
__global__ void ShearSortColumn(int* matrix, int n) 
{
    // calculate thread ID
    int threadID = blockIdx.x * blockDim.x + threadIdx.x;

    // check that the thread ID is in bounds
    if (threadID < n) 
    {
        // loop through matrix rows
        for (int i = 0; i < n; i++) 
        {
            // loop through matrix columns
            for (int j = 0; j < n - 1; j++) 
            {
                // Calculate the index in the matrix based on the column index and threadID
                int index = j * n + threadID;

                // compare and swap
                if (matrix[index] > matrix[index + n]) 
                {
                    // Swap
                    int temp = matrix[index];
                    matrix[index] = matrix[index + n];
                    matrix[index + n] = temp;
                }
            }
        }
    }
} // end "ShearSortColumn"



/*
Function: main
*/
int main() 
{
    int N = 0;

    // get value of n from the user
    cout << "Enter an integer value for n greater than 0: ";

    cin >> N;

    // check that n is positive
    while(N < 1)
    {
        cout << "n must be greater than 0. Re-enter value: ";

        cin >> N;
    }

    int ha[N][N], *dm;

    // Initialize the matrix with random values, and print.
    std::cout<<"Matrix before sorting: "<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            ha[i][j] = (rand() % 1000) - 100;
            std::cout<<setw(5)<<ha[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"------------------------------------------------"<<std::endl;

    // allocate matrix on the GPU and copy over the matrix initialized on the CPU
    cudaMalloc(&dm, N * N * sizeof(int));
    cudaMemcpy(dm, ha, N * N * sizeof(int), cudaMemcpyHostToDevice);
    
    // kernel dimensions: n threads per block, and 1 block per grid
    dim3 threadsPerBlock(N);
    dim3 numBlocks(1);

    // sort rows in odd stage and columns in even stage log(n) times
    // synchronizing the device after each stage
    for (int i = 0; i < log2(N) + 1; i++) 
    {
        ShearSortRow<<<numBlocks, threadsPerBlock>>>(dm, N);
        cudaDeviceSynchronize();
        ShearSortColumn<<<numBlocks, threadsPerBlock>>>(dm, N);
        cudaDeviceSynchronize();
    }
    
    // Copy the matrix back to the host
    cudaMemcpy(ha, dm, N * N * sizeof(int), cudaMemcpyDeviceToHost);

    // Free the memory on the device
    cudaFree(dm);

    // Print the sorted matrix
    std::cout<<"Matrix After sorting: "<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            std::cout<<setw(5)<<ha[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"------------------------------------------------"<<std::endl;
    return 0;
} // end "main"
