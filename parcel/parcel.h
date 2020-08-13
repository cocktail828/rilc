//create by bingjie.chen on 12-22-2018
#ifndef _PARCEL_H
#define _PARCEL_H
#include <sys/types.h>
#include "jstring.h"
#include <stdlib.h>
#include <endian.h>
#include <string.h>

//typedef char uint8_t;
typedef int32_t status_t;

#define NO_ERROR 0
#define NOT_ENOUGH_DATA 0x80000003
#define NO_MEMORY 12
#define PAD_SIZE(s) (((s) + 3) & ~3)
//#define INT32_MAX ((int32_t)(2147483647))

class Parcel
{
public:
    Parcel();

    ~Parcel();

    status_t setData(const uint8_t *buffer, size_t len);

    const uint8_t *data() const;

    size_t dataSize() const;

    size_t dataAvail() const;

    size_t dataPosition() const;

    size_t dataCapacity() const;

    status_t setDataSize(size_t size);

    void setDataPosition(size_t pos) const;

    status_t setDataCapacity(size_t size);

    template <class T>
    status_t readAligned(T *pArg) const;

    template <class T>
    T readAligned() const;

    //read interface
    status_t readInt(int32_t *pArg) const;

    int32_t readInt() const;

    void freeString(const char *str) const;

    const char *readString() const;

    const void *readInplace(size_t len) const;

    template <class T>
    status_t writeAligned(T val);

    //write interface
    status_t writeInt(int32_t val);

    status_t writeString(const char *str);

    void *writeInplace(size_t len);

private:
    status_t restartWrite(size_t desired);

    status_t continueWrite(size_t desired);

    status_t finishWrite(size_t len);

    status_t growData(size_t len);

    uint8_t *mData;

    size_t mDataSize;

    size_t mDataCapacity;

    mutable size_t mDataPos;
};

#endif