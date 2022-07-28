#include "Interface/Logger.h"
#include <stdio.h>
#include <memory>
#include <iostream>
#include <unistd.h>

int main() {
    shiny::Logger *logger = shiny::Logger::getLogger();
    
    logger->config("./logdir", "./mmapdir", "logtest", shiny::LogSync);
    logger->setConsoleOutput(true);

    shiny::LoggerInfo info(shiny::LOG_DEBUG, "testfilename");
    int i = 0;
    while (i++ < 10) {
        logger->logPrint(info, "this is a log!");
        // sleep(1);
    }
    
    // logger->logPrint(nullptr, "hello world");

    return 0;
}