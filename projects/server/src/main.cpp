#include <iostream>
#include <cstring>
#include "logger.h"
#include "net/SNetHandler/SNetHandler.h"
#include "threading/TaskQueue.h"
#include "Request.h"
#include <pthread.h>
#include <fstream>
#include <stdlib.h>

int main(){
    Logger::init("SERVER");
    Logger::logf("Server's logger initialized");
    SNetHandler nh;
    TaskQueue tq;
    while(true){
        buffer_t buffer;
        nh.proc(buffer);
        Request r;
        if(r.parse(std::move(buffer))){
            //tq.addCommand(r.getCommands());
            for(cmd_arg_t cmd : r.getCommands()){
                Logger::logf("Getted command: %d", cmd.first);
                for(Arg a : cmd.second){
                    Logger::logf("Getted Argument with type: %d", a.getType());
                    switch(a.getType()){
                        case Type::Int:{
                            int i;
                            a.getValue(&i);
                            Logger::logf("\t%d", i);
                            break;
                        }
                        case Type::Flt:{
                            float i;
                            a.getValue(&i);
                            Logger::logf("\t%f", i);
                            break;
                        }
                        case Type::Str:{
                            char str[256];
                            a.getValue(str);
                            Logger::logf("\t%s", str);
                            break;
                        }
                    }
                }
            }
        }
        //tq.proc();
    }
}