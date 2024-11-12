#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__
#include <queue>
#include "Request.h"
#include "config.h"

class TaskQueue{
public:
    size_t addCommand(task_t task_ptr);
    void proc();
private:
    pthread_t threads_[CMAKE_THREAD_LIMIT];
    std::queue<task_t> q_;
};

#endif