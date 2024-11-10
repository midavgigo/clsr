#include "Arg.h"
#include "Request.h"
#include <memory>
#include <iostream>
#include "logger.h"
int main(){
    Logger::init("test");
    Request req;
    Arg path(Type::Str);
    path.copyValue("path");
    Arg text(Type::Str);
    text.copyValue("text");
    Arg mode(Type::Int);
    int wmode = 0;
    mode.copyValue(&wmode);
    req.pushCmd({Command::Write, {path, text, mode}});
    buffer buf;
    req.getMessage(buf);
    Request req_a;
    bool res = req_a.parse(move(buf));
    if(res){
        for(cmd_arg_t cmd : req_a.getCommands()){
            std::cout<<cmd.first<<"\n";
            for(Arg arg : cmd.second){
                std::cout<<"\t"<<arg.getType()<<"\n";
                int i;
                float f;
                char str[256];
                switch(arg.getType()){
                    case Type::Str:
                        arg.getValue(str);
                        std::cout<<"\t"<<str<<"\n";
                        break;
                    case Type::Flt:
                        arg.getValue(&f);
                        std::cout<<"\t"<<f<<"\n";
                        break;
                    case Type::Int:
                        arg.getValue(&i);
                        std::cout<<"\t"<<i<<"\n";
                        break;
                }
            }
        }
    }
    return 0;
}