#include "Interface/Logger.h"
#include <stdio.h>
#include <memory>
#include <iostream>
#include <unistd.h>

int main() {
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

    return 0;
}