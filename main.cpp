#include <stdio.h>
#include <memory>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include "Interface/Logger.h"
#include "zip/zipHelper.h"


int main() {

    const char* src = "this is a message!";
    char dest[100];
    size_t size = 100;
    shiny::compressMem(dest, &size, src, strlen(src));

    std::cout << dest << std::endl;
    std::cout << size << std::endl;
    char dest2[100];
    size_t size2 = 100;
    shiny::decompressMem(dest2, &size2, dest, size);
    std::cout << dest2 << std::endl;

    /*
    shiny::Logger *logger = shiny::Logger::getLogger();
    
    logger->config("./logdir", "./mmapdir", "logtest", shiny::LogSync);
    logger->setConsoleOutput(false);

    shiny::LoggerInfo info(shiny::LOG_DEBUG, "testfilename");
    int i = 0;
    clock_t start = clock();
    while (i < 100) {
        logger->logPrint(info, "this is a log!");
        // sleep(1);
        ++i;
    }
    clock_t end = clock();
    std::cout << "time: " << (end - start) / (double)CLOCKS_PER_SEC << std::endl;
    */
    return 0;
}