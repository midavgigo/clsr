#ifndef __NET_HANDLER_H__
#define __NET_HANDLER_H__
#include <stdint.h>
#include <queue>
#include "config.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "logger.h"
enum ClientRequest{
    None
};
enum ProcResult{
    Success,
    Warning,
    Error
};
typedef std::queue<ClientRequest> request_queue;
typedef int32_t sd;
typedef char    message_unit;
//Класс для работы с сетевой связью
class NetHandler{
public:
    NetHandler();
    ~NetHandler();

    ProcResult      proc();
private:
    //ClientRequest   recievMessage();
    request_queue   qreq;
    sd              sock;
    sockaddr_in     sadr;
};

#endif