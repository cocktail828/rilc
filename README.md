# rilc
A simple SDK writen in c++, that can communicate with RILD of Android

## Framework

### DeviceManager

`DeviceManager` will manager the ttydevice/socket. Anyone that will be used for communicate with RILD.

```
class DeviceManager final : public ISubject
{
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;
...
};
```

`DeviceManager` will start a new thread and polling any response via `epoll` from the file handle, that is managed. If any response (socilited/unsocilited) message was received, `DeviceManager` will call `processResponse` to notify the observer.



## RilRequest

```c++

class RilRequest final : public IObserver
{
private:
    /* class variables */
    static DeviceManager *mDeviceMgr;
    static int mGlobalRequestId;
    static bool mReady;

public:
    static std::mutex mGlobalLock;
    static const int RIL_MAX_COMMAND_BYTES = (8 * 1024);
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;
...
};
```



`RilRequest` is the real worker for every request. Before all the job starts, user should call `RILC_init` to do some init works, including 'start new polling thread in the background', 'init the class variables'.



## RIlResponse

// TODO

```c++

```

