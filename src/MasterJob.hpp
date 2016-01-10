#ifndef MasterJob_H
#define MasterJob_H

//#include "LifeSolver.h"
#include "Matrix.hpp"
#include "Master.hpp"
#include "Command.hpp"

using namespace std;

class Job
{
    
public:
    
    
    std::map<std::string, Command*> commands;
    
    
    void run() {
        
        while (true) {
            cout << "> ";
            
            string cmd;
            
            cin >> cmd;
            if (commands[cmd]) {
                commands[cmd]->handle(life_field);
            }
            else {
                cout << "Unknown command\n";
            }
        }
        
    }
    
    
private:
    
    
    Matrix* life_field;
    
    
};





class MasterJob: public Job
{
    
    Master* master;
    
public:
    
    MasterJob();
    
    ~MasterJob();
    
    void run(int size);
    
};

MasterJob::MasterJob()
{
    commands["START"] = new StartCommand();
    
    commands["STATUS"] = new StatusCommand();
    
    commands["RUN"] = new RunCommand();
    
    commands["STOP"] = new StopCommand();
    
    commands["EXIT"] = new ExitCommand();
    
}

void MasterJob::run(int size)
{
    master = new Master();
    master->set_workers_count(size - 1);
    while (true)
    {
        cout << "> ";
        string cmd;
        cin >> cmd;
        if (commands[cmd])
        {
            commands[cmd]->handle(master);
        }
        else
        {
            cout << "Unknown command\n";
        }
    }
}

MasterJob::~MasterJob()
{
    assert(master->getState() == Master::NOT_STARTED || master->getState() == Master::FINISHED);
}

#endif
