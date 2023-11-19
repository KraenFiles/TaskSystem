#include "Processor.h"

#include <iostream>
#include <thread>

Processor::Processor()
    : _task(nullptr), _inProcess(false)
{
}

Processor::~Processor()
{
    delete _task;
}

void Processor::SetTask(const Task *newTask)
{
    std::lock_guard<std::mutex> lock(_procMutex);
    _task = newTask->clone();
    std::cout << "Задача установлена в процессор c id: " << _task->id << std::endl;
}

void Processor::Exec()
{
    while (!_stopProcessor)
    {
        if (!_inProcess && _task != nullptr)
        {
            std::lock_guard<std::mutex> lock(_procMutex);
            _inProcess = true;
            _task->startTask();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            delete _task;
            _task = nullptr;
            _inProcess = false;
        }
    }
}