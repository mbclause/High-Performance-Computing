/*
File:
Description: This CUDA program uses a global function to compute the number of even values in a given NxN matrix, N being 16.
*/


#include <stdio.h>

#define N 16

#define SIZE N * N

#define BLOCKSIZE 4



/*
Function: isEven
Description: A device function that checks if a value is even or odd. Returns 1 or 0 respectively.
*/
__device__ int IsEven(int val)
{

        if (val % 2 == 0) return 1;

        return 0;

} // end "isEven"



/*
Function: compute
Description: A global function that keeps track of the number of even values in its matrix/array block by storing
1 or zero in d_out depending on if the respective element is even or not.
*/
__global__ void compute(int *d_in,int *d_out) {

        d_out[threadIdx.x] = 0;

        for (int i=0; i<SIZE/BLOCKSIZE;i++)
        {

                int val = d_in[i*BLOCKSIZE + threadIdx.x];

                d_out[threadIdx.x] += IsEven(val);

        }

} // end "compute"



/*
Function: outer_compute
Description: Host function which launches size/blocksize kernels and launches them.
It copies the resulting array from the gpu to the cpu, stored in h_out_array.
*/
__host__ void outer_compute (int *h_in_array, int *h_out_array)
{

        int *d_in_array, *d_out_array;

        cudaMalloc((void **) &d_in_array,SIZE*sizeof(int));

        cudaMalloc((void **) &d_out_array,SIZE*sizeof(int));

        cudaMemcpy(d_in_array, h_in_array,SIZE*sizeof(int),cudaMemcpyHostToDevice);

        compute<<<1, BLOCKSIZE, 0>>>(d_in_array, d_out_array);

        cudaMemcpy(h_out_array, d_out_array,SIZE*sizeof(int),cudaMemcpyDeviceToHost);

} // end "outer_compute"



/*
Function: main
*/
int main()
{

        int *in_array, *out_array;

        int sum = 0;

        in_array = (int *)malloc(SIZE * sizeof(int));

        out_array = (int *)malloc(SIZE * sizeof(int));

        // initialize matrix
        for(int i = 0; i < SIZE; i++)
                in_array[i] = i;

        printf("Matrix\n");

        // display the matrix
        for(int i = 0; i < N; i++)
        {
                for(int j = 0; j < N; j++)
                {
                        printf("%2d ", in_array[i * N + j]);
                }

                printf("\n");
        }

        outer_compute(in_array, out_array);

        // add up the total number of even values from the output array
        for (int i=0; i<SIZE; i++)
        {

                sum+=out_array[i];

        }

        printf ("\nNumber of even values = %d\n",sum);

} // end "main"