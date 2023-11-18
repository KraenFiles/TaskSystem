#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Task.h"

#include <mutex>

class Processor
{
public:
    Processor();
    ~Processor();

    void SetTask(Task *newTask);
    void Exec();

    inline void Stop() { _stopProcessor = true; }
    inline bool IsBuzy() { return _inProcess; }

private:
    Task *_task;
    bool _inProcess;
    bool _stopProcessor = false;

    std::mutex _procMutex;
};

#endif
