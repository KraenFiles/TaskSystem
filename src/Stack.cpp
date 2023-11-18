#include "Stack.h"

#include <format>
#include <iostream>
#include <memory>

Stack::Stack()
    : _stackSize(-1),
      _filled(false),
      _taskArray(static_cast<Task *>(malloc(sizeof(Task) * MAX_STACK_SIZE))) {}

Stack::~Stack() {}

void Stack::addElement(Task *newTask)
{
    std::lock_guard<std::mutex> lock(_stackMutex);
    if (!_filled)
    {
        ++_stackSize;
        switch (newTask->type())
        {
        case Task::Print:
            std::construct_at(static_cast<PrintTask *>(_taskArray.get() + _stackSize), newTask->id, newTask->timeArrival, newTask->text);
            break;
        case Task::Added:
            std::construct_at(static_cast<AddTask *>(_taskArray.get() + _stackSize), newTask->id, newTask->timeArrival, newTask->text);
            break;
        case Task::Hashing:
            std::construct_at(static_cast<HashingTask *>(_taskArray.get() + _stackSize), newTask->id, newTask->timeArrival, newTask->text);
            break;
        default:
            break;
        }
        std::cout << "Добавлен элемент в stack с id: " << newTask->id << std::endl;
        if (_stackSize == MAX_STACK_SIZE - 1)
            _filled = true;
        showStack();
    }
}

Task *Stack::getElement()
{
    std::lock_guard<std::mutex> lock(_stackMutex);
    return !isEmpty() ? _taskArray.get() + _stackSize : nullptr;
}

void Stack::updateStack()
{
    std::lock_guard<std::mutex> lock(_stackMutex);
    if (!isEmpty())
    {
        Task *copy =
            reinterpret_cast<Task *>(malloc(sizeof(Task) * MAX_STACK_SIZE));
        for (int i = 0; i < _stackSize; i++)
        {
            auto type = _taskArray.get() + i;
            if (type->type() == Task::Print)
            {
                std::construct_at(static_cast<PrintTask *>(copy + i), type->id,
                                  type->timeArrival, type->text);
            }
            else
            {
                if (type->type() == Task::Added)
                {
                    std::construct_at(static_cast<AddTask *>(copy + i), type->id,
                                      type->timeArrival, type->text);
                }
                else
                {
                    std::construct_at(static_cast<HashingTask *>(copy + i), type->id,
                                      type->timeArrival, type->text);
                }
            }
        }
        _taskArray.reset(copy);
        --_stackSize;
        showStack();
    }
}

void Stack::showStack()
{
    std::cout << "Список стека:\n";
    for (int i = 0; i <= _stackSize; ++i)
    {
        auto task = _taskArray.get() + i;
        std::cout << std::format("{} {} {} {}\n", std::to_string(task->id), std::to_string(task->type()),
                                 task->text, std::to_string(task->timeArrival));
    }
}
