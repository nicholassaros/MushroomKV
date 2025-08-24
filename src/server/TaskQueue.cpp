#include "TaskQueue.h"


void TaskQueue::Push(Task task){
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Queue.push(task);
    m_CV.notify_one();
};

Task TaskQueue::Pop() {
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_CV.wait(lock, [this] { return !m_Queue.empty(); });

    Task task = std::move(m_Queue.front());
    m_Queue.pop();
    return task;
};