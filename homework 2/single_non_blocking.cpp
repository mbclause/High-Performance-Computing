// File: single_non_blocking.cpp
// Description: This program sends a single communication using non-blocking.

#include <mpi.h>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
    int rank;

    int size;

    int count;

    double start;

    double end;

    MPI_Request ireq;

    MPI_Status istatus;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // get the start time for the program
    start = MPI_Wtime();

    if (rank == 0)
    {
        // pass the string as a char pointer of size .size()
        string name = "Michael Clausen";

        MPI_Isend(name.c_str(), name.size(), MPI_CHAR, 1, 0, MPI_COMM_WORLD, &ireq);

        cout << "Process 0 sent string " << name << " to process 1.\n";

        // wait until the send is completed
        MPI_Wait(&ireq, &istatus);
    }

    else if (rank == 1)
    {
        // get the size of the communication buffer
        MPI_Probe(0, 0, MPI_COMM_WORLD, &istatus);

        MPI_Get_count(&istatus, MPI_CHAR, &count);

        // use count to allocate the receiving char buffer
        char* nameRecvd = (char*)malloc(sizeof(char) * count);

        MPI_Irecv(nameRecvd, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &ireq);

        string newName(nameRecvd, count);

        cout << "Process 1 received string " << newName << " from process 0.\n";

        free(nameRecvd);

        // wait until the recv is completed
        MPI_Wait(&ireq, &istatus);

        // since this is the final process, get the stop time of the program
        end = MPI_Wtime();
    }

    MPI_Finalize();

    // only display the time for the last process
    if (rank == 1)
       cout << "Execution time for 1 communication using non-blocking = " << end - start << endl;
}