#ifndef _AUTO_BUFFER_H
#define _AUTO_BUFFER_H

#ifndef _WIN32

#include <sys/types.h>



namespace shiny {

class AutoBuffer {

public:
    explicit AutoBuffer(size_t size = 128);
    explicit AutoBuffer(void *buffer, size_t size = 128);
    ~AutoBuffer();

private:
    unsigned char *_buffer;
    off_t _pos;
    size_t _size;
    size_t _capacity;
};

}




#endif
#endif