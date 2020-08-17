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
    virtual int get_requestid() = 0;
    virtual int get_commandid() = 0;
};

class ISubject
{
private:
    std::mutex mListLock;

protected:
    std::vector<IObserver *> mObservers;

public:
    void attach(IObserver *o)
    {
        std::lock_guard<std::mutex> _lk(mListLock);
        LOGD << "attach new observer: sn "
             << o->get_requestid() << " cid "
             << o->get_commandid() << ENDL;
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
                     << o->get_requestid()
                     << " cid " << o->get_commandid() << ENDL;
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
            LOGD << "removing observer: sn " << o->get_requestid() << ENDL;
            o->update(p);
        }

        mObservers.clear();
        LOGD << "removing all observers finished" << ENDL;
    }
};

#endif //__ISUBJECTOBSERVER
