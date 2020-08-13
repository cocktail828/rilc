// #include "ril-client.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <vector>

// #include "rilc_api.h"
#include "logger.h"

class xx
{
    int x;

public:
    operator int()
    {
        return 10;
    }
};

int main()
{

    xx x;
    LOGI << int(x) << ENDL;
    return 0;

    // LOGFI("main1");
    // RILC_init("/dev/ttyUSB0");
    // LOGFI("main2");

    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // RILC_uninit();
    // LOGFI("main3");

    return 0;
}
