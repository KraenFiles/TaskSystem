#include "Task.h"

#include <iostream>

Task::Task() : _id(0), _type(TaskType::NoType) {}

Task::Task(int32_t id, const std::string &text, TaskType setType) 
: _id(id), _text(text), _type(setType) {}

PrintTask::PrintTask(int32_t id, const std::string &text)
    : Task(id, text, TaskType::Print)
{
}

PrintTask::~PrintTask() {}

void PrintTask::startTask()
{
    std::cout << "Printing task for id: " << _id << "\n"
              << _text << std::endl;
}

CalculateTask::CalculateTask(int32_t id, const std::string &text)
    : Task(id, text, TaskType::Calculate)
{
}

CalculateTask::~CalculateTask() {}

void CalculateTask::startTask()
{
    std::cout << "CalculateTask task for id: " << _id << "\n"
              << "Lenght is " << _text.length() << std::endl;
}

HashingTask::HashingTask(int32_t id, const std::string &text)
    : Task(id, text, TaskType::Hashing)
{
}

HashingTask::~HashingTask() {}

void HashingTask::startTask()
{
    size_t hash = std::hash<std::string>{}(_text);
    std::cout << "Hashing task for id: " << _id << "\n"
              << "Hash is " << hash << std::endl;
}
