#ifndef _LOGGERBUFFER_H
#define _LOGGERBUFFER_H

#ifndef _WIN32

#include <sys/types.h>
#include <memory>


class LoggerBuffer {
public:
    LoggerBuffer(void *pbuffer, size_t size, bool compress = true);
    ~LoggerBuffer();
    
public:
    void *getBuffer();
    size_t getSize();
    bool isCompress();
    
private:
    bool reset();
    void clear();

private:
    size_t _size;
    size_t _capacity;
    void *_pbuffer;
    bool _compress;

};


#endif
#endif