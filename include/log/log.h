#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
extern FILE* InitLog(const char* path, bool is_print_log);
extern int CloseLog();
extern int LOG(const char *format, ...);
#endif