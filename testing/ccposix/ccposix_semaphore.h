#ifndef POSIX_SEMAPHORE_H_
#define POSIX_SEMAPHORE_H_
#include <pthread.h>
#include <semaphore.h>
#include "ccsemaphore.h"

namespace ipc
{
class POSIX_Semaphore : public cc::Semaphore::Cbk
{
    private:
    sem_t sem;
    public:
    explicit POSIX_Semaphore(uint32_t const resources);
    virtual ~POSIX_Semaphore(void);
    bool wait(ipc::Clock_T const wait_ms);
    bool post(void);
};
}
#endif /*POSIX_SEMAPHORE_H_*/