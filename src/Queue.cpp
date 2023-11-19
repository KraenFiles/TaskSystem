#include "Queue.h"

#include <exception>

Queue::Queue()
    : TaskContainer<MAX_QUEUE_SIZE>()
{
}

Queue::~Queue()
{
}

Queue::Iterator Queue::GetTask() const
{
    return _taskArray.begin();
}

void Queue::PopTask()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if(IsEmpty()) std::__throw_out_of_range("Queue is empty");
    _taskArray.erase(_taskArray.begin());
}
