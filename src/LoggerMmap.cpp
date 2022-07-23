#include "LoggerMmap.h"



LoggerMmap::~LoggerMmap() {
    if (_ptr != nullptr) {
        munmap();
    }
}

void LoggerMmap::mmap(size_t size, int prot, int flags, int fd, off_t offset) {
    _ptr = ::mmap(nullptr, size, prot, flags, fd, offset);
    if (_ptr == MAP_FAILED) {
        _ptr = nullptr;
        _size = 0;
    } else {
        _size = size;
    }
}

void LoggerMmap::mmap(const char *file, size_t length) {
    int fd = open(file, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        if (errno == EEXIST) {
            fd = open(file, O_RDWR | O_EXCL);
            if (fd == -1) {
                _ptr = nullptr;
                _size = 0;
                return;
            }
        } else {
            _ptr = nullptr;
            _size = 0;
            return;
        }
    }

    lseek(fd, length - 1, SEEK_SET);
    write(fd, "\0", 1);

    _ptr = ::mmap(nullptr, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (fd != -1) {
        close(fd);
    }

    if (_ptr == MAP_FAILED) {
        _ptr = nullptr;
        _size = 0;
    } else {
        _size = length;
    }
    
}

void LoggerMmap::munmap() {
    if (_ptr == nullptr)    return;
    int ret = ::munmap(_ptr, _size);
    if (ret == 0) {
        _ptr = nullptr;
        _size = 0;
    }
}

void LoggerMmap::msync(bool Sync) {
    if (_ptr == nullptr)    return;

    int flag = Sync ? MS_SYNC : MS_ASYNC;
    int ret = ::msync(_ptr, _size, flag | MS_INVALIDATE);

}

void LoggerMmap::madvise(int advice) {
}
void LoggerMmap::mlock(void *ptr, size_t size) {
}
void LoggerMmap::munlock(void *ptr, size_t size) {

}
void LoggerMmap::mlockall(int flags) {
}
void LoggerMmap::munlockall() {
}

void* LoggerMmap::getPointer() const {
    return _ptr;
}
size_t LoggerMmap::getSize() const {
    return _size;
}
void LoggerMmap::setOwns(bool owns) {
    _is_owns = owns;
}