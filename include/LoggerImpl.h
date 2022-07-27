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
#include <sys/time.h>
#include <string>

#include "./Interface/Logger.h"
#include "LoggerMmap.h"
#include "LogController.h"

namespace shiny {

class LoggerImpl : public Logger {
public:
    LoggerImpl() : _isConfigured(false), _consoleOutput(false), _logLevel(LOG_DEBUG), 
                    _logMode(LogAsync), _logMmap(), _logMemBufer(nullptr), _logController(nullptr) {};
    virtual ~LoggerImpl(){};

    virtual void config(const std::string& logDir, const std::string& cacheDir, const std::string& logFileName, LogMode mode) override;

    virtual void log(const std::string& data)  override; 

    virtual void flush() override;
    virtual void close() override;

    virtual void setLogMode(LogMode mode) override;
    virtual void setLogLevel(LogLevel level) override;
    virtual void setLogLevel(const char *level) override;
    virtual void setLogLevel(int level) override;
    virtual LogLevel getLogLevel() override;

    virtual void logPrint(LoggerInfo *info, const char *msg) override;
    virtual void logPrintf(LoggerInfo *info, const char *fmt, ...) override;

    virtual void setConsoleOutput(bool enable) override;

public:
    void logFormat(const LoggerInfo &_info, const char *_logbody, PtrBuffer &_buff);
    

public:
    static const unsigned int LOG_MEM_MAP_SIZE = 1024 * 150;
    static const unsigned int LOG_FILE_MAX_SIZE = 1024 * 1024 * 10;
    static const char* LOG_FILE_SUFFIX;

private:
    bool memoryMap();
    bool openLogFile();
    void closeLogFile();
    
    void log2file(const void* data, size_t size);

    void writeTips2File(const char* tips);
    bool write2File(const char* data, size_t size, FILE* file);
private:
    std::string _logDir;
    std::string _mmapDir;
    std::string _logname;

    FILE *_logFile;
    time_t _openLogFileTime;

    bool _isConfigured;
    bool _consoleOutput;

    LogLevel _logLevel;
    LogMode _logMode;

    LoggerMmap _logMmap;
    
    char *_logMemBufer;
    LogController *_logController;

    std::condition_variable _logcondition;
    std::mutex _logFilemutex;
};

}



#endif
#endif