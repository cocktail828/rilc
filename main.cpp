#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <vector>

#include <unistd.h>
#include <string.h>

#include "rilc_api.h"
#include "rilc_interface.h"
#include "logger.h"

std::mutex mutex;
std::condition_variable cond;

void socilited_notify(void *arg)
{
    cond.notify_one();
    LOGI << "RILC call user defined socilited_notify function" << ENDL;
}

void unsocilited_notify(void *arg)
{
    cond.notify_one();
    LOGI << "RILC call user defined unsocilited_notify function" << ENDL;
}

void dump_response(RILResponse *resp)
{
    if (resp->error_code)
    {
        LOGI << "GET RESPONSE: error code = " << resp->error_code << ENDL;
    }
    else
    {
        switch (resp->type)
        {
        case TYPE_INT:
            LOGI << "GET RESPONSE: " << resp->response_data.value_int << ENDL;
            break;
        case TYPE_STRING:
            LOGI << "GET RESPONSE: " << resp->response_data.value_string << ENDL;
            break;
        case TYPE_INT_ARR:
        {
            LOGI << "data num: " << resp->response_data.array.num << ENDL;
            int *data = (int *)resp->response_data.array.data;
            for (int i = 0; i < resp->response_data.array.num; i++)
                LOGI << "data[" << i << "]: " << data[i] << ENDL;
            break;
        }
        case TYPE_STRING_ARR:
        {
            LOGI << "data num: " << resp->response_data.array.num << ENDL;
            const char **data = (const char **)resp->response_data.array.data;
            for (int i = 0; i < resp->response_data.array.num; i++)
                LOGI << "data[" << i << "]: " << (data[i] ? data[i] : "null") << ENDL;
            break;
        }
        default:
            LOGI << "do it yourself" << ENDL;
            break;
        }
    }
}

#define RILC_DO_COMMAND(RILC_func, args...)                                         \
    do                                                                              \
    {                                                                               \
        RILResponse resp;                                                           \
        memset(&resp, 0, sizeof(RILResponse));                                      \
        resp.notify = socilited_notify;                                             \
        std::unique_lock<std::mutex> _lk(mutex);                                    \
        RILC_func(&resp, ##args);                                                   \
        if (cond.wait_for(_lk, std::chrono::seconds(5)) == std::cv_status::timeout) \
            LOGE << "TIMEOUT" << ENDL;                                              \
        else                                                                        \
        {                                                                           \
            dump_response(&resp);                                                   \
        }                                                                           \
        _lk.unlock();                                                               \
    } while (0);

int main(int argc, char **argv)
{
    /**
     * set log level Severity::INFO
     * for more detail set Severity::DEBUG
     */
    Logger::Init("RILC", Severity::DEBUG, false);

    /** test on Android
     * Android only allow user radio connect socket '/dev/socket/rild'
     */
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

    /** test on Linux with RG500U
     * Android only allow user radio connect socket '/dev/socket/rild'
     */
    if (argc > 1)
        RILC_init(argv[1]);
    else
        RILC_init("/dev/ttyUSB4");

    RILC_DO_COMMAND(RILC_getIMEI);

    // RILC_DO_COMMAND(RILC_getIMSI);

    // RILC_DO_COMMAND(RILC_getVoiceRegistrationState);

    // RILC_DO_COMMAND(RILC_getDataRegistrationState);

    // RILC_DO_COMMAND(RILC_getOperator);

    // RILC_DO_COMMAND(RILC_getNeighboringCids);

    // RILC_DO_COMMAND(RILC_getSignalStrength);

    // RILC_DO_COMMAND(RILC_setPreferredNetworkType, RADIO_TECHNOLOGY_LTE);

    RILC_DO_COMMAND(RILC_setupDataCall, RADIO_TECHNOLOGY_LTE, "0", "3gnet",
                    "user", "1234", SETUP_DATA_AUTH_NONE, PROTOCOL_IPV4);

    // RILC_DO_COMMAND(RILC_queryAvailableBandMode);

    RILC_uninit();

    return 0;
}
