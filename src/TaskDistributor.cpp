#include "TaskDistributor.h"

#include "Queue.h"
#include "Stack.h"
#include "TaskVisitor.h"

#include <thread>
#include <iostream>

TaskDistributor::TaskDistributor(Queue *queue)
    : _queue(queue), _stack(new Stack()), _visitor(new TaskVisitor())
{
}

TaskDistributor::~TaskDistributor()
{
    delete _visitor;
    delete _stack;
}

void TaskDistributor::Exec()
{
    while (!_stopDistributor)
    {
        if (!_stack->IsEmpty())
        {
            std::visit(*_visitor, *_stack->GetTask());
            if(_visitor->IsSetTask())
                _stack->PopTask();
        }

        if (!_queue->IsEmpty())
        {
            std::visit(*_visitor, *_queue->GetTask());
            if(_visitor->IsSetTask())
            {
                _queue->UpdateQueue();
            }
            else
            {
                if(!_stack->IsFilled())
                {
                    auto ref = _queue->PopTask();
                    _stack->PushTask(ref);
                }
            }
        }
    }
}
