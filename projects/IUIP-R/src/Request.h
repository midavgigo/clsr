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
    Read,
    Execute,
    COMMANDS_COUNT
};

typedef std::vector<Type> types_t;

const types_t COMMAND_TYPES[] = {
    {Type::Str, Type::Str, Type::Int},
    {Type::Str, Type::Int},
    {Type::Str}
};

const byte IUIP_LABEL[6] = {'I','U','I','P','-','R'};
const byte IUIP_VERS[4] = {'.','V','E','R'};

typedef std::vector<Arg> args_t;
typedef std::pair<Command, args_t> cmd_arg_t;
typedef std::vector<cmd_arg_t> cmd_list_t;

class Request{
public:
    Request(IUIP_version v = IUIP_version::INDEV);
    bool parse(buffer raw);
    void pushCmd(cmd_arg_t cmd);
    cmd_arg_t popCmd();
    cmd_list_t getCommands();
    void getMessage(buffer &buf);
private:
    size_t getMessageSize();

    IUIP_version v_;
    cmd_list_t commands_;
};
#endif