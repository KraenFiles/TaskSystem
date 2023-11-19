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
        Calculate = 1,
        Hashing = 2
    };

    Task();
    Task(int32_t id, const std::string &text, TaskType setType = NoType);
    virtual ~Task() = default;
    virtual void startTask() = 0;
    virtual Task *clone() const = 0;

    int32_t _id;
    std::string _text;

    inline TaskType type() const { return _type; }
    
private:
    TaskType _type;
};

struct PrintTask : public Task
{
    PrintTask(int32_t id, const std::string &text);
    ~PrintTask();

    void startTask() override;
    inline PrintTask *clone() const override { return new PrintTask(*this); }
};

struct CalculateTask : public Task
{
    CalculateTask(int32_t id, const std::string &text);
    ~CalculateTask();

    void startTask() override;
    inline CalculateTask *clone() const override { return new CalculateTask(*this); }
};

struct HashingTask : public Task
{
    HashingTask(int32_t id, const std::string &text);
    ~HashingTask();

    void startTask() override;
    inline HashingTask *clone() const override { return new HashingTask(*this); }
};

#endif // TASK_H
