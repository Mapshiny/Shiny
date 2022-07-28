#ifndef _WIN32s

#include "PtrBuffer.h"


namespace shiny {

PtrBuffer::~PtrBuffer() {
    reset();
}

void PtrBuffer::reset() {
    _pos = 0;
    _size = 0;
    _capacity = 0;
    _pbuffer = nullptr;
}

void PtrBuffer::write(const void *data, size_t size) {
    if (size < 1 || data == nullptr)
        return;
    
    write(data, size, pos());
    seek(size, kSeekCur);
}

void PtrBuffer::write(const void *data, size_t size, const off_t& pos) {
    if (size < 1 || data == nullptr)
        return;
    
    size_t copylen = min(size, capacity() - pos);
    
    _size = max(_size, copylen + pos);
    
    memcpy((unsigned char*)ptr() + pos, data, size);
}


void PtrBuffer::attach(void* ptr, size_t size, size_t capacity) {
    reset();

    _pbuffer = (unsigned char*)ptr;
    _size = size;
    _capacity = capacity;
}


// void PtrBuffer::adjust(off_t nPos, size_t nSize) {
//     _size = _capacity < nSize ? _capacity : nSize;
//     seek(nPos, kSeekStart);
// }



}








#endif