#ifndef STACK_H
#define STACK_H

#include "Configs.h"
#include "Container.h"

class Stack : public TaskContainer<MAX_STACK_SIZE>
{
public:
    Stack();
    ~Stack();
    
    ConstIterator GetTask() const override;
    ValueType PopTask() override;
};

#endif // STACK_H
