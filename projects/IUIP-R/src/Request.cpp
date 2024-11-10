#include "Request.h"


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
        offset += 4;
        byte version = *(raw.get()+offset);
        offset++;
        ind_size = IUIP_IND_SIZE[version];
    }else{
        Logger::wrnf("The version is not specified, the value of the zero version is set");
        ind_size = IUIP_IND_SIZE[IUIP_VERSION::INDEV];
    }
    mindex cmd_count = 0;
    for(mindex i = 0; i < ind_size; i++){
        byte el = *(raw.get()+offset);
        cmd_count <<= sizeof(byte)*8;
        cmd_count += el;
        offset++;
    }
    for(mindex i = 0; i < cmd_count; i++){
        Command cmd;
        args_t args;
        for(mindex j = 0; j < ind_size; j++){
            byte el = *(raw.get()+offset);
            cmd <<= sizeof(byte)*8;
            cmd += el;
            offset++;
        }
        if(cmd >= Command::COMMANDS_COUNT){
            Logger::wrnf("Parsed command type are'nt recognized");
            return false;
        }
        Arg a(ind_size, raw.get()+offset, offset);
        if(a.getType() >= Type::TYPES_COUNT){
            Logger::wrnf("Parsed argument type are'nt recognized: %d", a.getType());
            return false;
        }

    }
}