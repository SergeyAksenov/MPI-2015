#include <iostream>
#include <string>
#include "mpi.h"
#include "MasterJob.hpp"

#define mymessage 99

using namespace std;

int main(int argc, char** argv)
{
    MPI_Status status;
    MPI_Init(&argc, &argv);
    int id;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    /*if (size < 2)
    {
        throw "Very few workers are available.";
    }*/
    
    if (id == 0)
    {
        MasterJob msj;// = MasterJob();
        msj.run(size);
    }
    else
    {
        WorkerJob wrj;// = Worker();
        wrj(id, size);
    }
    
    MPI_Finalize();
    return 0;
}








