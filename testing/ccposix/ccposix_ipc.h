#ifndef  CCPOSIX_IPC_H_
#define  CCPOSIX_IPC_H_

#include <time.h>
#include "ccipc.h"

namespace ipc
{
class POSIX : public cc::IPC::Cbk
{
    public:
    POSIX(void);
    virtual ~POSIX(void);
    void sleep(ipc::Clock_T const wait_ms);
    ipc::Clock_T clock(void);
    ipc::TID_T self_thread(void);
    std::shared_ptr<cc::Thread::Cbk> create_thread(void);
    std::shared_ptr<cc::Mailbox::Cbk> create_mailbox(void);
    std::shared_ptr<cc::Mutex::Cbk> create_mutex(void);
    std::shared_ptr<cc::Semaphore::Cbk> create_semaphore(void);
    std::shared_ptr<cc::Cond_Var::Cbk> create_cond_var(void);
    
};

inline struct timespec clock_2_timespec(Clock_T const & ms)
{
    struct timespce ts;
    ts.tv_sec = static_cast<time_t>(ms / IPC_MS_2_SEC);
    ts.tv_nsec = static_cast<long>(ms) - static_cast<long>(ts.tv_sec * IPC_MS_2_SEC);
    ts.tv_nsec *= IPC_NS_MS;
    return ts;
}

inline Clock_T timespec_2_clock(struct timespec const & ts)
{
    Clock_T ms = static_cast<Clock_T>(ts.tv_sec * IPC_MS_2_SEC) + static_cast<Clock_T>(ts.tv_nsec / IPC_NS_MS);
    return ms;
}

}

#endif /*CCPOSIX_IPC_H_*/