#ifndef MASTER_HPP
#define MASTER_HPP

#include "WorkerJob.hpp"
#include "Exception.hpp"

class Master
{
    
public:
    
    enum StateType
    {
        NOT_STARTED,
        NOT_RUNNING,
        RUNNING,
        STOPPED,
        FINISHED
    };
    
    Matrix* grid;
    
public:
    
    Master() : state(NOT_STARTED)
    {
        grid = new Matrix;
    }
    
    void initWorkers();
    
    void run_workers(int iterations);
    
    void stop_workers();
    
    void shutdown();
    
    void gatherGrid();
    
    void change_state(StateType s);
    
    StateType getState();
    
    int getIterNum();
    
    Matrix* getGrid();
    
    void setNumWorkers(int workers_count);
    
    int getNumWorkers();
    
private:
    
    StateType state;
    
    unsigned int workersCount;
    
    bool* gridBuffer;
    
    int worker_arg[2];
    
    int iterNumber;
    
    
};

void Master::setNumWorkers(int workers_count)
{
    workersCount = workers_count;
}

int Master::getNumWorkers()
{
    return workersCount;
}

void Master::initWorkers()
{
    gridBuffer = new bool[grid->width * grid->height];
    worker_arg[0] = grid->width / workersCount;
    worker_arg[1] = grid->height;
    cout << worker_arg[0] << " " << worker_arg[2] << " " << workersCount << endl;
    int start_row = 0;
    
    for (int i = 1; i <= workersCount; ++i)
    {
        if (i == workersCount)
        {
            worker_arg[0] += grid->width % workersCount;
        }
        grid->write_to_buffer(gridBuffer, start_row, worker_arg[0]);
        
        MPI_Send(worker_arg, 2, MPI::INT, i, FIELD_INFO, MPI_COMM_WORLD);
        
        MPI_Send(gridBuffer, worker_arg[0] * grid->height, MPI::BOOL,
                 i, FIELD_INIT, MPI_COMM_WORLD);
        
        cout << "sended info\n";
        start_row += worker_arg[0];
    }
}


void Master::gatherGrid()
{
    MPI_Status status;
    bool* field_part_pointer = gridBuffer;
    bool some_message = 0;
    worker_arg[0] = grid->width / workersCount;
    
    for (int i = workersCount; i >= 1; --i)
    {
        if (i == workersCount)
        {
            worker_arg[0] += grid->width % workersCount;
        }
        
        MPI_Send(&some_message, 1, MPI::INT, i, FIELD_GATHER, MPI_COMM_WORLD);
        MPI_Recv(field_part_pointer, worker_arg[0] * grid->height, MPI::BOOL, i, FIELD_GATHER, MPI_COMM_WORLD, &status);
        field_part_pointer += worker_arg[0] * grid->height;
    }
    grid->init_from_buffer(gridBuffer, grid->width, grid->height);
}


int Master::getIterNum()
{
    return iterNumber;
}


Matrix* Master::getGrid()
{
    return grid;
}

void Master::run_workers(int iterations)
{
    for (int i = 1; i <= workersCount; ++i)
    {
        MPI_Send(&iterations, 1, MPI::INT, i, RUN, MPI_COMM_WORLD);
    }
}

void Master::change_state(StateType s)
{
    state = s;
}

Master::StateType Master::getState()
{
    return state;
}

void Master::stop_workers()
{
    MPI_Status status;
    bool some_message = 0;
    cout << "Master starts stopping workers\n";
    MPI_Send(&some_message, 1, MPI::INT, 1, STOP, MPI_COMM_WORLD);
    cout << "Master sent some info\n";
    int new_iter_number;
    int iterations_ready;
    cout << "But previous iterNumber " << iterNumber << endl;
    for (int i = 2; i <= workersCount; ++i)
    {
        MPI_Recv(&iterations_ready, 1, MPI::INT, i, ITERATION_GATHER, MPI_COMM_WORLD, &status);
        cout << "received from " << i << " " << iterations_ready << endl;
    }
    iterNumber = iterations_ready;
}

void Master::shutdown()
{
    int some_message = 0;
    for (int i = 1; i <= workersCount; ++i)
    {
        MPI_Send(&some_message, 1, MPI::INT, i, FINISH, MPI_COMM_WORLD);
    }
    state = FINISHED;
}

#endif