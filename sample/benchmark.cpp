#include "../include/Interface/Logger.h"
#include <stdio.h>
#include <memory>
#include <iostream>
#include <unistd.h>

using namespace shiny;

int main() {
#pragma region Shiny
    Logger *logger = shiny::Logger::getLogger();
    
    logger->config("./logdir", "./mmapdir", "logtest", shiny::LogSync);
    logger->setConsoleOutput(false);

    shiny::LoggerInfo info(shiny::LOG_DEBUG, "testfilename");
    int i = 0;
    clock_t start = clock();
    while (i++ < 10000) {
        logger->logPrint(info, "this is a log!");
        ++i;
    }
    clock_t end = clock();
    std::cout << "Shiny log2File time: " << (end - start) / (double)CLOCKS_PER_SEC << "ms" << std::endl;

#pragma endregion

#pragma region WriteFile
    FILE *fp = fopen("./logdir/logtest.log", "w");
    if (fp == NULL) {
        std::cout << "open file error" << std::endl;
        return -1;
    }
    i = 0;
    start = clock();
    while (i++ < 10000) {
        fwrite("this is a log!\n", sizeof("this is a log!\n"), 1, fp);

    }
    end = clock();
    std::cout << "time: " << (end - start) / (double)CLOCKS_PER_SEC << std::endl;
    fclose(fp);
#pragma endregion
}