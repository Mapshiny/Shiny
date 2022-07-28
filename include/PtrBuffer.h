#ifndef _WIN32
#ifndef _PTRBUFFER_H
#define _PTRBUFFER_H

#include <string.h>

#include "./Interface/PtrController.h"


namespace shiny {

class PtrBuffer : public PtrController {
public:
    PtrBuffer() {}
    explicit PtrBuffer(void* _ptr, size_t _len) : PtrController(_ptr, _len) {}
    explicit PtrBuffer(void* _ptr, size_t _len, size_t _capacity) : PtrController(_ptr, _len, _capacity) {}

    ~PtrBuffer();
    PtrBuffer(const PtrBuffer& other) = delete;
    PtrBuffer& operator=(const PtrBuffer& other) = delete;

public:
    void write(const void *data, size_t size) override;
    void write(const void *data, size_t size, const off_t& pos);


    void attach(void* ptr, size_t size, size_t capacity) override;
    // void adjust(off_t nPos, size_t nSize);

private:
    void reset() override;

};

}
#endif
#endif