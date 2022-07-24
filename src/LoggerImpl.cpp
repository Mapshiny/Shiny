#ifndef _WIN32

#include "LoggerImpl.h"


namespace shiny{

    const char* LoggerImpl::LOG_FILE_SUFFIX = ".shiny";

    Logger* Logger::getLogger() {
        static LoggerImpl logger;
        return &logger;
    }
    
    LoggerImpl::~LoggerImpl() {
    }


    void LoggerImpl::config(const std::string& logDir, const std::string& cacheDir, const std::string& logFileName, LogMode mode) {
        if (_isConfigured || logDir == "" || logFileName == "") {
            return;
        }
        
        _logDir = logDir;
        _mmapDir = cacheDir == "" ? logDir : cacheDir;
        _logname = logFileName;
        _logMode = mode;
        
        mkdir(_logDir.c_str(), 0755);
        mkdir(_mmapDir.c_str(), 0755);

        // memory map
        bool res = memoryMap();
        if (res) {
            _logBuffer = new LoggerBuffer(_logMmap.getPointer(), LOG_MEM_MAP_SIZE);
        } else {    // memory map failed, use memory buffer
            mode = LogSync;
            _logMemBufer = new char[LOG_MEM_MAP_SIZE];
            _logBuffer    = new LoggerBuffer(_logMemBufer, LOG_MEM_MAP_SIZE);
        }
        setLogMode(mode);

        _isConfigured = true;

    }


    void LoggerImpl::log(const std::string& data, const char *msg) {
        if (data == "" || msg == nullptr) {
            return;
        }

        if (openLogFile()) {
            write2file(data, data.size(), _logFile);

            bool tooMany = ftell(_logFile) > LOG_FILE_MAX_SIZE;
            if (_logMode == LogAsync && tooMany) {
                closeLogFile();
            }
            if (tooMany) {
                //TODO: rotate log file
            }
        }
        
    }

    void LoggerImpl::flush() {

    }
    void LoggerImpl::close() {

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
        if (info == nullptr && !_isConfigured) return;
        
        if (_logMode == LogAsync) {
            //TODO: async log
        } else {
            
        }

    }
    void LoggerImpl::logPrintf(LoggerInfo *info, const char *fmt, ...) {
        if (info == NULL) return;
    
    }

    void LoggerImpl::setConsoleOutput(bool enable) {
        _consoleOutput = enable;
    }

    
    bool LoggerImpl::memoryMap() {
        char map_file[256] = {0};
        snprintf(map_file, sizeof(map_file), "%s/%s.map", 
                _mmapDir.empty() ? _logDir.c_str() : _mmapDir.c_str(), _logname.c_str());

        _logMmap.mmap(map_file, LOG_MEM_MAP_SIZE);

        return _logMmap.getPointer() != NULL;

    }

    bool LoggerImpl::openLogFile() {
        std::unique_lock<std::mutex> lock_file(_logFilemutex);
        struct timeval tv;
        gettimeofday(&tv, NULL);

        time_t time_now = tv.tv_sec;
        tm tm_now = *localtime(&time_now);

        if (nullptr != _logFile) {
            tm tm_file = *localtime(&_openLogFileTime);

            if (tm_now.tm_year == tm_file.tm_year && tm_now.tm_mon == tm_file.tm_mon && tm_now.tm_mday == tm_file.tm_mday) {
                return true;
            }

            fclose(_logFile);
            _logFile = nullptr;
        }

        static char last_log_file[256] = {0};

        if (time_now < _openLogFileTime) {
            _openLogFileTime = time_now;
            _logFile = fopen(last_log_file, "ab");

            return nullptr != _logFile;
        }

        char log_file_name[256] = {0};
        snprintf(log_file_name, sizeof(log_file_name), "%s/%s_%04d%02d%02d.%s", 
                _logDir.c_str(), _logname.c_str(), tm_now.tm_year + 1900, tm_now.tm_mon + 1, tm_now.tm_mday, LOG_FILE_SUFFIX);
        
        _logFile = fopen(log_file_name, "ab");

        memcpy(last_log_file, log_file_name, sizeof(last_log_file));
        _openLogFileTime = time_now;

        return nullptr != _logFile;
    }
    
    void LoggerImpl::closeLogFile() {
        std::unique_lock<std::mutex> lock_file(_logFilemutex);
        if (nullptr != _logFile) {
            fclose(_logFile);
            _logFile = nullptr;
        }
    }

    bool LoggerImpl::write2file(const std::string& data, size_t size, FILE* file) {
        if (file == nullptr) {
            return false;
        }
        long offset = ftell(file);

        if (offset < 0)     return false;

        if (fwrite(data.c_str(), size, 1, file) != 1) {
            int err = ferror(file);

            ftruncate(fileno(file), offset);
            fseek(file, 0, SEEK_END);

            char err_msg[256] = {0};
            snprintf(err_msg, sizeof(err_msg), "write file failed, errno: %d", err);



            return false;
        }
        return true;
    }


}

#endif