#include <thread>
#include <chrono>
#include <cassert>

#include "ril_request.h"
#include "rilc_api.h"
#include "logger.h"

#define NULLSTR(str) (str == NULL ? "" : str)

int RILC_init(const char *device)
{
    const int max_try = 30;
    int try_time = 0;

    /* another thread is doing init? */
    if (!RILREQUEST::mGlobalLock.try_lock())
        return EBUSY;

    if (RILREQUEST::isReady())
    {
        RILREQUEST::mGlobalLock.unlock();
        return 0;
    }

    for (try_time = 0; try_time < max_try; try_time++)
    {
        if (RILREQUEST::instance().init(device))
            break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        LOGI << "start polling thread fail, times = " << try_time << ENDL;
    }

    bool ret = RILREQUEST::instance().isReady();
    if (ret)
    {
        LOGI << "init seccussfully " << ENDL;
    }
    else
    {
        LOGI << "init failed " << ENDL;
    }

    RILREQUEST::mGlobalLock.unlock();

    return ret;
}

int RILC_uninit()
{
    if (!RILREQUEST::mGlobalLock.try_lock())
        return EBUSY;

    if (!RILREQUEST::isReady())
    {
        RILREQUEST::mGlobalLock.unlock();
        return 0;
    }

    int ret = RILREQUEST::uninit();
    RILREQUEST::mGlobalLock.unlock();
    return ret;
}

int RILC_getIMEI(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getIMEI())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_getSignalStrength(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getSignalStrength())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_getIMSI(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getIMSI())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_getVoiceRegistrationState(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getVoiceRegistrationState())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_getDataRegistrationState(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getDataRegistrationState())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_getOperator(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getOperator())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_getNeighboringCids(RILResponse *resp)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->getNeighboringCids())
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_setupDataCall(RILResponse *resp, RadioTech radioTechnology, const char *profile, const char *apn,
                       const char *user, const char *password, RadioAuth authType, RadioProtocol protocol)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);

    const char *ip_protocol[] = {
        [0] = "IP",
        [1] = "IPV6",
        [2] = "IPV4V6",
    };

    const char *proto = ip_protocol[protocol];
    if (req->setupDataCall(std::to_string(radioTechnology).c_str(),
                           NULLSTR(profile),
                           NULLSTR(apn),
                           NULLSTR(user),
                           NULLSTR(password),
                           std::to_string(authType).c_str(),
                           proto))
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_setPreferredNetworkType(RILResponse *resp, RadioTech networktype)
{
    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->setPreferredNetworkType(networktype))
    {
        delete req;
        return -1;
    }
    return 0;
}

int RILC_queryAvailableBandMode(RILResponse *resp)
{

    if (!resp)
        LOGW << __func__ << " is called without response parameter" << ENDL;

    clock_gettime(CLOCK_MONOTONIC, &(resp->start_time));
    RILRequest *req = new (std::nothrow) RILRequest(resp);
    if (req->queryAvailableBandMode())
    {
        delete req;
        return -1;
    }
    return 0;
}