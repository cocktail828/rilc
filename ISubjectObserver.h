#ifndef __ISUBJECTOBSERVER
#define __ISUBJECTOBSERVER

#include <mutex>
#include <condition_variable>
#include <vector>

#include "parcel/parcel.h"
#include "logger.h"

class IObserver
{
protected:
    std::mutex mLock;
    std::condition_variable mCond;

public:
    IObserver() {}
    virtual ~IObserver() {}
    virtual void update(Parcel &p) = 0;
    virtual int getRequestId() = 0;
    virtual int getCommandId() = 0;
};

// TODO, distinguish sync/async requests
class ISubject
{
private:
    std::mutex mListLock;
    std::vector<IObserver *> mObservers;
    const size_t mMaxSize = 10;

public:
    void attach(IObserver *o)
    {
        std::lock_guard<std::mutex> _lk(mListLock);
        LOGD << "attach new observer: sn "
             << o->getRequestId() << " cid "
             << o->getCommandId() << ENDL;
        mObservers.emplace_back(o);
    }

    void detach(IObserver *o)
    {
        std::lock_guard<std::mutex> _lk(mListLock);
        for (auto iter = mObservers.begin(); iter != mObservers.end();)
        {
            if ((*iter) == o)
            {
                LOGD << "detach observer(" + std::to_string(mObservers.size()) + ") sn "
                     << o->getRequestId()
                     << " cid " << o->getCommandId() << ENDL;
                mObservers.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    void detachAll()
    {
        std::lock_guard<std::mutex> _lk(mListLock);
        /* notice all the ovservers the quit event */

        LOGD << "removing all observers" << ENDL;
        for (auto o : mObservers)
        {
            Parcel p;
            LOGD << "removing observer: sn " << o->getRequestId() << ENDL;
            o->update(p);
        }

        mObservers.clear();
        LOGD << "removing all observers finished" << ENDL;
    }

    void notify(int rid, Parcel &p)
    {
        std::lock_guard<std::mutex> _lk(mListLock);

        LOGD << "try to find and notify observer, rid " << rid << ENDL;
        for (auto iter = mObservers.begin(); iter != mObservers.end();)
        {
            IObserver *o = *iter;
            if (o->getRequestId() == rid)
            {
                o->update(p);
                mObservers.erase(iter);
            }
        }
    }

    bool isListFull()
    {
        std::lock_guard<std::mutex> _lk(mListLock);
        return (mObservers.size() >= mMaxSize);
    }
};

#endif //__ISUBJECTOBSERVER
