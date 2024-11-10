#ifndef __REQUEST_H__
#define __REQUEST_H__
#include <memory>
#include <vector>
#include <pair>
#include "config.h"
#include "Arg.h"
#include "logger.h"
enum Command{
    Write,
    Read,
    Execute,
    COMMANDS_COUNT
};

typedef std::vector<Type> types_t;

const types_t COMMAND_TYPES{
    {Type::Str, Type::Str, Type::Int},
    {Type::Str, Type::Int},
    {Type::Str}
};

const byte IUIP_LABEL[4] = {'I','U','I','P'};
const byte IUIP_VERS[4] = {'.','V','E','R'};

typedef std::vector<Arg> args_t;
typedef std::pair<Command, args_t> cmd_arg_t;
typedef std::vector<cmd_arg_t> cmd_list_t;

class Request{
public:
    Request();
    bool parse(message raw);
    void pushCmd(cmd_arg_t cmd);
    cmd_arg_t popCmd();
    cmd_list_t getCommands();
    message getMessage();
    
private:
    cmd_list_t commands;
};
#endif