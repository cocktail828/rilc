#ifndef __ISUBJECTOBSERVER
#define __ISUBJECTOBSERVER

#include <mutex>
#include <condition_variable>
#include <vector>

#include "parcel/parcel.h"

class IObserver
{
protected:
    std::mutex mLock;
    std::condition_variable mCond;

public:
    IObserver() {}
    virtual ~IObserver() {}
    virtual void update(void *data) = 0;
    virtual int get_requestid() = 0;
    virtual int get_commandid() = 0;
};

class ISubject
{
protected:
    std::vector<IObserver *> mObservers;

public:
    virtual void processResponse(void *data, size_t len) = 0;

    void attach(IObserver *o)
    {
        mObservers.emplace_back(o);
    }

    void detach(IObserver *o)
    {
        for (auto iter = mObservers.begin();
             iter != mObservers.end(); iter++)
        {
            if ((*iter) == o)
                mObservers.erase(iter);
        }
    }
};

#endif //__ISUBJECTOBSERVER