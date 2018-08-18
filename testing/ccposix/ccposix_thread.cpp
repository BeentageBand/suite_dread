#include "ccposix_thread.h"

using namespace ipc;

std::map<pthread_t, cc::Thread * > POSIX_Thread::pthread_pool;
std::map<TID_T, cc::Thread * > POSIX_Thread::tid_pool; 

void * POSIX_Thread::routine(void * args)
{
    cc::Thread * const thread = reinterpret_cast<cc::Thread *>(args);
    if(thread)
    {
        thread->run();
    }
    return nullptr;
}

POSIX_Thread(void)
: cc::Thread::Cbk(),
pthread(-1),
pthread_attr()
{
    pthread_attr_init(&this->pthread_attr);
}

~POSIX_Thread(void)
{}

int register_thread(Thread & thread)
{
    POSIX_Thread::tid_pool[thread.tid] = &thread;
}

int create_thread(Thread & thread)
{
    int rc = pthread_create(&this->pthread, 
                        &this->pthread_attr,
                        POSIX_Thread::routine,
                        &thread);
    if(-1 != this->pthread)
    {
        POSIX_Thread::pthread_pool[this->pthread] = &thread;
    }
    return rc;
}

int cancel_thread(void &* exit)
{
    pthread_cancel(this->pthread);
    return this->join_thread();
}

int join_thread(void)
{
    rc = pthread_join(this->pthread, nullptr);
    if(0 == rc)
    {
        POSIX_Thread::pthread_pool.erase(this->pthread);
    }
    return rc;
}
