#ifndef __RILC_INTERFACE
#define __RILC_INTERFACE

#include <time.h>

typedef enum
{
    TYPE_INVALID = 0,
    TYPE_STRING,
    TYPE_STRING_ARR,
    TYPE_INT,
    TYPE_INT_ARR,
    TYPE_STRUCT
} response_type;

typedef struct
{
    int num;
    void *data;
} data_array;

typedef struct
{
    /**
     * user data field, user can set the fileld as he will
     * users should distinguish the request by himself
     * value set by user
     */
    void *userdata;
    /**
     * an callback function, notify caller that rilc has finish the request
     * NOTICE:
     *      User should implement an mechenism of notification, by signal or lock, 
     *      anyway, rilc not care, but it should work
     * value set by user
     */
    typedef void notify_(void *);
    notify_ *notify;

    /**
     * response data if have 
     * value set by rilc
     */
    union
    {
        int value_int;
        const char *value_string;
        data_array array;
    } response_data;

    response_type type;

    /**
     * command id, or request id
     */
    int command_id;

    /**
     * error code from rild, refer to rild for more details. notice, this field is valid only in unsocilited response
     * value set by rilc
     */
    int error_code;

    /**
     * the response is unsocilited response?
     * 0 for socilited response
     * 1 for unsocilited response
     * value set by rilc
     */
    int is_unsocilited;

    /* request time, rilc will set the time 
     * value set by rilc
     */
    struct timespec start_time;

    /**
     * request finish time, rilc will set the time when finish
     * value set by rilc
     */
    struct timespec finish_time;
} RILResponse;

#define FIELD_INVALID -1

#endif //__RILC_INTERFACE
