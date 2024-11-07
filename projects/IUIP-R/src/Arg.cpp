#include "Arg.h"

Arg::Arg(Type t, void * v):t_(t), v_(v){

}

void Arg::getValue(void *v){
    void *ptr = nullptr;
    switch(t_){
        case Type::Int:
            *(int *)v = *(int *)(v_);
            break;
        case Type::Flt:
            *(float *)v = *(float *)(v_);
            break;
        case Type::Str:
            char *d = (char *)v;
            char *s = (char *)v_;
            for(;*s; d++,s++){
                *d = *s;
            }
            break;
    }
}

Type Arg::getType(){
    return t_;
}