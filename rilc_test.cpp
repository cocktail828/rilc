#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <vector>

#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "rilc_api.h"
#include "rilc_interface.h"
#include "logger.h"

std::mutex mutex;
std::condition_variable cond;

void socilited_notify(RILResponse *arg)
{
    cond.notify_one();
    LOGI << "RILC call user defined socilited_notify function" << ENDL;
}

void unsocilited_notify(void *arg)
{
    cond.notify_one();
    LOGI << "RILC call user defined unsocilited_notify function" << ENDL;
}

static int sg_index = 0;
/**
 * will call std::abort() if get an timeout
 */
#define RILC_TEST_ABORT_TIMEOUT(func, args...)                                                   \
    do                                                                                           \
    {                                                                                            \
        LOGI << ">>>>>>>> RILC_TEST index: " << ++sg_index << ENDL;                              \
        RILResponse resp;                                                                        \
        memset(&resp, 0, sizeof(RILResponse));                                                   \
        resp.responseNotify = socilited_notify;                                                  \
        std::unique_lock<std::mutex> _lk(mutex);                                                 \
        func(&resp, ##args);                                                                     \
        if (cond.wait_for(_lk, std::chrono::seconds(60)) == std::cv_status::timeout)             \
        {                                                                                        \
            LOGI << ">>>>>>>> RILC_TEST index: " << sg_index << " failed for timeout" << ENDL;   \
            LOGE << "OOPS!!! request timeout" << ENDL;                                           \
            LOGE << "check wether host can get response from device" << ENDL;                    \
            std::abort();                                                                        \
        }                                                                                        \
        else                                                                                     \
        {                                                                                        \
            if (resp.responseShow)                                                               \
                resp.responseShow(&resp);                                                        \
            if (resp.responseFree)                                                               \
                resp.responseFree(&resp);                                                        \
            LOGI << ">>>>>>>> RILC_TEST index: " << sg_index << " pass" << ENDL;                 \
        }                                                                                        \
        _lk.unlock();                                                                            \
        LOGI << ">>>>>>>> RILC_TEST index: " << sg_index << " finished" << ENDL << ENDL << ENDL; \
    } while (0);

int main(int argc, char **argv)
{
    static const struct option long_options[] = {
        {"device", required_argument, NULL, 'd'},
        {"mode", required_argument, NULL, 'm'},
        {"platform", required_argument, NULL, 'p'},
        {"level", required_argument, NULL, 'l'},
        {NULL, 0, NULL, 0}};

    const char *device = "/dev/ttyUSB4";
    Severity s = Severity::DEBUG;

    /**
     * 0 Linux
     * 1 Android
     */
    int platform = 0;

    /**
     * 0 abort if timeout
     * 1 abort if response report an error
     */
    int test_mode = 0;

    int long_index = 0;
    int opt;
    while ((opt = getopt_long(argc, argv, "d:m:p:l:?h", long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'd':
            device = optarg;
            LOGI << "using device: " << device << ENDL;
            break;
        case 'm':
            test_mode = !!atoi(optarg);
            LOGI << "using test mode: " << test_mode << ENDL;
            break;
        case 'p':
            if (optarg && !strncasecmp(optarg, "linux", 4))
                platform = 0;
            else if (optarg && !strncasecmp(optarg, "android", 4))
                platform = 1;
            LOGI << "using platform: " << (platform ? "Android" : "Linux") << ENDL;
            break;
        case 'l':
            if (optarg && !strncasecmp(optarg, "debug", 4))
                s = Severity::DEBUG;
            else if (optarg && !strncasecmp(optarg, "info", 4))
                s = Severity::INFO;
            else if (optarg && !strncasecmp(optarg, "warn", 4))
                s = Severity::WARNING;
            else if (optarg && !strncasecmp(optarg, "error", 4))
                s = Severity::ERROR;
            else
                s = Severity::INFO;
            break;
        default:
            LOGI << "help message:" << ENDL;
            LOGI << "  -d, --device            ttydevice or socket" << ENDL;
            LOGI << "  -m, --mode              test mode(0 stop test if meet a timeout, 1 stop test if meet an error)" << ENDL;
            LOGI << "  -p, --platform          os platform(0 for Linux, 1 for Android)" << ENDL;
            LOGI << "  -l, --level             log level(debug, info, warning, error)" << ENDL;
            return 0;
        }
    }

    if (access(device, R_OK | W_OK))
    {
        LOGE << "invalid device: " << device << ENDL;
        return 0;
    }
    /**
     * set log level Severity::INFO
     * for more detail set Severity::DEBUG
     */
    Logger::Init("RILC", s, false);

    /** test on Android
     * Android only allow user radio connect socket '/dev/socket/rild'
     */
    if (platform == 1)
    {
        setgid(1001);
        setuid(1001);
        LOGI << "try to switch user to radio: id 1001" << ENDL;
        LOGD << "after switch user UID\t= " << getuid() << ENDL;
        LOGD << "after switch user EUID\t= " << geteuid() << ENDL;
        LOGD << "after switch user GID\t= " << getgid() << ENDL;
        LOGD << "after switch user EGID\t= " << getegid() << ENDL;
    }

    /** test on Linux with RG500U
     * Android only allow user radio connect socket '/dev/socket/rild'
     */
    if (device)
        RILC_init(device);
    else
    {
        if (platform == 1)
            RILC_init("/dev/socket/rild");
        else
            RILC_init("/dev/ttyUSB4");
    }

    // RILC_TEST_ABORT_TIMEOUT(RILC_getIMEI);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getIMEISV);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getIMSI);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getVoiceRegistrationState);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getDataRegistrationState);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getOperator);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getNeighboringCids);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getSignalStrength);

    // RILC_TEST_ABORT_TIMEOUT(RILC_getPreferredNetworkType);

    // RILC_TEST_ABORT_TIMEOUT(RILC_setPreferredNetworkType, RADIO_TECHNOLOGY_LTE);

    // RILC_TEST_ABORT_TIMEOUT(RILC_setupDataCall, RADIO_TECHNOLOGY_LTE, "0", "3gnet",
    //                         "", "", SETUP_DATA_AUTH_NONE, PROTOCOL_IPV4);

    RILC_TEST_ABORT_TIMEOUT(RILC_getIccCardStatus);

    RILC_TEST_ABORT_TIMEOUT(RILC_getCurrentCalls);

    RILC_TEST_ABORT_TIMEOUT(RILC_getNetworkSelectionMode);

    RILC_TEST_ABORT_TIMEOUT(RILC_getDataCallList);

    RILC_TEST_ABORT_TIMEOUT(RILC_getBasebandVersion);

    RILC_TEST_ABORT_TIMEOUT(RILC_queryAvailableBandMode);

    RILC_uninit();

    return 0;
}
