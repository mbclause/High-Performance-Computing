/*
Write an MPI program in which N processes communicate like in a bidirectional ring: 
each process of rank k sends its value  to both neighbors (to the rank (k-1) %N and to the rank (k+1)%N),
receive the values from both neighbors and displays its rank and the two received values.
*/

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
	int size = 0;

	int rank = 0;

	int prev_token = 0;

	int next_token = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// CLOCKWISE
	// non zero processes must receive values first
	if (rank != 0)
	{
		// receive next_token from (rank - 1) % size, clockwise
		MPI_Recv(&next_token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		cout << "Process " << rank << " received token " << next_token << " from process " << (rank - 1) % size << endl;
	}

	// first process sets values
	else
	{

		next_token = 231;
	}

	// send next_token to (rank + 1) % size, clockwise
	MPI_Send(&next_token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

	// first process can now receive the values
	if (rank == 0)
	{
		// receive next_token from (rank - 1) % size, clockwise
		MPI_Recv(&next_token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		cout << "Process " << rank << " received token " << next_token << " from process " << size - 1 << endl;
	}




	//COUNTER CLOCKWISE
	// non zero processes must receive values first
	if (rank != 0)
	{
		// receive prev_token from (rank + 1) % size, counter clockwise
		MPI_Recv(&prev_token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		cout << "Process " << rank << " received token " << prev_token << " from process " << (rank + 1) % size << endl;

		// send prev_token to (rank - 1) % size, counter clockwise
		MPI_Send(&prev_token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD);
	}

	// first process sets values
	else
	{
		prev_token = -10;

		MPI_Send(&prev_token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD);

		// receive prev_token from (rank + 1) % size, counter clockwise
		MPI_Recv(&prev_token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		cout << "Process " << rank << " received token " << prev_token << " from process " << (rank + 1) % size << endl;
	}

	MPI_Finalize();
}

