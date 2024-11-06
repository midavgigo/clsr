#include <iostream>
#include <cstring>
#include "logger.h"
#include "net/SNetHandler/SNetHandler.h"

int main(){
    Logger::init("SERVER");
    Logger::logf("Server's logger initialized");
    SNetHandler nh;
    while(true){
        try{
            nh.proc();
        }catch(...){
            break;
        }
    }
}