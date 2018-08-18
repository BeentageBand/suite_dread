#ifndef POSIX_THREAD_H_
#define POSIX_THREAD_H_
#include <pthread.h>
#include "ccthread.h"

namespace ipc
{
class POSIX_Thread : public cc::Thread::Cbk
{
    private:
    static std::map<pthread_t, Thread * > pthread_pool;
    static std::map<TID_T, Thread * > tid_pool; 
    pthread_t pthread;
    pthread_attr_t pthread_attr;
    public:
    POSIX_Thread(void);
    virtual ~POSIX_Thread(void);

	int register_thread(Thread & thread);
	int create_thread(Thread & thread);
	int cancel_thread(void &* exit);
	int join_thread(void);

    private:
    static void * routine(void * args);
};
}
#endif /*POSIX_THREAD_H_*/