#include <thread>
#include <chrono>

#include "ril_request.h"
#include "logger.h"

int RILC_init(const char *device)
{
    const int max_try = 100;
    int try_time = 0;

    LINE;
    /* another thread is doing init? */
    if (!RILREQUEST::mGlobalLock.try_lock())
        return EBUSY;

    if (RILREQUEST::isReady())
    {
        RILREQUEST::mGlobalLock.unlock();
        return 0;
    }

    LINE;
    for (try_time = 0; try_time < max_try; try_time++)
    {
        LINE;
        if (RILREQUEST::instance().init(device))
            break;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    RILREQUEST::mGlobalLock.unlock();
    LOGI << "init seccussfully " << ENDL;
    return 0;
}

int RILC_uninit()
{
    if (!RILREQUEST::mGlobalLock.try_lock())
        return EBUSY;

    if (!RILREQUEST::isReady())
        return 0;

    int ret = RILREQUEST::uninit();
    RILREQUEST::mGlobalLock.unlock();
    return ret;
}

int RILC_requestIMSI()
{
    RilRequest *req = new RilRequest();

    req->getIMSI(new RilResponse());

    return 0;
}

int RILC_onUnsocial(void *)
{
    return 0;
}
