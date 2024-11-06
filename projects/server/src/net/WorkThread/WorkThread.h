#ifndef __WORK_THREAD_H__
#define __WORK_THREAD_H__
#include <memory>
class WorkThread{
public:
    WorkThread(void (*func)());
    ~WorkThread();
    void proc();
private:
    void (*func_)();
};
#endif