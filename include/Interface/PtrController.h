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
protected:
    explicit PtrController() : _pbuffer(nullptr), _pos(0), _size(0), _capacity(0) {}
    explicit PtrController(void* ptr, size_t len) : _pbuffer((unsigned char*)ptr), _pos(0), _size(len), _capacity(len) {} 
    explicit PtrController(void* ptr, size_t len, size_t capcity) : _pbuffer((unsigned char*)ptr), _pos(0), _size(len), _capacity(capcity) {} 


    PtrController(const PtrController& other) = delete;
    PtrController& operator=(const PtrController& other) = delete;

    virtual ~PtrController() { if (_pbuffer) delete(_pbuffer); }

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
    void *ptr() const { return _pbuffer; }
    off_t pos() const { return _pos; }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

protected:
    virtual void reset() = 0;

protected:
    unsigned char *_pbuffer;
    off_t _pos;
    size_t _size;
    size_t _capacity;
};



}


#endif
#endif