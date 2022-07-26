#include "Interface/Logger.h"
#include <stdio.h>
#include <memory>
#include <iostream>

int main() {
    shiny::Logger *logger = shiny::Logger::getLogger();
    
    logger->config("./logdir", "./mmapdir", "logtest", shiny::LogSync);

    logger->logPrint(nullptr, "hello world");

    return 0;
}