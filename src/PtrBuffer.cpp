#ifndef _WIN32s

#include "PtrBuffer.h"


namespace shiny {

void PtrBuffer::reset() {
    _pos = 0;
    _size = 0;
    _capacity = 0;
    _pbuffer = nullptr;
}


void PtrBuffer::attach(void* ptr, size_t size) {
    attach(ptr, size, size);
}


void PtrBuffer::attach(void* ptr, size_t size, size_t capacity) {
    reset();

    _pbuffer = (unsigned char*)ptr;
    _size = size;
    _capacity = capacity;
}


void PtrBuffer::length(off_t nPos, size_t nSize) {
    _size = _capacity < nSize ? _capacity : nSize;
    seek(nPos, kSeekStart);
}



}








#endif