#ifndef TASKGENERATION_H
#define TASKGENERATION_H

#include <random>
#include <stdint.h>

class Queue;
class Task;

class TaskGeneration
{
public:
    TaskGeneration(Queue *queue);
    ~TaskGeneration();

    void Exec();

    inline void SetId(int32_t id) { sendId = id; }

protected:
    void CreateTask();

private:
    Queue *_queue;

    const uint32_t SECS_TO_SEND = 3;
    int32_t sendId;
};

#endif // TASKGENERATION_H
