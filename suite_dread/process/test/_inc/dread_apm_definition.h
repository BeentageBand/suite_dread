/*=====================================================================================*/
/**
 * api_set.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_APM_DEFINITIONS_H_
#define DREAD_APM_DEFINITIONS_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "test_stubs.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
namespace apm{
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define APM_THREAD_DEFINTINION_TB \
APM_THREAD(APM_THREAD_ID,     TestDispatch,    DREAD_NULL_THREAD, DREAD_NULL_THREAD, DREAD_NULL_THREAD, DREAD_NULL_THREAD, DREAD_NULL_THREAD) \
APM_THREAD(TEST_THREAD_ID,    TestDispatch,    DREAD_NULL_THREAD, DREAD_NULL_THREAD, DREAD_NULL_THREAD, DREAD_NULL_THREAD, DREAD_NULL_THREAD) \
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
#undef APM_THREAD
#define APM_THREAD(thread, thread_o, dep1, dep2, dep3, dep4, dep5) \
   APM_REGISTERED_##thread,

enum
{
   APM_THREAD_DEFINTINION_TB
   APM_TOTAL_REGISTERED_THREADS
};
/*=====================================================================================* 
 * api_set.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
} /*namespace apm*/
#endif /*DREAD_APM_DEFINITIONS_H_*/
