#ifndef _LOGGERMEM_H
#define _LOGGERMEM_H

#ifndef _WIN32

#include <sys/mman.h>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>


class LoggerMmap {
public:
    LoggerMmap() : _is_mapped(false), _ptr(nullptr), _size(0) {};
    ~LoggerMmap();
    
    void mmap(size_t size, int prot, int flags, int fd, off_t offset = 0);
    void mmap(const char *file, size_t length);
    void munmap();
    void msync(bool Sync);

    void madvise(int advice);
    void mlock(void *ptr, size_t size);
    void munlock(void *ptr, size_t size);
    void mlockall(int flags);
    void munlockall();

    void* getPointer() const;
    size_t getSize() const;
    // void setIsMmap(bool owns);


protected:
    bool _is_mapped;
    void *_ptr;
    size_t _size;
};


#endif
#endif