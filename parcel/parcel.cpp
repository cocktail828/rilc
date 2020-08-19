#include "parcel.h"
#include "jstring.h"

#define SIZE_T_MAX (0xffffffff)

static size_t pad_size(size_t s)
{
    if (s > (SIZE_T_MAX - 3))
    {
        abort();
    }
    return PAD_SIZE_UNSAFE(s);
}

Parcel::Parcel()
{
    mData = NULL;
    mDataSize = 0;
    mDataCapacity = 0;
    mDataPos = 0;
}

Parcel::~Parcel()
{
    if (mData != NULL)
    {
        free(mData);
    }
}

void Parcel::recycle()
{
    if (mData)
        free(mData);

    mData = NULL;
    mDataSize = 0;
    mDataCapacity = 0;
    mDataPos = 0;
}

const uint8_t *Parcel::data() const
{
    return mData;
}

status_t Parcel::setData(const uint8_t *buffer, size_t len)
{
    status_t err = restartWrite(len);
    if (err == NO_ERROR)
    {
        memcpy(const_cast<uint8_t *>(data()), buffer, len);
        mDataSize = len;
    }
    return err;
}

size_t Parcel::dataSize() const
{
    return (mDataSize > mDataPos ? mDataSize : mDataPos);
}

size_t Parcel::dataAvail() const
{
    return dataSize() - dataPosition();
}

size_t Parcel::dataPosition() const
{
    return mDataPos;
}

size_t Parcel::dataCapacity() const
{
    return mDataCapacity;
}

status_t Parcel::setDataSize(size_t size)
{
    status_t err;
    err = continueWrite(size);
    if (err == NO_ERROR)
    {
        mDataSize = size;
    }
    return err;
}

void Parcel::setDataPosition(size_t pos) const
{
    mDataPos = pos;
}

status_t Parcel::setDataCapacity(size_t size)
{
    if (size > mDataCapacity)
        return continueWrite(size);
    return NO_ERROR;
}

status_t Parcel::restartWrite(size_t desired)
{
    uint8_t *data = (uint8_t *)realloc(mData, desired);
    if (!data && desired > mDataCapacity)
    {
        //mError = NO_MEMORY;
        return NO_MEMORY;
    }

    if (data)
    {
        mData = data;
        mDataCapacity = desired;
    }

    mDataSize = 0;
    mDataPos = 0;

    return NO_ERROR;
}

status_t Parcel::continueWrite(size_t desired)
{
    if (mData)
    {
        if (desired > mDataCapacity)
        {
            uint8_t *data = (uint8_t *)realloc(mData, desired);
            if (data)
            {
                mData = data;
                mDataCapacity = desired;
            }
            else
            {
                //mError = NO_MEMORY;
                return NO_MEMORY;
            }
        }
        else
        {
            if (mDataSize > desired)
            {
                mDataSize = desired;
            }
            if (mDataPos > desired)
            {
                mDataPos = desired;
            }
        }
    }
    else
    {
        uint8_t *data = (uint8_t *)malloc(desired);
        if (!data)
        {
            //mError = NO_MEMORY;
            return NO_MEMORY;
        }

        mData = data;
        mDataSize = mDataPos = 0;
        mDataCapacity = desired;
    }

    return NO_ERROR;
}

status_t Parcel::readInt32(int32_t *pArg) const
{
    return readAligned(pArg);
}

template <class T>
status_t Parcel::readAligned(T *pArg) const
{
    if ((mDataPos + sizeof(T)) <= mDataSize)
    {
        const void *data = mData + mDataPos;
        mDataPos += sizeof(T);
        *pArg = *reinterpret_cast<const T *>(data);
        return NO_ERROR;
    }
    return NOT_ENOUGH_DATA;
}

status_t Parcel::writeInt32(int32_t val)
{
    return writeAligned(val);
}

template <class T>
status_t Parcel::writeAligned(T val)
{
    if ((mDataPos + sizeof(val)) <= mDataCapacity)
    {
    restart_write:
        *reinterpret_cast<T *>(mData + mDataPos) = val;
        return finishWrite(sizeof(val));
    }
    status_t err = growData(sizeof(val));
    if (err == NO_ERROR)
        goto restart_write;
    return err;
}

status_t Parcel::finishWrite(size_t len)
{
    mDataPos += len;
    if (mDataPos > mDataSize)
    {
        mDataSize = mDataPos;
    }
    return NO_ERROR;
}

status_t Parcel::growData(size_t len)
{
    size_t newSize = ((mDataSize + len) * 3) / 2;
    return (newSize <= mDataSize) ? (status_t)NO_MEMORY : continueWrite(newSize);
}

void Parcel::freeString(const char *str) const
{
    free(const_cast<char *>(str));
}

const char *Parcel::readString() const
{
    int32_t size = readInt32();
    if (size >= 0 && size < INT32_MAX)
    {
        const char16_t *str16 = (const char16_t *)readInplace((size + 1) * sizeof(char16_t));
        if (str16 != NULL)
            return strndup16to8(str16, size);
    }

    return NULL;
}

const void *Parcel::readInplace(size_t len) const
{
    if (len > INT32_MAX)
    {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return NULL;
    }

    if ((mDataPos + pad_size(len)) >= mDataPos &&
        (mDataPos + pad_size(len)) <= mDataSize &&
        len <= pad_size(len))
    {
        const void *data = mData + mDataPos;
        mDataPos += pad_size(len);
        // ALOGV("readInplace Setting data pos of %p to %zu", this, mDataPos);
        return data;
    }
    return NULL;
}

int32_t Parcel::readInt32() const
{
    return readAligned<int32_t>();
}

template <class T>
T Parcel::readAligned() const
{
    T result;
    if (readAligned(&result) != NO_ERROR)
    {
        result = 0;
    }
    return result;
}

status_t Parcel::writeString(const char *str)
{
    size_t s16_len;
    char16_t *str16 = strdup8to16(str, &s16_len);

    if (str16 == NULL)
        return writeInt32(-1);

    status_t err = writeInt32(s16_len);
    if (err == NO_ERROR)
    {
        s16_len *= sizeof(char16_t);
        uint8_t *data = (uint8_t *)writeInplace(s16_len + sizeof(char16_t));
        if (data)
        {
            memcpy(data, str16, s16_len);
            *reinterpret_cast<char16_t *>(data + s16_len) = 0;
            free(str16);
            return NO_ERROR;
        }
    }
    free(str16);
    return err;
}

void *Parcel::writeInplace(size_t len)
{
    const size_t padded = pad_size(len);

    // sanity check for integer overflow
    if (mDataPos + padded < mDataPos)
    {
        return NULL;
    }

    if ((mDataPos + padded) <= mDataCapacity)
    {
    restart_write:
        uint8_t *const data = mData + mDataPos;

        // Need to pad at end?
        if (padded != len)
        {
#if BYTE_ORDER == BIG_ENDIAN
            static const uint32_t mask[4] = {
                0x00000000, 0xffffff00, 0xffff0000, 0xff000000};
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
            static const uint32_t mask[4] = {
                0x00000000, 0x00ffffff, 0x0000ffff, 0x000000ff};
#endif
            *reinterpret_cast<uint32_t *>(data + padded - 4) &= mask[padded - len];
        }

        finishWrite(padded);
        return data;
    }

    status_t err = growData(padded);
    if (err == NO_ERROR)
        goto restart_write;
    return NULL;
}
