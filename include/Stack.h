#ifndef STACK_H
#define STACK_H

#include "Configs.h"
#include "Container.h"

class Stack : public TaskContainer<MAX_STACK_SIZE>
{
public:
    typedef Container::const_iterator Iterator;

    Stack();
    ~Stack();
    
    Iterator GetTask() const override;
    void PopTask() override;
};

#endif // STACK_H
