/*=====================================================================================*/
/**
 * dread.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_H_
#define DREAD_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_applications.h"
#include "dread_events.h"
#include "dread_threads.h"
#include "dread_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#define DREAD dread::Dread::Get_Instance()
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
namespace dread{
class Dread
{
private:
   static Dread * Instance;

public:
   static Dread * Get_Instance(void);

   template<size_t N> bool Subscribe(Event_Id_T (&ev_list)[N]);

   template<size_t N> bool Unsubscribe(Event_Id_T (&ev_list)[N]);

   template<size_t N> const Message & Receive_Message(Event_Id_T (&ev_list)[N], uint32_t tout_ms);
   template<size_t N> const Message & Receive_Message(Event_Id_T (&ev_list)[N]);
   Message & Receive_Message(uint32_t tout_ms);
   Message & Receive_Message(void);

   void Send_Message(const App_Id_T application, const Thread_Id_T thread,
         const Event_Id_T event, BDB_T const & data);

   void Publish_Message(const Event_Id_T event, BDB_T const & data);

private:
   Dread(void);
   virtual ~Dread(void);

   const Message * fetch(void);
   void dump_message(Message const & msg);
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
} /* namespace dread */
/*=====================================================================================* 
 * dread.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*DREAD_H_*/
