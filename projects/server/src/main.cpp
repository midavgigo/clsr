#include <iostream>
#include "logger.h"

int main(){
    Logger::init();
    Logger::logf("U menya ochko vot takoy shiriny %d", 22);
}