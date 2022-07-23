#ifndef _WIN32

#include "LoggerImpl.h"


namespace tlog{

    const char* LoggerImpl::LOG_FILE_SUFFIX = ".shiny";

    Logger* Logger::getLogger() {
        static LoggerImpl logger;
        return &logger;
    }
    
    LoggerImpl::~LoggerImpl() {
    }


    void LoggerImpl::logOpen(const char *logDir, const char* mmapDir, const char *logName, LogMode mode) {
        if (_isOpened || logDir == nullptr || logName == nullptr) {
            return;
        }
        
        _logDir = logDir;
        _mmapDir = mmapDir == nullptr ? logDir : mmapDir;
        _logname = logName;
        _logMode = mode;
        
        mkdir(_logDir.c_str(), 0755);
        mkdir(_mmapDir.c_str(), 0755);

        // memory map
        bool res = memoryMap();
        if (res) {

        } else {    // memory map failed, use memory buffer
            mode = LogSync;
            _logBufferPtr = new char[LOG_MEM_MAP_SIZE];
            _logBuffer    = new LoggerBuffer(_logBufferPtr, LOG_MEM_MAP_SIZE);
        }
        setLogMode(mode);

            

        
    }


    void LoggerImpl::log(LoggerInfo *info, const char *msg) {
        
    }

    void LoggerImpl::setLogMode(LogMode mode) {
        _logMode = mode;
    }

    void LoggerImpl::setLogLevel(LogLevel level) {
        _logLevel = level;
    }
    void LoggerImpl::setLogLevel(const char *level) {
        if (level == NULL) return;

        if (strcmp(level, "debug") == 0) {
            _logLevel = LOG_DEBUG;
        } else if (strcmp(level, "info") == 0) {
            _logLevel = LOG_INFO;
        } else if (strcmp(level, "warning") == 0) {
            _logLevel = LOG_WARNING;
        } else if (strcmp(level, "error") == 0) {
            _logLevel = LOG_ERROR;
        } else if (strcmp(level, "fatal") == 0) {
            _logLevel = LOG_FATAL;
        }
    }
    void LoggerImpl::setLogLevel(int level) {
        if (level == 0) {
            _logLevel = LOG_DEBUG;
        } else if (level == 1) {
            _logLevel = LOG_INFO;
        } else if (level == 2) {
            _logLevel = LOG_WARNING;
        } else if (level == 3) {
            _logLevel = LOG_ERROR;
        } else if (level == 4) {
            _logLevel = LOG_FATAL;
        }
    }
    LogLevel LoggerImpl::getLogLevel() {
        return _logLevel;
    }

    void LoggerImpl::logPrint(LoggerInfo *info, const char *msg) {
        if (info == NULL) return;
        
        if (info->level >= _logLevel) {
            log(info, msg);
        }

    }
    void LoggerImpl::logPrintf(LoggerInfo *info, const char *fmt, ...) {
        if (info == NULL) return;
    
    }

    bool LoggerImpl::memoryMap() {
        char map_file[256] = {0};
        snprintf(map_file, sizeof(map_file), "%s/%s.map", 
                _mmapDir.empty() ? _logDir.c_str() : _mmapDir.c_str(), _logname.c_str());

        size_t LOG_MAP_SIZE = 1024 * 1024 * 1024;
        _logMmap.mmap(map_file, LOG_MAP_SIZE);

        return _logMmap.getPointer() != NULL;

    }

}

#endif