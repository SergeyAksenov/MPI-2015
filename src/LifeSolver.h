#ifndef LIFESOLVER_H
#define LIFESOLVER_H

#include <string>
#include <map>
#include <iostream>
#include "Command.hpp"
#include "Matrix.hpp"

using namespace std;

class LifeSolver
{
    
public:
    
    
    std::map<std::string, Command*> commands;
    
    
    void run() {
        
        while (true) {
            cout << "$ ";
            
            string cmd;
            
            cin >> cmd;
            if (commands[cmd]) {
                commands[cmd]->handle(life_field);
            }
            else {
                cout << "Wrong command\n";
            }
        }
        
    }
    
    
private:
    
    
    Field* life_field;
    
    
};

#endif
