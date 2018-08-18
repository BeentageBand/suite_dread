#ifndef POSIX_COND_VAR_H_
#define POSIX_COND_VAR_H_

#include "cccond_var.h"
#include "ccmutex.h"

namespace ipc
{
class POSIX_Cond_Var : public cc::Cond_Var::Cbk
{
    private:
    pthread_condattr_t cond_attr;
    pthread_cond_t cond;
    public:
    POSIX_Cond_Var(void);
    virtual ~POSIX_Cond_Var(void);

    bool wait(Mutex & mux, ipc::Clock_T const wait_ms);
    bool signal(void);
};
}
#endif /*POSIX_COND_VAR_H_*/