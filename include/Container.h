#ifndef CONTAINER_H
#define CONTAINER_H

#include <variant>
#include <vector>
#include <mutex>
#include <sstream>
#include <format>
#include <iostream>
#include <iomanip>

#include "Task.h"

template <size_t containerSize>
class TaskContainer
{
public:
    typedef std::variant<PrintTask, CalculateTask, HashingTask> ValueType;
    typedef ValueType &Reference;
    typedef std::vector<ValueType> Container;

    inline TaskContainer()
        : _filled(false), _taskArray()
    {
        _taskArray.reserve(containerSize);
    }
    virtual ~TaskContainer() = default;

    void PushTask(const Reference newTask);
    void PushTask(Task *newTask);
    virtual Container::const_iterator GetTask() const = 0;
    virtual void PopTask() = 0;
    void ShowAllTasks();

    // inline size_t Size() const { return _taskArray.size(); }
    inline bool IsFilled() const { return _filled; }

    inline bool IsEmpty() const { return _taskArray.empty(); }

protected:
    std::mutex _mutex;

    // size_t _tasksCount;
    bool _filled;

    Container _taskArray;
};

template <size_t containerSize>
void TaskContainer<containerSize>::PushTask(const Reference newTask)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_filled)
        std::__throw_overflow_error("Container is overflow");
    _taskArray.push_back(newTask);
    if (_taskArray.size() == containerSize)
        _filled = true;
}

template <size_t containerSize>
void TaskContainer<containerSize>::PushTask(Task *newTask)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_filled)
        std::__throw_overflow_error("Container is overflow");
    switch (newTask->type())
    {
    case Task::Print:
        _taskArray.push_back(PrintTask(newTask->_id, newTask->_text));
        break;
    case Task::Calculate:
        _taskArray.push_back(CalculateTask(newTask->_id, newTask->_text));
        break;
    case Task::Hashing:
        _taskArray.push_back(HashingTask(newTask->_id, newTask->_text));
        break;
    default:
        std::__throw_invalid_argument("NewTask doesn't have task type");
        break;
    }
    if (_taskArray.size() == containerSize)
        _filled = true;
    this->ShowAllTasks();
}

template <size_t containerSize>
void TaskContainer<containerSize>::ShowAllTasks()
{
    if (IsEmpty())
        return;
    auto setIndent = [](const std::string &str, int indent) -> std::stringstream
    { std::stringstream strStream; strStream << std::setw(indent) << str; return strStream; };

    for (auto it = _taskArray.begin(); it != _taskArray.end(); ++it)
    {
        // clang-format off
        std::string result = std::visit([&](auto &&arg) -> std::string
                                {
                                    return std::format(
                                    "|{}|{}|{}|\n", 
                                    setIndent(std::to_string(arg._id), 8).view(),
                                    setIndent(std::to_string(arg.type()), 10).view(),
                                    setIndent(arg._text, 25).view());
                                }, *it);
        // clang-format on
        std::cout << result;
    }
}

#endif // CONTAINER_H
