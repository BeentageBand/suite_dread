/*=====================================================================================*/
/**
 * api.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_assert.h"
#include "dread_threadable.h"
#include "dread_apm_ext.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/
using namespace dread;
/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Definitions

 *=====================================================================================*/
Thread::Thread(const int thread_id)
: dread_id(thread_id)
{
   this->thread_id = 0;
   this->is_alive = false;
   pthread_attr_init(&this->attributes);
}

void Thread::run(void)
{
   Tr_Notify_1("run dread id %d", (int)this->dread_id);
   int created = pthread_create(&this->thread_id, &this->attributes, Thread::thread_func,this);
   Tr_Notify_1("creating thread id %lu", (unsigned long)this->thread_id);

   apm::Register_Thread(this->dread_id, this->thread_id);

   Tr_Ensure_1(0 == created, "pthread not created = %d",created);

   //pthread_detach(this->thread_id);
}

int Thread::join(void)
{
   std::shared_ptr<void *> argc(nullptr);
   int ret = pthread_join(this->thread_id, argc.get());
   argc.reset();
   return ret;
}

int Thread::run_thread(void)
{
   this->is_alive = true;
   int sout = on_thread();
   this->is_alive = false;
   return sout;
}

void Thread::initialize(void)
{
   this->run();
}

void Thread::shutdown(void)
{
   this->join();

}

void * Thread::thread_func(void * argv)
{
   int * sout = new int(-1);
   if(nullptr != argv)
   {
      Thread * t = static_cast<Thread *>(argv);
      *sout = t->run_thread();
   }
   return sout;
}
/*=====================================================================================* 
 * api.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


