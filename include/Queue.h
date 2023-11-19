#ifndef QUEUE_H
#define QUEUE_H

#include "Configs.h"
#include "Container.h"

class Queue : public TaskContainer<MAX_QUEUE_SIZE>
{
public:
    Queue();
    ~Queue();
    
    ConstIterator GetTask() const override;
    ValueType PopTask() override;

    void UpdateQueue();
};

#endif // QUEUE_H
