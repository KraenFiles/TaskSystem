#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <string>

struct Task
{
    Task();
    Task(int32_t _id, const std::string &text);
    virtual ~Task() = default;
    virtual void startTask() = 0;
    virtual Task *clone() const = 0;

    int32_t id;
    std::string _text;
};

struct PrintTask : public Task
{
    PrintTask(int32_t id, const std::string &text);
    ~PrintTask();

    void startTask() override;
    inline PrintTask *clone() const { return new PrintTask(*this); }
};

struct CalculateTask : public Task
{
    CalculateTask(int32_t id, const std::string &text);
    ~CalculateTask();

    void startTask() override;
    inline CalculateTask *clone() const { return new CalculateTask(*this); }
};

struct HashingTask : public Task
{
    HashingTask(int32_t id, const std::string &text);
    ~HashingTask();

    void startTask() override;
    inline HashingTask *clone() const { return new HashingTask(*this); }
};

#endif // TASK_H
