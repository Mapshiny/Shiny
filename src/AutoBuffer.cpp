#ifndef _WIN32


#include "AutoBuffer.h"
namespace shiny {

    AutoBuffer::AutoBuffer(size_t size = 128) {}
    AutoBuffer::AutoBuffer(void *buffer, size_t size = 128) {}
    AutoBuffer::~AutoBuffer() {}

}

#endif