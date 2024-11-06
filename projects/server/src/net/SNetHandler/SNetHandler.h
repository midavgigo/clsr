#ifndef __S_NET_HANDLER_H__
#define __S_NET_HANDLER_H__
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
typedef char    message_unit;
//Класс для работы с сетевой связью
class SNetHandler{
public:
    SNetHandler();
    ~SNetHandler();

    ProcResult      proc();
private:
    //ClientRequest   recievMessage();
    request_queue   qreq;
    sd              sock;
    sockaddr_in     sadr;
};

#endif