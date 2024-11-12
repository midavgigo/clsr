#include <iostream>
#include "config.h"
#include "client_config.h"
#include "logger.h"
#include "CNetHandler/CNetHandler.h"
#include <thread>
//#include <chrono>
#include "Request.h"
#include "Arg.h"

int main(){
    Logger::init("CLIENT");
    Logger::logf("Client's logger initialized");
    CNetHandler hand(CONNECT_ADDRESS, CONNECT_PORT);
    while(true){
        if(CLIENT_INTERFACE == interfaces::CLI){
            std::cout<<"Input count of commands [0:256): ";
            int count;
            std::cin>>count;
            if(count < 0 || count > 255){
                std::cout<<"Wrong count of commands\n";
                continue;
            }
            Request r;
            for(int c = 0; c < count; c++){
                std::cout<<"Choose command(input number): \n";
                int option = 0;
                for(int i = 0; i < Command::COMMANDS_COUNT; i++){
                    std::cout<<"\t"<<i<<") "<<COMMAND_NAMES[i]<<"\n";
                }
                std::cin >> option;
                if (option >= 0 && option < Command::COMMANDS_COUNT){
                    std::cout<<"Input arguments:\n";
                    int i;
                    float f;
                    std::string s;
                    cmd_arg_t cmd;
                    cmd.first = (Command)option;
                    for(Type t : COMMAND_TYPES[option]){
                        cmd.second.push_back(Arg(t));
                        switch(t){
                            case Type::Int:
                                std::cout<<"Input integer: ";
                                std::cin >> i;
                                cmd.second[cmd.second.size()-1].copyValue(&i);
                                break;
                            case Type::Flt:
                                std::cout<<"Input float: ";
                                std::cin >> f;
                                cmd.second[cmd.second.size()-1].copyValue(&f);
                                break;
                            case Type::Str:
                                std::cout<<"Input text: ";
                                std::cin >> s;
                                cmd.second[cmd.second.size()-1].copyValue(s.c_str());
                                break;
                        }
                    }
                    r.pushCmd(cmd);
                    for(cmd_arg_t cmd : r.getCommands()){
                        Logger::logf("cmd %d", cmd.first);
                        for(Arg arg : cmd.second){
                            Logger::logf("arg type %d", arg.getType());
                        }
                    }
                    buffer_t message;
                    size_t size = r.getMessage(message);
                    for(int i = 0; i < size; i++){
                        std::cout<<(char)*(message.get()+i)<<",";
                    }
                    std::cout<<"\n";
                    for(int i = 0; i < size; i++){
                        std::cout<<(int)*(message.get()+i)<<",";
                    }
                    std::cout<<"\n";
                    hand.send_message(move(message), size);
                }else{
                    std::cout<<"Wrong command, try again!\n";
                }
            }
        }
    }
}