#ifndef _WIN32


#include "AutoBuffer.h"

namespace shiny {

AutoBuffer::~AutoBuffer() {}

void AutoBuffer::alloc(size_t _readyToWrite, bool _changeSize) {
    size_t len = pos() + _readyToWrite;
    fitBuffer(len);     //TODO: catch exception
    if (_changeSize)
        _size = std::max(_size, len);
}

void AutoBuffer::addCapacity(size_t _addCapacity) {
    fitBuffer(size() + _addCapacity);   //TODO: catch exception
}

void AutoBuffer::fitBuffer(size_t size) throw(std::bad_alloc) {
    if (size > capacity()) {
        size_t mallocSize = ( (size + unit_size - 1) / unit_size ) * unit_size;
        void* p = realloc(_pbuffer, mallocSize);
        if (p == nullptr) {
            free(_pbuffer);
            //TODO: roll back
            throw std::bad_alloc();
        }
        
        _pbuffer = (unsigned char*)p;

        memset(_pbuffer + _capacity, 0, mallocSize - _capacity);
        _capacity = mallocSize;
    }
}

void AutoBuffer::write(const void *data, size_t size) {
    if (size < 1 || data == nullptr)
        return;
    
    write(pos(), data, size);
    seek(size, kSeekCur);
}

void AutoBuffer::write(const off_t& pos, const void *data, size_t size) {
    if (size < 1 || data == nullptr)
        return;
    
    fitBuffer(size + pos);
    
    _size = std::max(_size, pos + size);

    memcpy((unsigned char*)ptr() + pos, data, size);
}


void AutoBuffer::reset() {
    if (_pbuffer != nullptr) {
        free(_pbuffer);
    }
    _pos = 0;
    _size = 0;
    _capacity = 0;
    _pbuffer = nullptr;
}

}

#endif