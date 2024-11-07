#include "Request.h"

Request::Request(Command cmd):cmd_(cmd){
}

Request::Request(){}

bool checkMask(std::unique_ptr<byte> a, std::unique_ptr<byte> b, mindex len){
    for(mindex i = 0; i < len; i++){
        if(a.get()[i] != b.get()[i]){
            return false;
        }
    }
    return true;
}

#define BPTR(a) std::make_unique<byte>(a)

bool Request::parse(std::unique_ptr<byte> raw){
    bool res = checkMask(BPTR(IUIP_LABEL), BPTR(raw.get()), 4);
    if(!res){
        Logger::wrnf("IUIP-label isn't recognized. Messages parsing is interrupted");
        return false;
    }
    mindex offset = 4;
    res = checkMask(BPTR(IUIP_VERS), BPTR(raw.get()+offset), 4);
    mindex ind_size = 0;
    if(res){
        offset += 5;
        byte version = *(raw.get()+offset);
        ind_size = IUIP_IND_SIZE[version];
    }else{
        Logger::wrnf("The version is not specified, the value of the zero version is set");
        ind_size = IUIP_IND_SIZE[IUIP_VERSION::INDEV];
    }
    
}