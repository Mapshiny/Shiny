#ifndef _WIN32

#include "LoggerBuffer.h"


LoggerBuffer::LoggerBuffer(void *pbuffer, size_t size, bool compress) : _size(size), _capacity(size), _compress(compress), _pbuffer(pbuffer) {
}

LoggerBuffer::~LoggerBuffer() {
}




#endif