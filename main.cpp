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

    if (argc > 1)
        RILC_init(argv[1]);
    else
        RILC_init("/dev/ttyUSB4");

    RILC_TEST_REQ();

    RILC_uninit();

    return 0;
}
