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
#include "dread_apm.h"
#include "dread_apm_ext.h"
#include "dread_threadable.h"
#include "dread_threads.h"
#include "dread_assert.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <map>
#include <memory>
#include <pthread.h>
using namespace apm;
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
class APMDefinition
{
public:
   std::shared_ptr<dread::Thread> thread;
   std::set<int> dependencies;
public:
   explicit APMDefinition(Thread_Def_T const & ap_definition);
   virtual ~APMDefinition(void);
   void initialize(void);
   void shutdown(void);
};

class ThreadKeyDependency
{
public:
   typedef APMDefinition first_argument_type;
   typedef APMDefinition second_argument_type;
   typedef bool result_type;
public:
   bool operator()(const APMDefinition* apm1,const APMDefinition* apm2)
   {
      Tr_Ensure(nullptr == apm1, "ThreadKeyDependency , NULL apm1");
      Tr_Ensure(nullptr == apm2, "ThreadKeyDependency , NULL apm2");
      std::set<int>::const_iterator found = apm2->dependencies.find(apm1->thread->dread_id);
      return found != apm2->dependencies.end();
   }
};
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
 * Local Object Definitions
 *=====================================================================================*/
static ThreadKeyDependency Thread_Dependency;
static std::set<APMDefinition*, ThreadKeyDependency> APM_Threads( apm::Thread_Def_Table,
      apm::Thread_Def_Table + sizeof(apm::Thread_Def_Table)/sizeof(apm::Thread_Def_Table[0]),
            Thread_Dependency );
/*=====================================================================================*
 * Local Function Definitions
 *=====================================================================================*/
APMDefinition::APMDefinition(Thread_Def_T const & ap_definition)
: thread(nullptr),
  dependencies(ap_definition.dependencies, ap_definition.dependencies +
      sizeof(ap_definition.dependencies)/sizeof(ap_definition.dependencies[0]) )
{
   this->thread.reset( Create_Thread(ap_definition.thread) );
}

APMDefinition::~APMDefinition(void)
{
   if(this->thread.unique())
   {
      this->thread.reset();
   }
}

void APMDefinition::initialize(void)
{
   this->thread->initialize();
}
void APMDefinition::shutdown(void)
{
   this->thread->initialize();
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/

ApplicationManager::ApplicationManager(void)
{
   Tr_Notify(__FUNCTION__);
   for(uint8_t i = (DREAD_NULL_THREAD + 1); i < DREAD_TOTAL_THREADS; ++i)
   {
      APM_Threads.insert(new APMDefinition( apm::Thread_Def_Table[i] ));
   }
}

int ApplicationManager::get_thread_id(void)
{
   int thread = -1;
   Tr_Notify(__FUNCTION__);
   if(!this->pthread_to_dread.empty())
   {
      std::map<unsigned long int, int>::iterator found;
      found = this->pthread_to_dread.find(pthread_self());

      if(this->pthread_to_dread.end() != found)
      {
         thread = found->second;
      }
   }
   return thread;
}
int ApplicationManager::get_app_id(void)
{
   return 0;
}

int ApplicationManager::run_application(void)
{
   Tr_Notify( __FUNCTION__ );
   std::set<APMDefinition*, ThreadKeyDependency>::iterator it;
   for(it = APM_Threads.begin(); it != APM_Threads.end(); ++it)
   {
      Tr_Ensure(nullptr != it._M_node, "NULL Thread");
      (*it)->initialize();
   }
   return 0;
}

/*=====================================================================================* 
 * api.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


