#include "TaskQueue.h"
#include <fstream>
size_t TaskQueue::addCommand(task_t task){
    q_.push(task);
}

void* proc_task(void *task_ptr){
    task_t task = *(task_t *)task_ptr;
    for(cmd_arg_t cmd : task){
        switch(cmd.first){
            case Command::Write:{
                    char path[256];
                    char text[256];
                    cmd.second[0].getValue(path);
                    cmd.second[1].getValue(text);
                    Logger::logf("Path %s Text %s", path, text);
                    std::ofstream fout(path);
                    fout << text;
                    fout.close();
                    break;
                }
            case Command::Execute:{
                    char command[256];
                    cmd.second[0].getValue(command);
                    system(command);
                    break;
                }
        }
    }
    return nullptr;
}

void TaskQueue::proc(){
    if(q_.size() <= 0){
        return;
    }
    for(int i = 0; i < CMAKE_THREAD_LIMIT; i++){
        int res = pthread_tryjoin_np(threads_[i], nullptr);
        if(res == 0 || res == ESRCH){
            Logger::logf("Thread %d is free", i);
            task_t task = q_.front();
            q_.pop();
            pthread_create(&threads_[i], nullptr, proc_task, &task);
        }
    }
}