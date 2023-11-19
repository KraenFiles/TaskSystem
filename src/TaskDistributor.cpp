#include "TaskDistributor.h"

#include "Queue.h"
#include "Stack.h"
#include "Processor.h"

#include <thread>
#include <iostream>

TaskDistributor::TaskDistributor(Queue *queue, Stack *stack, Process *printProc, Process *addProc, Process *hashProc)
    : _queue(queue), _stack(stack), _printProc(printProc), _addProc(addProc), _hashingProc(hashProc)
{
}

void TaskDistributor::exec()
{
    while (!_stopDistributor)
    {
        if (!_stack->isEmpty())
        {
            Task *task = _stack->getElement();
            checkTask(task, false);
        }

        if (!_queue->isEmpty())
        {
            Task *task = _queue->getElement();
            checkTask(task, true);
        }
    }
}

void TaskDistributor::checkTask(Task *task, bool addInStack)
{

    switch (task->type())
    {
    case Task::Print:
    {
        PrintTask *printTask = static_cast<PrintTask *>(task);
        checkProcessor(_printProc, printTask, addInStack);
        break;
    }
    case Task::Added:
    {
        AddTask *addTask = static_cast<AddTask *>(task);
        checkProcessor(_addProc, addTask, addInStack);
        break;
    }
    case Task::Hashing:
    {
        HashingTask *hashingTask = static_cast<HashingTask *>(task);
        checkProcessor(_hashingProc, hashingTask, addInStack);
        break;
    }

    default:
        break;
    }
}

template <typename T>
void TaskDistributor::checkProcessor(Process<T> *processor, T *task, bool addInStack)
{
    if (!processor->isBuzy())
    {
        processor->setTask(task);
        if (addInStack)
            _queue->updateQueue();
        else
            _stack->updateStack();
    }
    else if (addInStack)
    {
        if (!_stack->isFilled())
        {
            _stack->addElement(task);
            _queue->updateQueue();
        }
        else
        {
            std::clog << "Стек переполнен!";
        }
    }
}
