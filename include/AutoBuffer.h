#ifndef _AUTO_BUFFER_H
#define _AUTO_BUFFER_H

#ifndef _WIN32

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "./Interface/PtrController.h"

namespace shiny {

class AutoBuffer : public PtrController {

public:
    explicit AutoBuffer(size_t size = 128) : unit_size(size) {}
    explicit AutoBuffer(void* _pbuffer, size_t _len, size_t _nSize) : unit_size (_nSize) {
        // TODO: attach();
    }
    
    ~AutoBuffer();

    void alloc(size_t _readyToWrite, bool _changeSize = true);
    void addCapacity(size_t _addCapacity);

    void fitBuffer(size_t size) throw(std::bad_alloc);

public:
    void write(const void *data, size_t size) override;
    void write(const void *data, size_t size, const off_t& pos);

    void attach(void* ptr, size_t size, size_t capacity) override;

private:
    void reset() override;

private:
    size_t unit_size;
};

}

#endif
#endif