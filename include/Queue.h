#ifndef QUEUE_H
#define QUEUE_H

#include "Task.h"
#include <mutex>
#include <memory>

class Queue
{
public:
    Queue();
    ~Queue();

    void addElement(Task *newTask);
    Task *getElement();

    inline size_t size() const { return _queueSize; }
    inline bool isFilled() const { return _filled; }

    inline bool isEmpty() const { return _queueSize == -1; }

    void updateQueue();

    void showQueue();

private:
    int8_t _queueSize;
    const size_t MAX_QUEUE_SIZE = 16;
    bool _filled;

    std::unique_ptr<Task> _taskArray;

    std::mutex _queueMutex;
};

#endif // QUEUE_H
