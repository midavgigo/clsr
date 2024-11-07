#ifndef __REQUEST_H__
#define __REQUEST_H__
#include <memory>
#include <vector>
#include "config.h"
#include "Arg.h"
#include "logger.h"
enum Command{
    Write,
    Read,
    Execute
};


const byte IUIP_LABEL[4] = {'I','U','I','P'};
const byte IUIP_VERS[4] = {'.','V','E','R'};

class Request{
public:
    Request();
    Request(Command cmd);
    bool parse(std::unique_ptr<byte> raw);
    void setCmd(Command cmd);
    void addArg(Arg a);
    std::unique_ptr<byte> getMessage();
    Command getCmd();
    
private:
    Command cmd_;
    std::vector<Arg> args;
};
#endif