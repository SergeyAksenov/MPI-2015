#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <utility>
#include <cassert>
#include <mpi.h>
#include "Master.hpp"
//#include "Command.hpp"

using namespace std;


struct Command
{
    virtual void handle(void* arg) = 0;
    
    virtual ~Command() {}
};


struct StartCommand : public Command
{
    
    void handle(void* arg)
    {
        cout << "start command\n";
        Master* master = (Master*)arg;
        std::string field_info;
        
        cin >> field_info;
        
        try
        {
            int w = stoi(field_info), h;
            cin >> h;
            master->life_field->init_random(w, h);
            cout << "init random ended\n";
        }
        catch(...)
        {
            cerr << "init from file\n";
            master->life_field->init_from_file(field_info);
        }
        cout << "Master starts init workers\n";
        master->init_workers();
        cout << "Master ends init workers\n";
        master->change_state(Master::NOT_RUNNING);
    }
    
};



struct StatusCommand : public Command
{
    
    void handle(void* arg)
    {
        Master* master = (Master*)arg;
        if (master->get_state() == Master::NOT_STARTED)
        {
            cout << "The system has not yet started.";
            return;
        }
        if (master->get_state() == Master::RUNNING)
        {
            cout << "The system is still running. Try again.";
            return;
        }
        master->gather_field();
        cout << "Iteration number " << master->get_iter_number() << endl;
        master->get_field()->print_world();
    }
    
};



struct RunCommand : public Command
{
    void handle(void* arg)
    {
        Master* master = (Master*)arg;
        int iteration_count;
        cin >> iteration_count;
        master->run_workers(iteration_count);
        master->change_state(Master::RUNNING);
    }
};



struct StopCommand : public Command
{
    
    void handle(void* arg)
    {
        Master* master = (Master*)arg;
        if (master->get_state() == Master::NOT_STARTED)
        {
            cout << "The system has not yet started.";
            return;
        }
        master->stop_workers();
        master->change_state(Master::NOT_RUNNING);
    }
    
};



struct ExitCommand : public Command
{
    
    void handle(void* arg)
    {
        Master* master = (Master*)arg;
        master->shutdown();
        MPI_Finalize();
        exit(EXIT_SUCCESS);
    }
    
};

#endif