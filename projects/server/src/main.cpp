#include <iostream>
#include "logger.h"
#include "NetHandler/NetHandler.h"

int main(){
    Logger::init();
    NetHandler nh;
    while(true){
        try{
            nh.proc();
        }catch(...){
            break;
        }
    }
}