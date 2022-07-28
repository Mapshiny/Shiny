#ifndef _TLOG_H
#define _TLOG_H

#ifndef _WIN32

#include <time.h>
#include <stdint.h>
#include <string>


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
        const char *tag = nullptr;
        const char *file_name = nullptr;
        // int line;
        LoggerInfo_t(LogLevel level, const char *file_name) : level(level), timev(), thread_id(0), process_id(0){};
    } LoggerInfo;

    enum LogMode {
        LogAsync,
        LogSync
    };

    class Logger {
    public:

        static Logger *getLogger();

        virtual ~Logger() {};
        virtual void config(const std::string& logDir, const std::string& cacheDir, const std::string& logFileName, LogMode mode) = 0;
        virtual void log(const std::string& data) = 0;

        virtual void flush() = 0;
        virtual void close() = 0;

        virtual void setLogMode(LogMode mode) = 0;
        virtual void setLogLevel(LogLevel level) = 0;
        virtual void setLogLevel(const char *level) = 0;
        virtual void setLogLevel(int level) = 0;
        virtual LogLevel getLogLevel() = 0;

        virtual void logPrint(LoggerInfo &info, const char *msg) = 0;
        virtual void logPrintf(LoggerInfo &info, const char *fmt, ...) = 0;

        virtual void setConsoleOutput(bool enable) = 0;
    };
}


#endif
#endif