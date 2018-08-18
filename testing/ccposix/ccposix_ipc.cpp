#include <unistd.h>
#include <pthread.h>
#include "ccposix_ipc.h"
#include "ccposix_thread.h"
#include "ccposix_thread.h"
#include "ccposix_mutex.h"
#include "ccposix_semaphore.h"
#include "ccposix_cond_var.h"

#define IPC_MS_2_SEC (1000)
#define IPC_NS_MS (1000000L)

using namespace ipc;

POSIX::POSIX(void)
: cc::IPC::Cbk()
{}

POSIX::~POSIX(void){}

void POSIX::sleep(ipc::Clock_T const wait_ms)
{
    struct timespec wait_ts = clock_2_timespec(wait_ms);
    nanosleep(wait_ts);
}

Clock_T POSIX::clock(void)
{
    struct timespec now_ts;
    int rc = clock_gettime(CLOCK_MONOTONIC, &now_ts);
    return timepec_2_clock(now_ts);
}

TID_T POSIX::self_thread()
{
    pthread_t self = pthread_self();
    TID_T tid = MAX_TID;

    auto found  = POSIX_Thread::pthread_pool.find(self);
    if(POSIX_Thread::pthread_pool.end() != found)
    {
        tid = found->second;
    }
    return tid;
}

std::shared_ptr<cc::Thread::Cbk> POSIX::create_thread(void)
{
    return std::shared_ptr<cc::Thread::Cbk>(new POSIX_THREAD);
}

std::shared_ptr<cc::Mailbox::Cbk> POSIX::create_mailbox(void)
{
    return std::make_shared<cc::Mailbox::Cbk>(new POSIX_Mailbox);
}

std::shared_ptr<cc::Mutex::Cbk> create_mutex(void)
{
#ifndef __CYGWIN__
    return std::shared_ptr<cc::Mutex::Cbk>(new POSIX_Mutex);
#else
    return std::shared_ptr<cc::Mutex::Cbk>(new Cygwin_Mutex);
#endif
}

std::shared_ptr<cc::Semaphore::Cbk> create_semaphore(void)
{
    return std::shared_ptr<cc::Semaphore::Cbk>(new POSIX_Semaphore);
}

std::shared_ptr<cc::Cond_Var::Cbk> create_cond_var(void)
{
    return std::shared_ptr<cc::Cond_Var::Cbk>(new POSIX_Cond_Var);
}