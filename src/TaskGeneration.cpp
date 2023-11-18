#include "TaskGeneration.h"
#include "Task.h"
#include "Queue.h"

#include <thread>
#include <iostream>

TaskGeneration::TaskGeneration(Queue *queue)
    : _queue(queue), sendId(-1)
{
}

TaskGeneration::~TaskGeneration()
{
}

void TaskGeneration::exec()
{
    while (true)
    {
        if (!_queue->isFilled())
        {
            createTask();
        }
        else
        {
            std::clog << "Очередь переполнена\n";
        }
    }
}

void TaskGeneration::createTask()
{
    std::random_device rand;
    std::default_random_engine randEngine(rand());
    std::uniform_int_distribution<int> distType(0, 2);
    std::uniform_real_distribution<double> distText(1, 100);
    std::uniform_int_distribution<int> distTime(300, 500);

    auto taskNum = static_cast<Task::TaskType>(distType(randEngine));
    ++sendId;

    Task *newTask = nullptr;
    switch (taskNum)
    {
    case Task::Print:
        newTask = new PrintTask(sendId, distTime(randEngine), std::to_string(distText(randEngine)));
        break;

    case Task::Added:
        newTask = new AddTask(sendId, distTime(randEngine), std::to_string(distText(randEngine)));
        break;

    case Task::Hashing:
        newTask = new HashingTask(sendId, distTime(randEngine), std::to_string(distText(randEngine)));
        break;
    default:
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(newTask->timeArrival));
    _queue->addElement(newTask);
}
