#include "CNetHandler.h"

CNetHandler::CNetHandler(){
    sadr.sin_family = AF_INET;
}

CNetHandler::CNetHandler(std::string address, uint16_t port): CNetHandler(){
    sadr.sin_port = htons(port);
    sadr.sin_addr.s_addr = inet_addr(address.c_str());
}

CNetHandler::~CNetHandler(){
}

void CNetHandler::change_address(std::string address, uint16_t port){
    sadr.sin_port = htons(port);
    sadr.sin_addr.s_addr = inet_addr(address.c_str());
}

void CNetHandler::send_message(std::string message){
    std::unique_ptr<byte> mes{new byte(message.size())};
    for(int i = 0; i < message.size(); i++){
        *(mes.get()+i) = message[i];
    }
    send_message(move(mes), message.size());
}

void CNetHandler::send_message(std::unique_ptr<byte> buffer, size_t len){
    sd sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0){
        Logger::errf("Can't create client's socket");
    }else{
        Logger::logf("Socket for client is created: %d", sock);
    }
    if(len == 0){
        for(byte *b = buffer.get(); *b; b++){
            len++;
        }
    }
    int res = connect(sock, (const sockaddr *)&sadr, sizeof(sadr));
    if(res < 0){
        Logger::wrnf("Can't connect to server: %d", res);
    }else{
        Logger::logf("Successful connection");
        if(send(sock, buffer.get(), len, 0)<0){
            Logger::wrnf("Can't send message on server");
        }else{
            Logger::logf("Message successful sended");
        }
    }
    close(sock);
}