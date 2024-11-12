#include "SNetHandler.h"

SNetHandler::SNetHandler(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        Logger::errf("Can't create a socket. %d", sock);
    }else{
        Logger::logf("Socket for listening created: %d", sock);
    }
    sadr.sin_family         = AF_INET;
    sadr.sin_addr.s_addr    = INADDR_ANY;
    sadr.sin_port           = htons(CMAKE_SERVER_PORT);
    int result = bind(sock, (const sockaddr *)&sadr, sizeof(sadr));
    if(result < 0){
        Logger::errf(
            "Can't bind socket to address. \
            socket descriptor=%d \
            address=%d, %d:%d", 
            sock, sadr.sin_family, sadr.sin_addr, sadr.sin_port);
    }else{
        Logger::logf(
            "Socket %d binded to address: %d, %d:%d", 
            sock, sadr.sin_family, sadr.sin_addr, sadr.sin_port
        );
    }
    result = listen(sock, CMAKE_THREAD_LIMIT);
    if(result < 0){
        Logger::errf(
            "Can't set listen mod on socket. \
            socket descriptor=%d",
            sock
        );
    }else{
        Logger::logf(
            "Socket %d set to listen mod",
            sock
        );
    }
}
SNetHandler::~SNetHandler(){
    close(sock);
}

void SNetHandler::proc(buffer_t &buf){
    sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);
    Logger::logf("Wait for accept client request");
    sd nsock = accept(sock, (sockaddr *)&client_address,  &addrlen);
    if(nsock < 0){
        Logger::errf(
            "Can't accept client. socket descriptor=%d", 
            nsock);
    }
    byte buffer[CMAKE_REQUEST_LIMIT+1];
    buffer[CMAKE_REQUEST_LIMIT] = 0;
    int result = recv(nsock, buffer, sizeof(byte)*CMAKE_REQUEST_LIMIT, 0);
    if(result<0){
        Logger::errf("Can't recieve message from client.");
    }
    Logger::logf("Get client message: %s", buffer);
    buf = buffer_t(new byte[CMAKE_REQUEST_LIMIT]);
    std::memcpy(buf.get(), buffer, sizeof(byte)*CMAKE_REQUEST_LIMIT);
    // result = send(nsock, "answer", sizeof(message_unit)*8, 0);
    // if(result<0){
    //     Logger::errf("Can't send message to client.");
    // }
}