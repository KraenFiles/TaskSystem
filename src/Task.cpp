#include "Task.h"

#include <iostream>

Task::Task() : id(0), _type(TaskType::NoType) {}

Task::Task(int32_t _id, const std::string &text, TaskType setType = NoType) 
: id(_id), _text(text), _type(setType) {}

Task::~Task() {}

PrintTask::PrintTask(int32_t id, const std::string &text)
    : Task(id, text, TaskType::Print)
{
}

PrintTask::~PrintTask() {}

void PrintTask::startTask()
{
    std::cout << "Printing task for id: " << id << "\n"
              << _text << std::endl;
}

CalculateTask::CalculateTask(int32_t id, const std::string &text)
    : Task(id, text, TaskType::Calculate)
{
}

CalculateTask::~CalculateTask() {}

void CalculateTask::startTask()
{
    std::cout << "CalculateTask task for id: " << id << "\n"
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
    std::cout << "Hashing task for id: " << id << "\n"
              << "Hash is " << hash << std::endl;
}
