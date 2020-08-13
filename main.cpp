#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <vector>

#include "rilc_api.h"
#include "logger.h"

int main()
{
    LOGFI("main1");
    RILC_init("/dev/ttyUSB0");
    LOGFI("main2");

    std::this_thread::sleep_for(std::chrono::seconds(3));
    RILC_uninit();
    LOGFI("main3");

    return 0;
}
