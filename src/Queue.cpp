#include "Queue.h"
#include <memory>
#include <iostream>
#include <format>

Queue::Queue()
    : _queueSize(-1), _filled(false), _taskArray(static_cast<Task *>(malloc(sizeof(Task) * MAX_QUEUE_SIZE)))
{
}

Queue::~Queue()
{
    _taskArray.~unique_ptr();
}

void Queue::addElement(Task *newTask)
{
    std::lock_guard<std::mutex> lock(_queueMutex);
    if (!_filled)
    {
        ++_queueSize;
        switch (newTask->type())
        {
        case Task::Print:
            std::construct_at(static_cast<PrintTask *>(_taskArray.get() + _queueSize), newTask->id, newTask->timeArrival, newTask->text);
            break;
        case Task::Added:
            std::construct_at(static_cast<AddTask *>(_taskArray.get() + _queueSize), newTask->id, newTask->timeArrival, newTask->text);
            break;
        case Task::Hashing:
            std::construct_at(static_cast<HashingTask *>(_taskArray.get() + _queueSize), newTask->id, newTask->timeArrival, newTask->text);
            break;
        default:
            break;
        }
        std::cout << "Добавлен элемент в queue с id: " << newTask->id << std::endl;
        if (_queueSize == MAX_QUEUE_SIZE - 1)
            _filled = true;
        showQueue();
    }
}

Task *Queue::getElement()
{
    std::lock_guard<std::mutex> lock(_queueMutex);
    return !isEmpty() ? _taskArray.get() : nullptr;
}

void Queue::updateQueue()
{
    std::lock_guard<std::mutex> lock(_queueMutex);
    if (!isEmpty())
    {
        Task *copy = reinterpret_cast<Task *>(malloc(sizeof(Task) * MAX_QUEUE_SIZE));
        for (int i = 1; i <= _queueSize; ++i)
        {
            auto task = _taskArray.get() + i;
            if (task->type() == Task::Print)
            {
                std::construct_at(static_cast<PrintTask *>(copy + i - 1), task->id, task->timeArrival, task->text);
            }
            else
            {
                if (task->type() == Task::Added)
                {
                    std::construct_at(static_cast<AddTask *>(copy + i - 1), task->id, task->timeArrival, task->text);
                }
                else
                {
                    std::construct_at(static_cast<HashingTask *>(task + i - 1), task->id, task->timeArrival, task->text);
                }
            }
        }
        _taskArray.reset(copy);
        --_queueSize;
        showQueue();
    }
}

void Queue::showQueue()
{
    std::cout << "Список очереди:\n";
    for (int i = 0; i <= _queueSize; ++i)
    {
        auto task = _taskArray.get() + i;
        std::cout << std::format("{} {} {} {}\n", std::to_string(task->id), std::to_string(task->type()),
                                 task->text, std::to_string(task->timeArrival));
    }
}
