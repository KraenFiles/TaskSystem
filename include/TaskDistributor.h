#ifndef TASKDISTRIBUTOR_H
#define TASKDISTRIBUTOR_H

#include "Task.h"
//#include <mutex>

class Queue;
class Stack;
class TaskVisitor;

class TaskDistributor
{
public:
    TaskDistributor(Queue *queue);
    ~TaskDistributor();

    void Exec();
    inline void Stop() { _stopDistributor = true; }

private:
    bool _stopDistributor = false;

    Queue *_queue;
    Stack *_stack;
    TaskVisitor *_visitor;

    //std::mutex _distMutex;
};

#endif // TASKDISTRIBUTOR_H
