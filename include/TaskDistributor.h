#ifndef TASKDISTRIBUTOR_H
#define TASKDISTRIBUTOR_H

#include "Task.h"
#include <mutex>

class Queue;
class Stack;
template <typename T>
class Process;

class TaskDistributor
{
public:
    TaskDistributor(Queue *queue, Stack *stack, Process<PrintTask> *printProc, Process<AddTask> *addProc, Process<HashingTask> *hashProc);

    void exec();

    inline void stop() { _stopDistributor = true; }

private:
    void checkTask(Task *task, bool addInStack);
    template <typename T>
    void checkProcessor(Process<T> *processor, T *task, bool addInStack);

    bool _stopDistributor = false;

    Queue *_queue;
    Stack *_stack;

    Process<PrintTask> *_printProc;
    Process<AddTask> *_addProc;
    Process<HashingTask> *_hashingProc;

    std::mutex _distMutex;
};

#endif // TASKDISTRIBUTOR_H
