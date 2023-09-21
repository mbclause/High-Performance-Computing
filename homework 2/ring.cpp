/* File: ring.cpp
 Description: This program uses a ring topology to pass a single integer to all processes 
 sequentially until it arrives back at the first process.*/

#include <mpi.h>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
    int rank;

    int size;

    int count;

    int token;

    double start;

    double end;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // get the start time for the program
    start = MPI_Wtime();

    // the non-zero processes must receive the token before sending it
    if (rank != 0) 
    {
        MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received token %d from process %d\n", rank, token, (rank - 1) % size);
    }
    
    else 
    {
        // Set the token's value if you are process 0
        token = 23;
    }

    // send the token to the next process
    MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

    // Now process 0 can receive from the last process.
    if (rank == 0) 
    {
        MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received token %d from process %d\n", rank, token, size - 1);

        // since this is the last process, get the stop time for the program
        end = MPI_Wtime();
    }

    MPI_Finalize();

    // only the final process displays the execution time
    if (rank == 0)
        cout << "Execution time for ring topology with " << size << " nodes = " << end - start << endl;
}

