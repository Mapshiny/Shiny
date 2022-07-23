#ifndef _TLOG_H
#define _TLOG_H

#ifndef _WIN32

#include <time.h>
#include <stdint.h>



namespace shiny {

    typedef enum {
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,
        LOG_FATAL
    } LogLevel;
    
    typedef struct LoggerInfo_t {
        LogLevel level;
        struct timeval timev;
        int64_t thread_id;
        int64_t process_id;
        const char *name;
        const char *file;
        int line;
        LoggerInfo_t(LogLevel level, const char *name, const char *file, int line) : level(level), timev(), thread_id(0), process_id(0), name(name), file(file), line(line) {};
    } LoggerInfo;

    enum LogMode {
        LogAsync,
        LogSync
    };

    class Logger {
    public:

        static Logger *getLogger();

        virtual ~Logger() {};
        virtual void logOpen(const char *logdir, const char* mmapDir, const char *logname, LogMode mode) = 0;
        virtual void log(LoggerInfo *info, const char *msg) = 0;
        virtual void setLogMode(LogMode mode) = 0;

        virtual void setLogLevel(LogLevel level) = 0;
        virtual void setLogLevel(const char *level) = 0;
        virtual void setLogLevel(int level) = 0;
        virtual LogLevel getLogLevel() = 0;

        virtual void logPrint(LoggerInfo *info, const char *msg) = 0;
        virtual void logPrintf(LoggerInfo *info, const char *fmt, ...) = 0;
    };
}


#endif
#endif