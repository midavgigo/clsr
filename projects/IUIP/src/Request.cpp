#include "Request.h"


Request::Request(IUIP_version v):v_(v){}

bool checkMask(const byte * a, const byte * b, mindex len){
    for(mindex i = 0; i < len; i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}


bool Request::parse(buffer_t raw){    
    bool res = checkMask(IUIP_LABEL, raw.get(), 6);
    if(!res){
        Logger::wrnf("IUIP-label isn't recognized. Messages parsing is interrupted");
        return false;
    }
    mindex offset = 6;
    res = checkMask(IUIP_VERS, raw.get()+offset, 4);
    mindex ind_size = 0;
    if(res){
        offset += 4;
        std::memcpy(&v_, raw.get()+offset, 1);
        offset++;
        ind_size = IUIP_IND_SIZE[v_];
    }else{
        Logger::wrnf("The version is not specified, the value of the zero version is set");
        ind_size = IUIP_IND_SIZE[IUIP_version::INDEV];
    }
    mindex cmd_count = 0;
    std::memcpy(&cmd_count, raw.get()+offset, 1);
    offset++;
    if((int16_t)cmd_count < 0){
        Logger::wrnf("Error in command count reading");
        return false;
    }
    for(mindex i = 0; i < cmd_count; i++){
        byte cmd_b;
        args_t args;
        std::memcpy(&cmd_b, raw.get()+offset, ind_size);
        Command cmd = (Command)cmd_b;
        offset += ind_size;
        if(cmd >= Command::COMMANDS_COUNT || cmd < 0){
            Logger::wrnf("Parsed command type are'nt recognized");
            return false;
        }
        commands_.emplace_back(cmd, args_t());
        for(size_t i = 0; i < COMMAND_TYPES[cmd].size(); i++){
            Arg a(ind_size, raw.get()+offset, offset);
            if(a.getType() >= Type::TYPES_COUNT || a.getType() < 0){
                Logger::wrnf("Parsed argument type are'nt recognized: %d", a.getType());
                return false;
            }
            if(a.getType() != COMMAND_TYPES[cmd][i]){
                Logger::wrnf("Parsed argument type have wrong type: %d");
                return false;
            }
            commands_[commands_.size()-1].second.push_back(a);
        }
    }
    return true;
}

void Request::pushCmd(cmd_arg_t cmd){
    commands_.push_back(cmd);
}

cmd_list_t Request::getCommands(){
    return commands_;
}

size_t Request::getMessageSize(){
    size_t ret = 6;                             //Для метки протокола
    byte ind_size = IUIP_IND_SIZE[v_];
    ret += (v_ == IUIP_version::INDEV ? 0 : 5); //Для метки версии и указанной версии
    ret += 1;                                   //Для количества комманд
    for(cmd_arg_t cmd : commands_){
        ret+=ind_size;                          //Для команды
        for(Arg arg : cmd.second){
            ret+=ind_size;                      //Для указания типа
            ret+= arg.getSize();                //Для размера
        }
    }
    return ret;
}

size_t Request::getMessage(buffer_t &buf){
    size_t message_len = getMessageSize();
    buffer_t ret(new byte[message_len]);
    mindex offset = 0;
    std::memcpy(ret.get(), IUIP_LABEL, 6);
    offset += 6;
    if(v_ != IUIP_version::INDEV){
        std::memcpy(ret.get()+offset, IUIP_VERS, 4);
        offset+=4;
        std::memcpy(ret.get()+offset, &v_, 1);
        offset++;
    }
    byte count = (byte)commands_.size();
    std::memcpy(ret.get()+offset, &count, 1);
    offset++;
    for(cmd_arg_t cmd : commands_){
        std::memcpy(ret.get()+offset, &cmd.first, 1);
        offset++;
        for(Arg arg : cmd.second){
            Type t = arg.getType();
            std::memcpy(ret.get()+offset, &t, 1);
            offset++;
            arg.getValue(ret.get()+offset);
            offset += arg.getSize();
        }
    }
    buf = move(ret);
    return message_len;
}