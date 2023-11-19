#include "TaskVisitor.h"

#include <thread>
#include "Processor.h"

TaskVisitor::TaskVisitor()
    : _setTask(false),
      _printProc(new Processor()),
      _calculateProc(new Processor()),
      _hashingProc(new Processor())
{
    auto threadPrint = std::thread(&Processor::Exec, _printProc);
    threadPrint.detach();
    auto threadAdd = std::thread(&Processor::Exec, _calculateProc);
    threadAdd.detach();
    auto threadHash = std::thread(&Processor::Exec, _hashingProc);
    threadHash.detach();
}

TaskVisitor::~TaskVisitor()
{
    _printProc->Stop();
    _calculateProc->Stop();
    _hashingProc->Stop();

    delete _printProc;
    delete _calculateProc;
    delete _hashingProc;
}

void TaskVisitor::operator()(const PrintTask & task)
{
    if(!_printProc->IsBuzy())
    {
        _printProc->SetTask(&task);
        _setTask = true;
    }
    else
    {
        _setTask = false;
    }
}
void TaskVisitor::operator()(const CalculateTask & task)
{ 
    if(!_calculateProc->IsBuzy())
    {
        _calculateProc->SetTask(&task);
        _setTask = true;
    }
    else
    {
        _setTask = false;
    }
}

void TaskVisitor::operator()(const HashingTask & task)
{ 
    if(!_hashingProc->IsBuzy())
    {
        _hashingProc->SetTask(&task);
        _setTask = true;
    }
    else
    {
        _setTask = false;
    }
}