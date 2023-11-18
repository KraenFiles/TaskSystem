#include "Task.h"

#include <iostream>
#include <functional>

Task::Task(TaskType setType)
    : id(-1), timeArrival(1000), text("default text"), _type(setType)
{
}

Task::Task(int32_t _id, uint64_t _timeArrival, const std::string &newText, TaskType setType)
    : id(_id), timeArrival(_timeArrival), text(newText), _type(setType)
{
}

Task::~Task()
{
}

PrintTask::PrintTask(int32_t id, uint64_t timeArrival, const std::string &newText)
    : Task(id, timeArrival, newText, Print)
{
}

PrintTask::~PrintTask()
{
}

void PrintTask::startTask()
{
    std::cout << "Printing task for id: " << id << "\n"
              << text << "\n";
}

AddTask::AddTask(int32_t id, uint64_t timeArrival, const std::string &newText)
    : Task(id, timeArrival, newText, Added)
{
}

AddTask::~AddTask()
{
}

void AddTask::startTask()
{
    text.append(" add function");
    std::cout << "Added task for id: " << id << "\n"
              << text << "\n";
}

HashingTask::HashingTask(int32_t id, uint64_t timeArrival, const std::string &newText)
    : Task(id, timeArrival, newText, Hashing)
{
}

HashingTask::~HashingTask()
{
}

void HashingTask::startTask()
{
    size_t hash = std::hash<std::string>{}(text);
    std::cout << "Hashing task for id: " << id << "\n"
              << hash << "\n";
}
