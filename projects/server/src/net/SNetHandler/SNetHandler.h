#ifndef __S_NET_HANDLER_H__
#define __S_NET_HANDLER_H__
#include <stdint.h>
#include "config.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "logger.h"
#include <memory>
//Класс для работы с сетевой связью
class SNetHandler{
public:
    SNetHandler();
    ~SNetHandler();

    void      proc(buffer_t &buf);
private:
    //ClientRequest   recievMessage();
    sd              sock;
    sockaddr_in     sadr;
};

#endif