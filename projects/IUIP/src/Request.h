#ifndef __REQUEST_H__
#define __REQUEST_H__
#include <memory>
#include <vector>
#include <utility>
#include "config.h"
#include "Arg.h"
#include "logger.h"
enum Command{
    Write = 0,
    //Read,
    Execute,
    COMMANDS_COUNT
};

const std::string COMMAND_NAMES[] = {
    "Write to file. Arguments Path:Str, Text:Str",
    //"Read the file. Arguments Path:Str",
    "Execute command. Arguments Command:Str"
};

typedef std::vector<Type> types_t;

const types_t COMMAND_TYPES[] = {
    {Type::Str, Type::Str},
    //{Type::Str},
    {Type::Str}
};

const byte IUIP_LABEL[6] = {'I','U','I','P','-','R'};
const byte IUIP_VERS[4] = {'.','V','E','R'};

typedef std::vector<Arg> args_t;
typedef std::pair<Command, args_t> cmd_arg_t;
typedef std::vector<cmd_arg_t> task_t;

class Request{
public:
    Request(IUIP_version v = IUIP_version::INDEV);
    bool parse(buffer_t raw);
    void pushCmd(cmd_arg_t cmd);
    void popCmd();
    task_t getCommands();
    size_t getMessage(buffer_t &buf);
private:
    size_t getMessageSize();

    IUIP_version v_;
    task_t commands_;
};
#endif