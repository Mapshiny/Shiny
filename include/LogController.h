#ifndef _LogController_H
#define _LogController_H

#ifndef _WIN32

#include <sys/types.h>
#include <memory>
#include <mutex>
#include <string>

#include "AutoBuffer.h"
#include "PtrBuffer.h"

namespace shiny {

class LogController {
public:
    LogController(void *pbuffer, size_t len, bool compress = true) : _compress(compress){
        _ptrBuffer.attach(pbuffer, 0, len);
    }
    ~LogController();
    
public:
    void flush(AutoBuffer& buff);
    bool write(const std::string& data, size_t inputSize);
    bool write(const std::string& data, size_t inputSize, AutoBuffer &output);

    void setCompress(bool enabled);

private:
    bool reset();
    void clear();

private:
    std::mutex _logControllerMutex;

    PtrBuffer _ptrBuffer;
    
    bool _compress;

};

}
#endif
#endif