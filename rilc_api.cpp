#include <thread>
#include <chrono>

#include "ril_request.h"
#include "logger.h"

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

int RILC_requestIMEI()
{
    RilRequest req;
    req.getIMEI();

    return 0;
}

int RILC_sendEnvelope(const char *cnt)
{
    RilRequest req;
    req.sendEnvelope(cnt);

    return 0;
}

int RILC_onUnsocial(void *)
{
    return 0;
}
