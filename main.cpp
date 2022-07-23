#include "Logger.h"
#include <stdio.h>
#include <memory>
using namespace tlog;

int main() {
    Logger *logger1 = Logger::getLogger();
    Logger *logger2 = Logger::getLogger();
    
    if (logger1 == logger2) {
        printf("logger1 == logger2\n");
    } else {
        printf("logger1 != logger2\n");
    }


    std::unique_ptr<char> pbuffer(new char[1]);

    *pbuffer = 'a';
    *(pbuffer.get() + 1) = 'b';
    
    printf("%s\n", pbuffer.get());

    return 0;
}