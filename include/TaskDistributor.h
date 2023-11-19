#ifndef TASKDISTRIBUTOR_H
#define TASKDISTRIBUTOR_H

#include "Task.h"
#include <mutex>

class Queue;
class Stack;
class Processor;

class TaskDistributor
{
public:
    TaskDistributor(Queue *queue, Stack *stack, Processor *printProc, Processor *addProc, Processor *hashProc);

    void exec();
    inline void stop() { _stopDistributor = true; }

private:
    void checkTask(Task *task, bool addInStack);
    void checkProcessor(Processor *processor, Task *task, bool addInStack);

    bool _stopDistributor = false;

    Queue *_queue;
    Stack *_stack;

    Processor *_printProc;
    Processor *_addProc;
    Processor *_hashingProc;

    std::mutex _distMutex;
};

#endif // TASKDISTRIBUTOR_H
