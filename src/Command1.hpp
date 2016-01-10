#ifndef COMMAND_HPP
#define COMMAND_HPP

struct Handler
{
    virtual void handle(void* arg) = 0;
    
    virtual ~Handler() {}
};

#endif
