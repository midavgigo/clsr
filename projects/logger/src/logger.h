#ifndef __LOGGER_H__
#define __LOGGER_H__
#include <cstring>
#include "config.h"
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cstdarg>
#include <iostream>
#include <stdint.h>

//Перечисление типов формата
enum FormatTypes{
    Control     = '%',
    Decimal     = 'd',
    Hexadecimal = 'h',
    Float       = 'f',
    Char        = 'c',
    String      = 's'
};

typedef std::string log_error_t;

//Класс для записи логов
class Logger{
public:
    static void init();
    //Запись лога с помощью формата
    static void logf(const char * format...);
    //Запись лога с тегом о предупреждении
    static void wrnf(const char * format...);
    //Запись лога с выбросом ошибки
    static void errf(const char * format...);
private:
    //Обработка формата с переданными в одну из функций лога вариадическими параметрами
    static std::string fmt(const char * format, va_list factor);
    //Запсись в лог сообщения
    static void log(std::string message);
    /*
        @brief Получить префикс к логу
        @return Строка в виде времени и порядковому номеру лога 
    */
    static std::string getPrefix();
    static uint64_t         num_;   //Порядковый номер лога
    static std::string      fpath_; //Путь к файлу с логами
};

#endif