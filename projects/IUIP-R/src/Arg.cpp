#include "Arg.h"

Arg::Arg(Type t, void *v):t_(t), v_({v}){

}

void Arg::getValue(void *v){
    void *ptr = nullptr;
    switch(t_){
        case Type::Str:
            std::strcpy((char *)v, (char *)v_.get());
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

Arg::Arg(mindex ind_size, message raw, mindex &shift){
    mindex offset = 0;
    for(mindex i = 0; i < ind_size; i++){
        byte el = *(raw.get()+offset);
        t_ <<= sizeof(byte)*8;
        t_ += el;
        offset++;
    }
    switch(t_){
        case Type::Str:
            std::strcpy((char *)v, (char *)(raw.get()+offset));
            offset+=std::strlen(v);
            break;
        default:
            if(t_ < Type::TYPES_COUNT){
                std::memcpy(v, (void *)raw.get()+offset, TYPE_SIZES[t_]);
                offset+=TYPE_SIZES[t_];
            }else{
                Logger::wrnf("Argument have unknown type");
            }  
    }
    shift += offset;
}