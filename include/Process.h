#ifndef PROCESS_H
#define PROCESS_H
#include "Task.h"

#include <thread>
#include <mutex>
#include <iostream>

template <typename T>
class Process
{
public:
    Process();
    ~Process();

    void setTask(T *newTask);
    void exec();

    inline void stop() { _stopProcessor = true; }
    inline bool isBuzy() { return _inProcess; }

private:
    T *_task;
    bool _inProcess;
    bool _stopProcessor = false;

    std::mutex _procMutex;
};

template <typename T>
inline Process<T>::Process()
    : _task(nullptr), _inProcess(false)
{
}

template <typename T>
Process<T>::~Process()
{
}

template <typename T>
void Process<T>::setTask(T *newTask)
{
    std::lock_guard<std::mutex> lock(_procMutex);
    _task = new T(newTask->id, newTask->timeArrival, newTask->text);
    std::cout << "Задача установлена в процессор " << typeid(T).name() << " c id: " << _task->id << std::endl;
}

template <typename T>
void Process<T>::exec()
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

#endif
