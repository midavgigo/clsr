#ifndef __C_NET_HANDLER_H__
#define __C_NET_HANDLER_H__
#include <string>
#include <memory>
#include "config.h"
#include <sys/socket.h>
#include "logger.h"
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
class CNetHandler{
public:
    CNetHandler();
    CNetHandler(std::string address, uint16_t port);
    ~CNetHandler();

    void change_address(std::string address, uint16_t port);
    void send_message(std::string message);
    void send_message(std::unique_ptr<byte> buffer, size_t len=0);
private:
    sockaddr_in sadr;
};
#endif