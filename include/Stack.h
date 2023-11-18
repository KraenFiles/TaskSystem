#ifndef STACK_H
#define STACK_H

#include "Task.h"
#include <memory>
#include <mutex>

class Stack
{
public:
    Stack();
    ~Stack();

    void addElement(Task *newTask);
    Task *getElement();

    inline size_t size() const { return _stackSize; }
    inline bool isFilled() const { return _filled; }

    inline bool isEmpty() const { return _stackSize == -1; }

    void updateStack();

    void showStack();

private:
    int8_t _stackSize;
    const size_t MAX_STACK_SIZE = 16;
    bool _filled;

    std::unique_ptr<Task> _taskArray;

    std::mutex _stackMutex;
};

#endif // STACK_H
