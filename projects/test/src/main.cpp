#include "Arg.h"
#include <memory>
#include <iostream>
int main(){
    int a = 34;
    Arg ar(Type::Int, (void *)&a);
    int c = 0;
    ar.getValue((void *)&c);
    std::cout<<c;
    return 0;
}