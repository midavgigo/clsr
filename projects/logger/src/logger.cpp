#include "logger.h"

std::string Logger::fpath_ = "";
long long Logger::num_ = 0;

void Logger::init(){
    std::time_t now = std::time(nullptr);
    std::tm *tm_now = std::localtime(&now);
    char buf[18];
    fpath_ = CMAKE_LOG_PATH;
    std::strftime(buf, sizeof(buf), "/%Y-%m-%d.log", tm_now);
    fpath_ += std::string(buf);
}

std::string Logger::getPrefix(){
    std::time_t now = std::time(nullptr);
    std::tm *tm_now = std::localtime(&now);
    char buf[24];
    std::strftime(buf, sizeof(buf), ":[%Y-%m-%d %H:%M:%S]: ", tm_now);
    return std::to_string(num_)+std::string(buf);
}

void Logger::log(std::string message){
    if(CMAKE_BUILD_TYPE == "DEBUG"){
        std::cout<<message<<"\n";
    }
    std::fstream out(fpath_, std::fstream::out);
    if(out.is_open()){
        out << message << "\n";
    }
    out.close();
    num_++;
}

std::string Logger::fmt(const char * format, va_list factor){
    std::string ret;
    for(const char * cptr = format; *cptr; cptr++){
        char c = *cptr;
        int d = 0;
        if(c != '%'){
            ret += c;
        }else{
            cptr++;
            c = *cptr;
            switch(c){
                case FormatTypes::Control:
                    ret+=c;
                    break;
                case FormatTypes::Decimal:
                    ret += std::to_string(va_arg(factor, int));
                    break;
                case FormatTypes::Hexadecimal:
                    d = va_arg(factor, unsigned int);
                    ret += "00000000";
                    for(int i = 1; i < 9; i++){
                        char cym[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
                        ret[ret.size()-i] = cym[d%8];
                        d >>= 4;
                    }
                    break;
                case FormatTypes::Float:
                    ret += std::to_string(va_arg(factor, float));
                    break;
                case FormatTypes::Char:
                    ret+=va_arg(factor, char);
                    break;
                case FormatTypes::String:
                    ret += std::string(va_arg(factor, const char *));
                    break;
            }
        }
    }
    va_end(factor);
    return ret;
}

void Logger::logf(const char * format, ...){
    va_list factor;
    va_start(factor, format);
    log(getPrefix()+fmt(format, factor));
}

void Logger::wrnf(const char *format, ...){
    va_list factor;
    va_start(factor, format);
    log(getPrefix()+" [WARNING] "+fmt(format, factor));
}

void Logger::errf(const char *format, ...){
    va_list factor;
    va_start(factor, format);
    log(getPrefix()+" [ERROR] "+fmt(format, factor));
}