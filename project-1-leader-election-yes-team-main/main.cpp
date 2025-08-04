/*
File: main.cpp
Description: Uses MPI to find the second largest value and elect the process that has that value as the leader.
*/

#include <mpi.h>
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;



/*
Function: convert_id
Description: Generates a unique five digit ID for each process as described in the project prompt.
*/
int convert_id(const int rank_num)
{

    std::string nn;
    std::string d;
    std::string rr;

    int random_val = 10 + (rand() % 90); // generates random value between 10-99
    nn = std::to_string(random_val);     // convert to string
    d = std::to_string(random_val % 2);
    if (rank_num < 10)
        rr = std::to_string(0) + std::to_string(rank_num);
    else
        rr = std::to_string(rank_num);

    std::string new_id = nn + d + rr;
    return std::stoi(new_id);
} // end "convert_id"



/*
Function: main
*/
int main(int argc, char *argv[])
{
    int rank;

    int size;

    int Largest_IDs[2];

    int second_largest = 0;

    int ID = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::srand(std::time(0) + rank); // seed random number based on rank number

    // check that N is greater than 5
    if (size < 6)
    {
        cout << "N must be greater than 5\n";

        MPI_Finalize();

        exit(1);
    }

    Largest_IDs[0] = Largest_IDs[1] = 0;

    if (rank == 0)
    {
        // generate ID
        ID = convert_id(rank);

        // display ID
        cout << "Rank " << rank << " ID: " << ID << endl;

        Largest_IDs[0] = ID;

        // send ID to rank 1
        MPI_Send(Largest_IDs, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // receive the two largest IDs from the last process
        MPI_Recv(Largest_IDs, 2, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        second_largest = Largest_IDs[1];

        // if rank 0 has the second largest value, announce this
        if (ID == second_largest)
        {
            cout << "Process 0 has the second largest ID: " << ID << endl;
        }

        // send second largest ID to process 1
        MPI_Send(&second_largest, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    else if (rank == 1)
    {
        // generate ID
        ID = convert_id(rank);

        // display ID
        cout << "Rank " << rank << " ID: " << ID << endl;

        // receive process 0s ID in the first element of array
        MPI_Recv(Largest_IDs, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // if process 0s ID is larger than ID, store ID in second element of array
        if (Largest_IDs[0] >= ID)
            Largest_IDs[1] = ID;

        // if ID is larger than process 0s, store 0s in second element and ID in first element of array
        else
        {
            Largest_IDs[1] = Largest_IDs[0];

            Largest_IDs[0] = ID;
        }

        // send array to rank 2
        MPI_Send(Largest_IDs, 2, MPI_INT, 2, 0, MPI_COMM_WORLD);

        // receive second largest ID from rank 0
        MPI_Recv(&second_largest, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // if rank has the second largest value, announce this
        if (ID == second_largest)
        {
            cout << "Process " << rank << " has the second largest ID: " << ID << endl;
        }

        // send second largest ID to process 2
        MPI_Send(&second_largest, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }

    else
    {
        // generate ID
        ID = convert_id(rank);

        // display ID
        cout << "Rank " << rank << " ID: " << ID << endl;

        // receive two largest IDs from previous process
        MPI_Recv(Largest_IDs, 2, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // if ID is larger than the largest
        if (ID > Largest_IDs[0])
        {
            // largest ID is now second largest
            Largest_IDs[1] = Largest_IDs[0];

            // local ID is now largest
            Largest_IDs[0] = ID;
        }

        // if ID is smaller than the largest
        else if (ID <= Largest_IDs[0])
        {
            // if ID is larger than second largest
            if (ID > Largest_IDs[1])
                Largest_IDs[1] = ID;
        }

        // send two largest IDs to next process
        MPI_Send(Largest_IDs, 2, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

        // receive second largest ID from previous process
        MPI_Recv(&second_largest, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // if rank has the second largest value, announce this
        if (ID == second_largest)
        {
            cout << "Process " << rank << " has the second largest ID: " << ID << endl;
        }

        // if not last process
        if (rank < size)
        {
            // send second largest ID to next process
            MPI_Send(&second_largest, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
} // end "main"