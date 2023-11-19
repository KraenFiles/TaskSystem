#include "Queue.h"

#include <exception>

Queue::Queue()
    : TaskContainer<MAX_QUEUE_SIZE>()
{
}

Queue::~Queue()
{
}

Queue::ConstIterator Queue::GetTask() const
{
    return _taskArray.begin();
}

Queue::ValueType Queue::PopTask()
{
    if(IsEmpty()) std::__throw_out_of_range("Queue is empty");
    ValueType result = _taskArray.at(0);
    UpdateQueue();
    return result;
}

void Queue::UpdateQueue()
{
    std::lock_guard<std::mutex> lock(_mutex);
    --_tasksCount;
    for (int i = 0; i < _tasksCount; ++i)
    {
        _taskArray.at(i) = _taskArray.at(i+1);
    }
}
