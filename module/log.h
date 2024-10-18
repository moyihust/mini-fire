#ifndef LOG_H
#define LOG_H

#include <linux/types.h> // for uint8_t

#define LOG_DEBUG 0
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERROR 3

void log_message(uint8_t level, const char *fmt, ...);

#endif // LOG_H