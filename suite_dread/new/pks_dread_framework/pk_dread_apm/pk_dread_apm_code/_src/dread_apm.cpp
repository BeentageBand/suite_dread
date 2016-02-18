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
#include "dread_assert.h"
#include "dread_threadable.h"
#include "dread_threads.h"
/**====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <memory>
#include <pthread.h>
#include <set>
using namespace apm;
/**====================================================================================* 
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
   void initialize(void) const;
   void shutdown(void) const;
};

typedef bool (*APMDef_Dependency_T)(APMDefinition const &, APMDefinition const &);
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static bool APM_Def_Compare(APMDefinition const & apm1, APMDefinition const & apm2);
/*=====================================================================================*
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================*
 * Local Object Definitions
 *=====================================================================================*/
static std::set<APMDefinition, APMDef_Dependency_T> APM_Threads_Set( APM_Def_Compare );
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

void APMDefinition::initialize(void) const
{
   this->thread->initialize();
}

void APMDefinition::shutdown(void) const
{
   this->thread->shutdown();
}

bool APM_Def_Compare(APMDefinition const & apm1, APMDefinition const & apm2)
{
   std::set<int>::const_iterator found = apm2.dependencies.find(apm1.thread->dread_id);
   return found != apm2.dependencies.end();
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
#undef APM_THREAD
#define APM_THREAD(thread, thread_o, dep1, dep2, dep3, dep4, dep5) \
      APM_Threads_Set.insert( APMDefinition(apm::Thread_Def_Table[APM_REGISTERED_##thread]) );
ApplicationManager::ApplicationManager(void)
{
   Tr_Notify(__FUNCTION__);
   APM_THREAD_DEFINTINION_TB
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
   std::set<APMDefinition, APMDef_Dependency_T>::iterator it;
   for(it =  APM_Threads_Set.begin(); it != APM_Threads_Set.end(); ++it)
   {
      it->initialize();
   }
   return 0;
}

int ApplicationManager::stop_application(void)
{
   Tr_Notify( __FUNCTION__ );
   std::set<APMDefinition, APMDef_Dependency_T>::iterator it;
   for(it =  APM_Threads_Set.begin(); it != APM_Threads_Set.end(); ++it)
   {
      it->shutdown();
   }
   return 0;
}

void ApplicationManager::register_thread(const int thread, unsigned long int pthread)
{
   this->pthread_to_dread.insert(std::make_pair(pthread, thread));
}

void apm::Register_Thread(const int thread, const unsigned long int pthread)
{
   Application_Manager().register_thread(thread, pthread);
}
/*=====================================================================================* 
 * api.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


