#ifndef _AUTO_BUFFER_H
#define _AUTO_BUFFER_H

#ifndef _WIN32

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


namespace shiny {

class AutoBuffer {

public:
    explicit AutoBuffer(size_t size = 128) : _size(size), _capacity(size), _pos(0), _buffer(nullptr) {}
    explicit AutoBuffer(void *buffer, size_t size = 128) 
        : _size(size), _capacity(size), _pos(0), _buffer((unsigned char*)buffer) {}
    
    ~AutoBuffer();

    void allocWrite(size_t _readyToWrite, bool _changeSize = true);
    void addCapacity(size_t _addCapacity);

    void fitBuffer(size_t size) throw(std::bad_alloc);

public:
    template <class T>
    void write(const T& data) {
        write(&data, sizeof(T));
    }

    void write(const void *data, size_t size);
    void write(const off_t& pos, const void *data, size_t size);
public:
    void* ptr(off_t offset = 0) const { return _buffer + offset; }
    off_t pos() const { return _pos; }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    
private:
    unsigned char *_buffer;

    off_t _pos;
    size_t _size;
    size_t unit_size;
    size_t _capacity;
};

}

#endif
#endif