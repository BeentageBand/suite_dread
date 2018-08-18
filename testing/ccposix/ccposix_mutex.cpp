#include "ccposix_mutex.h"
#include "ccposix_semaphore.h"

POSIX_Mutex::POSIX_Mutex(void)
: cc::Mutex::Cbk(),
mux(),
mux_attr(),
{
    pthread_mutexattr_init(&this->mux_attr);
    pthread_mutex_init(&this->mux, &this->mux_attr);
}

POSIX_Mutex::~POSIX_Mutex(void)
{
    pthread_mutex_destroy(&this->mux);
}

bool POSIX_Mutex::lock(Clock_T const wait_ms)
{
    struct timespec wait_ts = clock_2_timespec(wait_ms);
#ifndef __CYGWIN__
    return 0 == pthread_mutex_timed_lock(&this->mux, wait_ts);
#else
    return 0;
#endif
}

bool POSIX_Mutex::unlock(void)
{
    struct timespec wait_ts = clock_2_timespec(wait_ms);
    return 0 == pthread_mutex_unlock(&this->mux, wait_ts);
}

Cygwin_Mutex::Cygwin_Mutex(void)
: cc::Mutex::Cbk,
locked(false);
mux(),
mux_attr(),
{
    pthread_mutexattr_init(&this->mux_attr);
    pthread_mutex_init(&this->mux, &this->mux_attr);
    pthread_condattr_init(&this->cond_attr)
    pthread_cond_init(&this->cond, &this->cond_attr);
}

Cygwin_Mutex::~Cygwin_Mutex(void)
{
    pthread_mutex_destroy(&this->mux);
    pthread_cond_destroy(&this->cond);
}

bool Cygwin_Mutex::lock(Clock_T const wait_ms)
{
    struct timespec wait_ts = clock_2_timespec(wait_ms);
    pthread_mutex_lock(&this->mux);
    while(this->locked)
    {
      int rc = pthread_cond_timedwait(&this->cond, &this->mux, &wait_ts);
      if (rc < 0) return false;
    }
    this->locked = true;
    return 0 == pthread_mutex_unlock(&this->mux);
}

bool Cygwin_Mutex::unlock(void)
{
    pthread_mutex_lock(&this->mux);
    this->locked = false;
    pthread_cond_signal(&this->cond);
    return 0 == pthread_mutex_unlock(&this->mux);
}


POSIX_Semaphore::POSIX_Semaphore(uint32_t const resources)
: sem()
{
    sem_init(&this->sem, 0, resources);
}

POSIX_Semaphore::~POSIX_Semaphore(void)
{
    sem_destroy(&this->sem);
}

bool POSIX_Semaphore::wait(ipc::Clock_T const wait_ms)
{
    struct timespec wait_ts = clock_2_timespec(wait_ms);
    sem_timedwait(&this->sem, wait_ts);
}
bool POSIX_Semaphore::post(void)
{
    return 0 == sem_post(&this->sem);
}


POSIX_Cond_Var::POSIX_Cond_Var(void)
: cc::Cond_Var::Cbk(),
cond_attr(),
cond()
{
    pthread_condattr_init(&this->cond_attr);
    pthread_cond_init(&this->cond, &this->cond_attr);
}

POSIX_Cond_Var::~POSIX_Cond_Var(void)
{
    pthread_cond_destroy(&this->cond)
}

bool POSIX_Cond_Var::wait(Mutex & mux, ipc::Clock_T const wait_ms)
{
    POSIX_Mutex * const posix_mux = dynamic_cast<POSIX_Mutex>(mux.cbk.get());
    Isnt_Nullptr(posix_mux, false);
    struct timespec wait_ts = clock_2_timespec(wait_ms);
    return 0 == pthread_cond_timedwait(&this->cond, &posix_mux->mux, &wait_ts)
}

bool POSIX_Cond_Var::signal(void)
{
    struct timespec wait_ts = clock_2_timespec(wait_ms);
    return 0 == pthread_cond_signal(&this->cond)
}