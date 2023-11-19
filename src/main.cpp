/* Задача 2.
Система состоит из трех процессоров P0, P1, P2, очереди F, сте-
ка S и распределителя задач R. В систему поступают запросы на
выполнение задач трёх типов – T0, T1 и T2, каждая для своего
процессора.
*/

#include <thread>
#include <iostream>

#include "Queue.h"
#include "Task.h"
#include "TaskGeneration.h"
#include "TaskDistributor.h"

using std::cin;
using std::cout;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    Queue *_queue = new Queue();
    TaskDistributor *taskDist = new TaskDistributor(_queue);
    auto asyncDist = std::thread(&TaskDistributor::Exec, taskDist);
    asyncDist.detach();

    TaskGeneration * taskGen = new TaskGeneration(_queue);

    int num = 0;
    int id = 0;
    do
    {
        cout << "Выберите действие: 1 - выбрать задание, 2 - сгенерировать задания\n";
        cin >> num;

        if (num == 1)
        {
            cout << "Выберите задание (0, 1, 2):";
            cin >> num;
            std::string text;
            cout << "Выберите текст для задания: ";
            cin >> text;

            Task::TaskType type = Task::NoType;
            if (num >= 0 && num <= 2)
            {
                type = static_cast<Task::TaskType>(num);
                switch (type)
                {
                case Task::Print:
                    _queue->PushTask(new PrintTask(id, text));
                    break;
                case Task::Calculate:
                    _queue->PushTask(new CalculateTask(id, text));
                    break;
                case Task::Hashing:
                    _queue->PushTask(new HashingTask(id, text));
                    break;
                default:
                    break;
                }
                ++id;
            }
        }
        else if (num == 2)
        {
            taskGen->SetId(id);
            taskGen->Exec();
        }
    } while (cin);
    taskDist->Stop();
    delete taskDist;
    delete taskGen;
    delete _queue;
    return 0;
}
