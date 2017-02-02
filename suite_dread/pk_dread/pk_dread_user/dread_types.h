/*=====================================================================================*/
/**
 * dread_types.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_TYPES_H_
#define DREAD_TYPES_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
#include <sstream>
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
namespace dread
{
typedef uint32_t Event_Id_T;
typedef uint32_t Thread_Id_T;
typedef uint32_t App_Id_T;

struct BDB_T
{

};
struct Message
{
public:
   const Event_Id_T  event;
   const Thread_Id_T thread;
   const App_Id_T    application;
   const BDB_T *     data;

private:
   const uint32_t timestamp;

public:

   explicit Message(const Event_Id_T event);

   Message(const Event_Id_T event, const Thread_Id_T thread,
   const App_Id_T application, BDB_T const & data);

   Message(const Event_Id_T event, BDB_T const & data);

   virtual ~Message(void);

};

}/* namespace dread */
/*=====================================================================================* 
 * dread_types.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*DREAD_TYPES_H_*/
