/* Задача 2.
Система состоит из трех процессоров P0, P1, P2, очереди F, сте-
ка S и распределителя задач R. В систему поступают запросы на
выполнение задач трёх типов – T0, T1 и T2, каждая для своего
процессора.
*/

#include <future>
#include <clocale>

#include "Queue.h"
#include "Stack.h"
#include "Task.h"
#include "Process.h"
#include "TaskGeneration.h"
#include "TaskDistributor.h"

using std::cin;
using std::cout;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    setlocale(LC_ALL, "russian");
    Queue *_queue = new Queue();
    Stack *_stack = new Stack();
    Process<PrintTask> *printProc = new Process<PrintTask>();
    auto asyncPrint = std::thread(&Process<PrintTask>::exec, printProc);
    asyncPrint.detach();
    Process<AddTask> *addProc = new Process<AddTask>();
    auto asyncAdd = std::thread(&Process<AddTask>::exec, addProc);
    asyncAdd.detach();
    Process<HashingTask> *hashProc = new Process<HashingTask>();
    auto asyncHash = std::thread(&Process<HashingTask>::exec, hashProc);
    asyncHash.detach();
    TaskDistributor *taskDist = new TaskDistributor(_queue, _stack, printProc, addProc, hashProc);
    auto asyncDist = std::thread(&TaskDistributor::exec, taskDist);
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
            uint64_t time;
            cout << "Введите время отправки в миллисекундах: ";
            cin >> time;

            Task::TaskType type = Task::NoType;
            if (num >= 0 && num <= 2)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(time));
                type = static_cast<Task::TaskType>(num);
                switch (type)
                {
                case Task::Print:
                    _queue->addElement(new PrintTask(id, time, text));
                    break;
                case Task::Added:
                    _queue->addElement(new AddTask(id, time, text));
                    break;
                case Task::Hashing:
                    _queue->addElement(new HashingTask(id, time, text));
                    break;
                default:
                    break;
                }
                ++id;
            }
        }
        else if (num == 2)
        {
            taskGen->setId(id);
            taskGen->exec();
        }
    } while (cin);
    taskDist->stop();
    printProc->stop();
    addProc->stop();
    hashProc->stop();
    return 0;
}
