/*Write either a single program or separate C/C++/Python programs that use(s) MPI blocking and
non-blocking commands MPI_Send, MPI_Rcvd, MPI_Isend and MPI_Ircvd to exchange one string value
between process with rank 0 and process with rank 1. The string value should be either your name or your group name.
The program(s) needs to calculate and display the communication time (using MPI_Wtime) for each of the four communications below.
Also, complete the table below as well and submit it:*/

// single transmission, blocking

/*#include <mpi.h>
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

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);

    start = MPI_Wtime();

    if (rank == 0)
    {
        string name = "Michael Clausen";

        MPI_Send(name.c_str(), name.size(), MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        cout << "Process 0 sent string " << name << " to process 1.\n";

        MPI_Probe(1, 0, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_CHAR, &count);

        char* nameRecvd = (char*)malloc(sizeof(char) * count);

        MPI_Recv(nameRecvd, count, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        string newName(nameRecvd, count);

        cout << "Process 0 received string " << newName << " from process 1.\n";

        free(nameRecvd);
    }

    else if (rank == 1)
    {
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_CHAR, &count);

        char* nameRecvd = (char*)malloc(sizeof(char) * count);

        MPI_Recv(nameRecvd, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        string newName(nameRecvd, count);

        cout << "Process 1 received string " << newName << " from process 0.\n";

        MPI_Send(newName.c_str(), newName.size(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);

        cout << "Process 1 sent string " << newName << " to process 0.\n";

        free(nameRecvd);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    end = MPI_Wtime();

    MPI_Finalize();

    if (rank == 0)
        cout << "Execution time for two communications using blocking = " << end - start << endl;
}*/
