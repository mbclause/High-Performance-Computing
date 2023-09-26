#include <mpi.h>
#include <iostream>
#include <iomanip>
#include "hw3.h"

using namespace std;

int main(int argc, char* argv[])
{
    int rank;

    int size;

    int charge_time = 0;

    int hours = 0;

    int min = 0;

    int total_time = 0;

    int total_min = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    charge_time = (rank * 15) + 5;

    MPI_Scan(&charge_time, &total_time, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    min = total_time - charge_time;

    total_min = min;

    FormatTime(hours, min);

    cout << "Rank " << rank << " will start charging after " << setw(5) << total_min << " minutes (" << hours << " hrs, " << setw(2) <<
        min << " min) and will be done after " << setw(5) << charge_time << " minutes\n";

    MPI_Finalize();

    return 0;
}