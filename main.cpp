#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <vector>

#include <unistd.h>

#include "rilc_api.h"
#include "logger.h"

int main(int argc, char **argv)
{
    Logger::Init("RILC", Severity::DEBUG, false);

    if (argc >= 3)
    {
        setgid(atoi(argv[2]));
        setuid(atoi(argv[2]));
        LOGI << "try to switch user to radio: " << argv[2] << ENDL;
        LOGD << "after switch user UID\t= " << getuid() << ENDL;
        LOGD << "after switch user EUID\t= " << geteuid() << ENDL;
        LOGD << "after switch user GID\t= " << getgid() << ENDL;
        LOGD << "after switch user EGID\t= " << getegid() << ENDL;
    }

    RILC_init(argv[1]);
    LOGFI("main1");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    RILC_requestIMEI();

    LOGFI("main2");
    RILC_uninit();
    LOGFI("main3");

    return 0;
}
