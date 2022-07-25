#ifndef _WIN32
#ifndef _PTRBUFFER_H
#define _PTRBUFFER_H

#include <sys/types.h>
#include "PtrController.h"


namespace shiny {

class PtrBuffer : public PtrController {

public:
    explicit PtrBuffer(size_t size = 128) : PtrController(size) {}
    explicit PtrBuffer(void *buffer, size_t size = 128) : PtrController(buffer, size) {}

    ~PtrBuffer() {}
    PtrBuffer(const PtrBuffer& other) = delete;
    PtrBuffer& operator=(const PtrBuffer& other) = delete;

};

}
#endif
#endif