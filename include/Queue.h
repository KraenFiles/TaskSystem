#ifndef QUEUE_H
#define QUEUE_H

#include "Configs.h"
#include "Container.h"

class Queue : public TaskContainer<MAX_QUEUE_SIZE>
{
public:
    typedef Container::const_iterator Iterator;

    Queue();
    ~Queue();
    
    Iterator GetTask() const override;
    void PopTask() override;
};

#endif // QUEUE_H
