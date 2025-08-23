#ifndef TASK_QUEUE
#define TASL_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>

enum TaskType {
    HANDLE_CLIENT_REQUEST
};

struct Task {
    TaskType    taskType;
    int         client_fd;
};


class TaskQueue {
public:
    void Push(Task);

    Task Pop();

private:
    std::queue<Task> m_Queue;
    std::mutex  m_Mutex;
    std::condition_variable m_CV;
};

#endif