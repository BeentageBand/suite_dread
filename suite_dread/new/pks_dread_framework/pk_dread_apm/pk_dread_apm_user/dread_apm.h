/*=====================================================================================*/
/**
 * api.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_APM_H_
#define DREAD_APM_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "Singleton.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <map>

namespace apm{
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
class ApplicationManager : public Singleton<ApplicationManager, int>
{
public:
   friend class Singleton<ApplicationManager, int>;
private:
   std::map<unsigned long int, int> pthread_to_dread;
public:
   int get_thread_id(void);
   int get_app_id(void);
   int run_application(void);
   virtual ~ApplicationManager(void){};
private:
   ApplicationManager(void);
   ApplicationManager(ApplicationManager const & o){}
   ApplicationManager & operator=(ApplicationManager const & o){ return *this;};
};
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
inline ApplicationManager & Application_Manager(void)
{
   int thread_id = ApplicationManager::Create_Instance(0)->get_thread_id();

   return *ApplicationManager::Create_Instance(thread_id);
}

inline void Activated(void) { Application_Manager(); }
inline void Terminated(void)
{
   int thread_id = ApplicationManager::Create_Instance(0)->get_thread_id();

   ApplicationManager::Destroy_Instance(thread_id);
}
/*=====================================================================================* 
 * api.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
} /* namespace dread*/
#endif /*DREAD_APM_H_*/
