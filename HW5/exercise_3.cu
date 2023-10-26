/*
Create another kernel that adds i to array[i] and do what Problem 1 and Problem 2 ask.
*/



#include <iostream>

#include <cuda.h>

using namespace std;



// initialize the array using the GPU
__global__ void Init_Array(int *array, const int size)
{
        int i = threadIdx.x;

        if(i < size)
                array[i] = 2;
}




// add index to all array values using the GPU
__global__  void  Add_Array(int  *array, const int size)
{

        int i = threadIdx.x;

        if(i < size)
                array[i] += i;

}




int main()
{
	// size of the array and the number of threads
        const int size = 1024;

        int  *deviceArray;

        int  cpuArray[size];

	// allocate memory on the GPU for the array
        cudaMalloc((void **)&deviceArray, size * sizeof(int));

        dim3   blockSize(size);

	// initialize array on GPU
        Init_Array<<<1, blockSize>>>(deviceArray, size);

	// add index to array on GPU
        Add_Array<<<1, blockSize>>>(deviceArray, size);

	// copy array from the GPU to CPU
        cudaMemcpy(cpuArray, deviceArray, size * sizeof(int), cudaMemcpyDeviceToHost);

	// display array
        for(int i = 0; i < size; i++)
                cout << cpuArray[i] << " ";

        cout << endl;

        cudaFree(deviceArray);

        return 0;

}