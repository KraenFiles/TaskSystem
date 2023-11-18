#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <string>

struct Task
{
    enum TaskType
    {
        NoType = -1,
        Print = 0,
        Added = 1,
        Hashing = 2
    };

    Task(TaskType setType = NoType);
    Task(int32_t _id, uint64_t _timeArrival, const std::string &newText, TaskType setType = NoType);
    virtual ~Task();

    virtual void startTask() = 0;

    int32_t id;
    uint64_t timeArrival;
    std::string text;
    inline TaskType type() const { return _type; }

private:
    TaskType _type;
};

struct PrintTask : public Task
{
    PrintTask(int32_t id, uint64_t timeArrival, const std::string &newText);
    ~PrintTask();

    void startTask() override;
};

struct AddTask : public Task
{
    AddTask(int32_t id, uint64_t timeArrival, const std::string &newText);
    ~AddTask();

    void startTask() override;
};

struct HashingTask : public Task
{
    HashingTask(int32_t id, uint64_t timeArrival, const std::string &newText);
    ~HashingTask();

    void startTask() override;
};

#endif // TASK_H
