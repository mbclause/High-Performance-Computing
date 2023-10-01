/*
File: main.cpp
Description: Contains the majority of the program besides the time formatting function.
*/

#include <mpi.h>
#include <iostream>
#include <iomanip>
#include "HW3.h"

using namespace std;

int main(int argc, char* argv[])
{
    int rank;

    int size;

    int charge_time = 0;

    int hours = 0;

    int min = 0;

    int total_time = 0;

    int wait_time = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate a unique charge time for each rank.
    charge_time = (rank * 15) + 5;

    // Add the charge time to the total amount of charge time for all processes up to this point.
    MPI_Scan(&charge_time, &total_time, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Wait time will be the total time minus this rank's charge time.
    min = total_time - charge_time;

    wait_time = min;

    // Change to time to hours and minutes
    FormatTime(hours, min);

    cout << "Rank " << rank << " will start charging after " << setw(5) << wait_time << " minutes (" << hours << " hrs, " << setw(2) <<
        min << " min) and will be done after " << setw(5) << charge_time << " minutes\n";

    MPI_Finalize();

    return 0;
}