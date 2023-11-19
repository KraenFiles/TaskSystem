#ifndef TASK_VISITOR_H
#define TASK_VISITOR_H

#include "Task.h"

class Processor;

class TaskVisitor
{
public:
    TaskVisitor();
    ~TaskVisitor();

    void operator()(const PrintTask &task);
    void operator()(const CalculateTask &task);
    void operator()(const HashingTask &task);

    inline bool IsSetTask() { return _setTask; }

private:
    bool _setTask;

    Processor *_printProc;
    Processor *_calculateProc;
    Processor *_hashingProc;
};

#endif