#ifndef _WIN32


#include "AutoBuffer.h"

namespace shiny {

AutoBuffer::~AutoBuffer() {}

void AutoBuffer::allocWrite(size_t _readyToWrite, bool _changeSize) {
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
        void* p = realloc(_buffer, mallocSize);
        if (p == nullptr) {
            free(_buffer);
            //TODO: roll back
            throw std::bad_alloc();
        }
        
        _buffer = (unsigned char*)p;

        memset(_buffer + _capacity, 0, mallocSize - _capacity);
        _capacity = mallocSize;
    }
}

void AutoBuffer::write(const void *data, size_t size) {
    if (size < 1 || data == nullptr)
        return;
    
    write(pos(), data, size);
}

void AutoBuffer::write(const off_t& pos, const void *data, size_t size) {
    if (size < 1 || data == nullptr)
        return;
    
    fitBuffer(size + pos);
    
    _size = std::max(_size, pos + size);

    memcpy(ptr() + pos, data, size);
}

void* AutoBuffer::ptr(off_t offset) const { return _buffer + offset; }

off_t AutoBuffer::pos() const { return _pos; }

size_t AutoBuffer::size() const { return _size; }

size_t AutoBuffer::capacity() const { return _capacity; }




}

#endif