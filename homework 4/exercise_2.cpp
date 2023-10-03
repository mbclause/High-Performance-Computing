/*In addition to what Exercise 1 asks, create another parallel construct that
adds 2*i to array[i].
*/

/*#include <iostream>
#include <omp.h>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    const int size = 64;

    int array[size];

    ofstream out;

    omp_set_num_threads(16);

    out.open("Exercise2_Output.txt");

    if (!out)
    {
        return -1;
    }

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        array[i] = 1;
    }

    out << "Array after first construct:\n";

    for (int i = 0; i < size; i++)
        out << array[i] << " ";

    out << endl;

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        array[i] += i * 2;
    }

    out << "Array after second construct:\n";

    for (int i = 0; i < size; i++)
        out << array[i] << " ";

    out << endl;

    out.close();

    return 0;
}*/
