#ifndef POSIX_MUTEX_H_
#define POSIX_MUTEX_H_

#include <pthread.h>
#include "ccmutex.h"

namespace ipc
{
class POSIX_Mutex : public cc::Mutex::Cbk
{
    private:
    pthread_mutex_t mux;
    pthread_mutex_attr_t mux_attr;
    public:
    POSIX_Mutex(void);
    virtual ~POSIX_Mutex(void);

    bool lock(Clock_T const wait_ms);
    bool unlock(void);
};

class Cygwin_Mutex : public cc::Mutex::Cbk
{
    private:
    volatile bool locked;
    pthread_mutex_t mux;
    pthread_mutex_attr_t mux_attr;
    pthread_cond_t cond;
    pthread_contattr_t cond_attr;
    public:
    POSIX_Mutex(void);
    virtual ~POSIX_Mutex(void);

    bool lock(Clock_T const wait_ms);
    bool unlock(void);
};

}

#endif /*POSIX_MUTEX_H_*/