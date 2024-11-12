#ifndef __ARG_H__
#define __ARG_H__
#include <memory>
#include "logger.h"
#include <cstring>

enum Type{
    Int = 0,
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
    Arg(Type t);
    Arg(const Arg &arg);
    void copyValue(const void *v);
    void getValue(void *v);
    Type getType();
    Arg(mindex ind_size, const void * raw, mindex &shift);
    size_t getSize();
private:
    Type t_;
    buffer_t v_;
};
#endif