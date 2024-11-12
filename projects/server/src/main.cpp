#include <iostream>
#include <cstring>
#include "logger.h"
#include "net/SNetHandler/SNetHandler.h"
#include "Request.h"
#include <pthread.h>
#include <fstream>
#include <stdlib.h>

void write(std::string path, std::string text){
    std::ofstream fout(path);
    fout << text;
    fout.close();
}

void execute(std::string command){
    system(command.c_str());
}

int main(){
    Logger::init("SERVER");
    Logger::logf("Server's logger initialized");
    SNetHandler nh;
    while(true){
        buffer_t buffer;
        nh.proc(buffer);
        Request r;
        if(r.parse(std::move(buffer))){
            for(cmd_arg_t cmd : r.getCommands()){
                switch (cmd.first){
                    case Command::Write:

                }
            }
        }
    }
}