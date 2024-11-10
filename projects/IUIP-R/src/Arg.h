#ifndef __ARG_H__
#define __ARG_H__
#include <memory>
#include "logger.h"
#include <cstring>

enum Type{
    Int,
    Flt,
    Str,
    TYPES_COUNT
};

const mindex TYPE_SIZES[] = {
    sizeof(int32_t),
    sizeof(float),
    sizeof(char)
};

class Arg{
public:
    Arg(Type t, void* v);
    //~Arg();
    void getValue(void *v);
    Type getType();
    Arg(mindex ind_size, message raw);
private:
    Type t_;
    message v_;
};
#endif