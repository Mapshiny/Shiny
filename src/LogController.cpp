#ifndef _WIN32

#include "LogController.h"

namespace shiny {

LogController::LogController(bool compress) : _compress(compress) {
}

LogController::~LogController() {
}

bool LogController::write(const std::string& data, size_t inputSize) {
    return false;
}

bool LogController::write(const std::string& data, size_t inputSize, AutoBuffer &output) {
    if (inputSize < 1 || data == "")    return false;

    output.allocWrite(inputSize);

    output.write(data.c_str(), inputSize);
    
}


void LogController::setCompress(bool enabled) {
    _compress = enabled;
}



}

#endif