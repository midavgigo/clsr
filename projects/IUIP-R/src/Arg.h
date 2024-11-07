#ifndef __ARG_H__
#define __ARG_H__
#include <memory>

enum Type{
    Int,
    Flt,
    Str
};

class Arg{
public:
    Arg(Type t, void* v);
    ~Arg();
    void getValue(void *v);
    Type getType();
private:
    Type t_;
    void *v_;
};
#endif