#ifndef _LOGIMPL_H
#define _LOGIMPL_H

#ifndef _WIN32

#include <string.h>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <memory>
#include <fcntl.h>
#include <sys/stat.h>

#include "Logger.h"
#include "LoggerMmap.h"
#include "LoggerBuffer.h"

namespace shiny {

    class LoggerImpl : public Logger {
        public:
            LoggerImpl() : _isOpened(false), _logLevel(LOG_DEBUG), _logMode(LogAsync), _logMmap(), _logBufferPtr(nullptr), _logBuffer(nullptr) {};
            virtual ~LoggerImpl();

            virtual void logOpen(const char *logDir, const char* mmapDir, const char *logName, LogMode mode) override;
            virtual void log(LoggerInfo *info, const char *msg) override; 
            virtual void setLogMode(LogMode mode) override;

            virtual void setLogLevel(LogLevel level) override;
            virtual void setLogLevel(const char *level) override;
            virtual void setLogLevel(int level) override;
            virtual LogLevel getLogLevel() override;

            virtual void logPrint(LoggerInfo *info, const char *msg) override;
            virtual void logPrintf(LoggerInfo *info, const char *fmt, ...) override;

        public:
            static const unsigned int LOG_MEM_MAP_SIZE = 1024 * 150;
            static const unsigned int LOG_FILE_MAX_SIZE = 1024 * 1024 * 10;
            static const char* LOG_FILE_SUFFIX;
        private:
            bool memoryMap();

        private:
            std::string _logDir;
            std::string _mmapDir;
            std::string _logname;

            bool _isOpened;

            LogLevel _logLevel;
            LogMode _logMode;

            LoggerMmap _logMmap;
            
            char *_logBufferPtr;
            LoggerBuffer *_logBuffer;

            std::condition_variable _logcondition;
            std::mutex _logmutex;
    };
}






#endif
#endif