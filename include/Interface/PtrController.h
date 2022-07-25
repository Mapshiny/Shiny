#ifndef _WIN32
#ifndef _PTRCONTROLLER_H
#define _PTRCONTROLLER_H

#include <sys/types.h>

namespace shiny {

class PtrController {
public:
    enum Seek {
        kSeekStart,
        kSeekCur,
        kSeekEnd,
    };
public:
    explicit PtrController(size_t size = 128) : _size(size), _capacity(size), _pos(0), _buffer(nullptr) {}
    explicit PtrController(void *buffer, size_t size = 128) 
        : _size(size), _capacity(size), _pos(0), _buffer((unsigned char*)buffer) {}
    PtrController(const PtrController& other) = delete;
    PtrController& operator=(const PtrController& other) = delete;
    virtual ~PtrController() { if (_buffer) delete(_buffer); }

public:
    void seek(off_t nOffset, Seek eOrigin) {
        switch (eOrigin) {
        case kSeekStart:
            _pos = nOffset;
            break;
        case kSeekCur:
            _pos += nOffset;
            break;
        case kSeekEnd:
            _pos = _capacity - nOffset;
            break;
        default:
            break;
        }

        if (_pos < 0) _pos = 0;
        if ((unsigned int)_pos > _capacity) _pos = _capacity;
    }

    void length(off_t nPos, size_t nSize) {
        _size = _capacity < nSize ? _capacity : nSize;
        seek(nPos, kSeekStart);
    }

public:
    void *ptr() const { return _buffer; }
    off_t pos() const { return _pos; }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    
protected:
    unsigned char *_buffer;
    off_t _pos;
    size_t _size;
    size_t _capacity;
};



}


#endif
#endif