#ifndef _LogController_H
#define _LogController_H

#ifndef _WIN32

#include <sys/types.h>
#include <memory>
#include <mutex>
#include <string>

#include "AutoBuffer.h"

namespace shiny {

class LogController {
public:
    LogController(bool compress = true);
    ~LogController();
    
public:
    bool write(const std::string& data, size_t inputSize);
    bool write(const std::string& data, size_t inputSize, AutoBuffer &output);
    void setCompress(bool enabled);

private:
    bool reset();
    void clear();

private:
    std::mutex _logControllerMutex;

    bool _compress;

};

}
#endif
#endif