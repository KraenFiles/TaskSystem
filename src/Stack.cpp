#include "Stack.h"

#include <exception>

Stack::Stack()
    : TaskContainer<MAX_STACK_SIZE>()
{
}

Stack::~Stack()
{
}

Stack::Iterator Stack::GetTask() const
{
    return (_taskArray.end()-1);
}

void Stack::PopTask()
{
    if(IsEmpty()) std::__throw_out_of_range("Stack is empty");
    _taskArray.pop_back();
}