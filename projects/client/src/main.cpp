#include <iostream>
#include "config.h"
#include "logger.h"
#include "CNetHandler/CNetHandler.h"
#include <thread>
#include <chrono>

int main(){
    Logger::init("CLIENT");
    Logger::logf("Client's logger initialized");
    CNetHandler hand("127.0.0.1", CMAKE_SERVER_PORT);
    while(true){
        hand.send_message("zdarova");
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}