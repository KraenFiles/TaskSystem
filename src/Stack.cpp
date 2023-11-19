#include "Stack.h"

#include <exception>

Stack::Stack()
    : TaskContainer<MAX_STACK_SIZE>()
{
}

Stack::~Stack()
{
}

Stack::ConstIterator Stack::GetTask() const
{
    if(IsEmpty()) return nullptr;
    return _taskArray.begin()+(_tasksCount-1);
}

Stack::ValueType Stack::PopTask()
{
    if(IsEmpty()) std::__throw_out_of_range("Stack is empty");
    ValueType result = _taskArray.at(_tasksCount);
    --_tasksCount;
    return result;
}