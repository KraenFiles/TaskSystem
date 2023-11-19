#ifndef CONTAINER_H
#define CONTAINER_H

#include <variant>
#include <array>
#include <mutex>
#include <sstream>
#include <format>

#include "Task.h"

template <size_t containerSize>
class TaskContainer
{
public:
    typedef std::variant<PrintTask, CalculateTask, HashingTask> ValueType;
    typedef ValueType &Reference;
    typedef ValueType *Iterator;
    typedef const ValueType *ConstIterator;

    inline TaskContainer()
        : _tasksCount(0), _filled(false), _taskArray()
    {
    }
    virtual ~TaskContainer() = default;

    void PushTask(Task *newTask);
    virtual ConstIterator GetTask() const = 0;
    virtual ValueType PopTask() = 0;
    void ShowAllTasks();

    inline size_t Size() const { return _tasksCount; }
    inline bool IsFilled() const { return _filled; }

    inline bool IsEmpty() const { return _tasksCount == 0; }

protected:
    std::mutex _mutex;

    size_t _tasksCount;
    bool _filled;

    std::array<ValueType, containerSize> _taskArray;
};

template <size_t containerSize>
void TaskContainer<containerSize>::PushTask(Task *newTask)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if(_filled) std::__throw_overflow_error("Container is overflow");
    switch (newTask->type())
    {
    case Task::Print:
        _taskArray.at(_tasksCount) = PrintTask(newTask->id, newTask->_text);
        break;
    case Task::Calculate:
        _taskArray.at(_tasksCount) = CalculateTask(newTask->id, newTask->_text);
        break;
    case Task::Hashing:
        _taskArray.at(_tasksCount) = HashingTask(newTask->id, newTask->_text);
        break;
    default:
        std::__throw_invalid_argument("NewTask doesn't have task type");
        break;
    }
    ++_tasksCount;
    if(_tasksCount == containerSize) _filled = true;
}

template<size_t containerSize>
void TaskContainer<containerSize>::ShowAllTasks()
{
    if(IsEmpty()) return;
        auto setIndent = [](const std::string &str, int indent) -> std::stringstream
        { return std::stringstream << std::setw(indent) << str; }

        for (int i = 0; i < _tasksCount; ++i)
        {
            auto value = _taskArray.at(i);
            // clang-format off
            std::cout << std::format(
                "|{}|{}|{}|\n", 
                setIndent(std::to_string(value.id), 8).view(),
                setIndent(std::to_string(value.type()), 10).view(),
                setIndent(value.text, 25).view() 
            );
            // clang-format on
        }
}

#endif // CONTAINER_H


