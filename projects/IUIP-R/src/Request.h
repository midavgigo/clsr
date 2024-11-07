#ifndef __REQUEST_H__
#define __REQUEST_H__
#include <memory>
#include <vector>
#include "config.h"
enum Command{
    Write,
    Read,
    Execute
};

class Request{
public:
    Request(Command command);
    Request(std::unique_ptr<byte> raw);
    void addArg(Type t, std::unique_ptr<byte> arg);
    std::unique_ptr<byte> getMessage();
    Command getCmd();
    
private:
    Command cmd;
    std::vector<Type> argTypes;
    std::vector<std::unique_ptr<byte>> args; 
};
#endif