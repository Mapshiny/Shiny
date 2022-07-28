#ifndef _WIN32
#ifndef _PTRCONTROLLER_H
#define _PTRCONTROLLER_H

#include <sys/types.h>

namespace shiny {

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

class PtrController {
public:
    enum Seek {
        kSeekStart,
        kSeekCur,
        kSeekEnd,
    };
protected:
    explicit PtrController() : _pbuffer(nullptr), _pos(0), _size(0), _capacity(0) {}
    explicit PtrController(void* ptr, size_t len) : _pbuffer((unsigned char*)ptr), _pos(0), _size(0), _capacity(len) {} 
    explicit PtrController(void* ptr, size_t len, size_t capcity) : _pbuffer((unsigned char*)ptr), _pos(0), _size(len), _capacity(capcity) {} 


    PtrController(const PtrController& other) = delete;
    PtrController& operator=(const PtrController& other) = delete;

    virtual ~PtrController() {}

public:
    void writeErr(const char *const _val) { write(_val, (unsigned int) strlen(_val));}
    virtual void write(const void* data, size_t len) = 0;

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

    void adjust(off_t nPos, size_t nSize) {
        _size = _capacity < nSize ? _capacity : nSize;
        seek(nPos, kSeekStart);
    }
    
    virtual void attach(void *ptr, size_t len, size_t capacity) = 0;

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