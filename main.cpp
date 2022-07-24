#include "Logger.h"
#include <stdio.h>
#include <memory>
#include <iostream>

int main() {
    shiny::Logger *logger = shiny::Logger::getLogger();
    
    std::cout << logger->getLogLevel() << std::endl;
    
    logger->setLogLevel(shiny::LOG_FATAL);
    std::cout << logger->getLogLevel() << std::endl;

    logger->config("./logdir", "./mmapdir", "logtest", shiny::LogSync);

    std::cout << sizeof(bool) << std::endl;

    return 0;
}