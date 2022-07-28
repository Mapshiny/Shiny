#ifndef _WIN32

#include "LogController.h"

namespace shiny {


LogController::~LogController() {
}

void LogController::flush(AutoBuffer& buff) {
    std::unique_lock<std::mutex> lock(_logControllerMutex);

    if (_ptrBuffer.size() > 0) {
        buff.write(_ptrBuffer.ptr(), _ptrBuffer.size());
    }
    
    clear();
}

bool LogController::write(const char* data, size_t inputSize) {
    return false;
}

bool LogController::write(const char* data, size_t inputSize, AutoBuffer &buffer) {
    if (inputSize < 1 || data == "")    return false;

    buffer.alloc(inputSize);
    buffer.write(data, inputSize);
    
    return true;
}


void LogController::setCompress(bool enabled) {
    _compress = enabled;
}

void LogController::clear() {
    memset(_ptrBuffer.ptr(), 0, _ptrBuffer.capacity());
    _ptrBuffer.adjust(0, 0);   
}


}

#endif