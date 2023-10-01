Programmer: Michael Clausen

Description: This program uses MPI_Scan to schedule EVs for charging. Each rank's charge time is (rank * 15) + 5. This is added to the running total using MPI_Scan and the results are displayed.

Usage: mpirun -n [NUM] ./a.out

