#ifndef _WIN32
#ifndef _PTRBUFFER_H
#define _PTRBUFFER_H


#include "./Interface/PtrController.h"


namespace shiny {

class PtrBuffer : public PtrController {
public:
    PtrBuffer() {}
    explicit PtrBuffer(void* _ptr, size_t _len, size_t _maxlen) : PtrController() {}
    explicit PtrBuffer(void* _ptr, size_t _len) : PtrController() {}

    ~PtrBuffer() {}
    PtrBuffer(const PtrBuffer& other) = delete;
    PtrBuffer& operator=(const PtrBuffer& other) = delete;

public:
    void attach(void* ptr, size_t size);
    void attach(void* ptr, size_t size, size_t capacity);
    void length(off_t nPos, size_t nSize);

private:
    void reset() override;

};

}
#endif
#endif