#include "WorkThread.h"

WorkThread::WorkThread(void (*func)()):func_(func){

}

void WorkThread::proc(){
    func_();
}