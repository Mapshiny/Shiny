#ifndef _WIN32

#include "LoggerImpl.h"


namespace shiny{

    const char* LoggerImpl::LOG_FILE_SUFFIX = "shiny";

    Logger* Logger::getLogger() {
        static LoggerImpl logger;
        return &logger;
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
            printf("memory map success\n");
            _logController = new LogController(_logMmap.getPointer(), LOG_MEM_MAP_SIZE);
        } else {    // memory map failed, use memory buffer
            mode = LogSync;
            _logMemBufer = new char[LOG_MEM_MAP_SIZE];
            _logController = new LogController(_logMemBufer, LOG_MEM_MAP_SIZE);
        }
        setLogMode(mode);

        AutoBuffer buffer;
        _logController->flush(buffer);

        if (buffer.ptr()) {
            writeTips2File("~~~~~cache begin~~~~~\n");
            log2file(buffer.ptr(), buffer.size());
            writeTips2File("~~~~~cache end~~~~~\n");
        }

        _isConfigured = true;

    }


    void LoggerImpl::log(const std::string& data) {
        if (data == "" || !_isConfigured)   return;

        if (openLogFile()) {
            write2File(data.c_str(), data.size(), _logFile);

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
        
        if (_consoleOutput) {
            printf("%s\n", msg);
        }

        char* p = (char*)_logMmap.getPointer();
        char test[] = "test";
        memcpy(p, test, 4);

        ::munmap(p, 4);

        /*
        if (_logMode == LogAsync) {
            //TODO: async log
        } else {
            AutoBuffer buffer;
            if (_logController->write("test", 4, buffer)) {
                log2file((char *)buffer.ptr(), buffer.size());
            }
        }
        */

    }
    void LoggerImpl::logPrintf(LoggerInfo *info, const char *fmt, ...) {
        if (info == NULL) return;
    
    }

    void LoggerImpl::setConsoleOutput(bool enable) {
        _consoleOutput = enable;
    }

    
    bool LoggerImpl::memoryMap() {
        char map_file[256] = {0};
        snprintf(map_file, sizeof(map_file), "%s/%s.text", 
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

    void LoggerImpl::log2file(const void* data, size_t size) {
        if (data == nullptr || size == 0) return;

        if (openLogFile()) {
            write2File((char *)data, size, _logFile);
        }
    }

    void LoggerImpl::writeTips2File(const char* tips) {
        if (tips == nullptr) return;

        AutoBuffer buffer;
        _logController->write(tips, strlen(tips), buffer);

        if (buffer.ptr()) {
            log2file(buffer.ptr(), buffer.size());
        }
    }
    

    bool LoggerImpl::write2File(const char* data, size_t size, FILE* file) {
        if (file == nullptr || data == nullptr) {
            return false;
        }
        long offset = ftell(file);

        if (offset < 0)     return false;

        if (fwrite(data, size, 1, file) != 1) {
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