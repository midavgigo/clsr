#include "Arg.h"

Arg::Arg(Type t):t_(t){
    v_ = buffer(new byte[TYPE_SIZES[t_]]);
}

Arg::Arg(const Arg &arg):t_(arg.t_){
    v_ = buffer(new byte[TYPE_SIZES[t_]]);
    copyValue(arg.v_.get());
}
void Arg::copyValue(const void * v){
    switch(t_){
        case Type::Str:
            v_ = buffer(new byte[std::strlen((const char *)v)+1]);
            std::strncpy((char *)v_.get(), (char *)v, std::strlen((const char *)v)+1);
            break;
        default:
            std::memcpy(v_.get(), v, TYPE_SIZES[t_]);
    }
}

void Arg::getValue(void *v){
    void *ptr = nullptr;
    switch(t_){
        case Type::Str:
            std::strncpy((char *)v, (char *)v_.get(), getSize());
            break;
        default:
            if(t_ < Type::TYPES_COUNT){
                std::memcpy(v, (void *)v_.get(), TYPE_SIZES[t_]);
            }else{
                Logger::wrnf("Unknown type, copy nothing");
            }    
    }
}

Type Arg::getType(){
    return t_;
}

Arg::Arg(mindex ind_size, const void * raw, mindex &shift){
    mindex offset = 0;
    byte type;
    std::memcpy(&type, raw+offset, ind_size);
    offset+=ind_size;
    t_ = Type(type);
    switch(t_){
        case Type::Str:
            v_ = buffer(new byte[std::strlen((char *)(raw+offset))+1]);
            std::strcpy(v_.get(), (char *)(raw+offset));
            offset+=getSize();
            break;
        default:
            v_ = buffer(new byte[TYPE_SIZES[t_]]);
            if(t_ < Type::TYPES_COUNT){
                std::memcpy(v_.get(), raw+offset, TYPE_SIZES[t_]);
                offset+=TYPE_SIZES[t_];
            }else{
                Logger::wrnf("Argument have unknown type");
            }  
    }
    shift += offset;
}

size_t Arg::getSize(){
    switch(t_){
        case Type::Str:
            return std::strlen((const char *)v_.get())+1;
            break;
        default:
            return TYPE_SIZES[t_];
    }
}