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
#ifndef DREAD_ASSERT_H_
#define DREAD_ASSERT_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_assert_uext.h"
/*=====================================================================================*
 * Standard Includes
 *=====================================================================================*/
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <assert.h>
namespace assert{
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
extern class AssertTrace
{
private:
   std::ostream * ios;
   const std::string trace_type;
public:
   char msg[255];
public:
   explicit AssertTrace(std::ostream & ios, std::string const & type);
   virtual ~AssertTrace(void){};
   void print_trace(const char * file, const int line);
   void ensure(int expr, const char * file, const int line);
   void expect(int expr, const char * file, const int line);
}Notify, Warn, Fault, Ensure;
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#define Tr_Notify(message)                   Trace_Print(  Notify, message);                  assert::Notify.print_trace(__FILE__, __LINE__)
#define Tr_Notify_1(message, v1)             Trace_Print_1(Notify, message, v1);              assert::Notify.print_trace(__FILE__, __LINE__)
#define Tr_Notify_2(message, v1, v2)         Trace_Print_2(Notify, message, v1, v2);          assert::Notify.print_trace(__FILE__, __LINE__)
#define Tr_Notify_3(message, v1, v2, v3)     Trace_Print_3(Notify, message, v1, v2, v3);      assert::Notify.print_trace(__FILE__, __LINE__)
#define Tr_Notify_4(message, v1, v2, v3, v4) Trace_Print_4(Notify, message, v1, v2, v3, v4);  assert::Notify.print_trace(__FILE__, __LINE__)
#define Tr_Warn(message)                     Trace_Print(  Warn,   message);                  assert::Warn.print_trace(  __FILE__, __LINE__)
#define Tr_Warn_1(message, v1)               Trace_Print_1(Warn,   message, v1);              assert::Warn.print_trace(  __FILE__, __LINE__)
#define Tr_Warn_2(message, v1, v2)           Trace_Print_2(Warn,   message, v1, v2);          assert::Warn.print_trace(  __FILE__, __LINE__)
#define Tr_Warn_3(message, v1, v2, v3)       Trace_Print_3(Warn,   message, v1, v2, v3);      assert::Warn.print_trace(  __FILE__, __LINE__)
#define Tr_Warn_4(message, v1, v2, v3, v4)   Trace_Print_4(Warn,   message, v1, v2, v3, v4);  assert::Warn.print_trace(  __FILE__, __LINE__)
#define Tr_Fault(message)                    Trace_Print(  Fault,  message);                  assert::Fault.print_trace( __FILE__, __LINE__)
#define Tr_Fault_1(message, v1)              Trace_Print_1(Fault,  message, v1);              assert::Fault.print_trace( __FILE__, __LINE__)
#define Tr_Fault_2(message, v1, v2)          Trace_Print_2(Fault,  message, v1, v2);          assert::Fault.print_trace( __FILE__, __LINE__)
#define Tr_Fault_3(message, v1, v2, v3)      Trace_Print_3(Fault,  message, v1, v2, v3);      assert::Fault.print_trace( __FILE__, __LINE__)
#define Tr_Fault_4(message, v1, v2, v3, v4)  Trace_Print_4(Fault,  message, v1, v2, v3, v4);  assert::Fault.print_trace( __FILE__, __LINE__)

#define Tr_Ensure(expr, message)                   Trace_Print(  Ensure, message);                 assert::Ensure.ensure(expr, __FILE__, __LINE__);    assert(expr)
#define Tr_Ensure_1(expr, message, v1)             Trace_Print_1(Ensure, message, v1);             assert::Ensure.ensure(expr, __FILE__, __LINE__);    assert(expr)
#define Tr_Ensure_2(expr, message, v1, v2)         Trace_Print_2(Ensure, message, v1, v2, );       assert::Ensure.ensure(expr, __FILE__, __LINE__);    assert(expr)
#define Tr_Ensure_3(expr, message, v1, v2, v3)     Trace_Print_3(Ensure, message, v1, v2, v3);     assert::Ensure.ensure(expr, __FILE__, __LINE__);    assert(expr)
#define Tr_Ensure_4(expr, message, v1, v2, v3, v4) Trace_Print_4(Ensure, message, v1, v2, v3, v4); assert::Ensure.ensure(expr, __FILE__, __LINE__);    assert(expr)

#define Trace_Print(tr, message)                   sprintf(assert::tr.msg, message )
#define Trace_Print_1(tr, message, v1)             sprintf(assert::tr.msg, message , v1)
#define Trace_Print_2(tr, message, v1, v2)         sprintf(assert::tr.msg, message , v1, v2)
#define Trace_Print_3(tr, message, v1, v2, v3)     sprintf(assert::tr.msg, message , v1, v2, v3)
#define Trace_Print_4(tr, message, v1, v2, v3, v4) sprintf(assert::tr.msg, message , v1, v2, v3, v4)
/*=====================================================================================* 
 * api.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
}/*namespace assert*/
#endif /*DREAD_ASSERT_H_*/
