/*
Write a CUDA program to initialize an array array[] of size 64 to all 2s
in parallel.
*/



#include <iostream>

#include <cuda.h>

using namespace std;



// Function to initialize the array using the GPU
__global__ void Init_Array(int *array, const int size)
{
        int i = threadIdx.x;

        if(i < size)
                array[i] = 2;
}







int main()
{
	// the size of the array, and thus the number of GPU threads
        const int size = 64;

        int  *deviceArray;

        int  cpuArray[size];

	// allocate memory for the device array
        cudaMalloc((void **)&deviceArray, size * sizeof(int));

	// set the number of threads
        dim3   blockSize(size);

        Init_Array<<<1, blockSize>>>(deviceArray, size);
	
	// copy the array initialized on the GPU to the cpu array
        cudaMemcpy(cpuArray, deviceArray, size * sizeof(int), cudaMemcpyDeviceToHost);

	// display the array contents
        for(int i = 0; i < size; i++)
                cout << cpuArray[i] << " ";

        cout << endl;

        cudaFree(deviceArray);

        return 0;

}
