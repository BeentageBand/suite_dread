/*=====================================================================================*/
/**
 * dread.cpp
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
#include "dread.h"
#include <stddef.h>
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
using namespace dread;
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
Dread * Dread::Instance  = nullptr;

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static uint32_t Get_Time_Elapsed(void);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
uint32_t Get_Time_Elapsed(void)
{
   return 0;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/


Dread * Dread::Get_Instance(void)
{
   Dread * p_instance = nullptr;
   if(nullptr == Instance)
   {
      Instance = new Dread;
   }
   return p_instance;
}

template<size_t N> bool Dread::Subscribe(Event_Id_T (&ev_list)[N])
{
   return true;
}

template<size_t N> bool Dread::Unsubscribe(Event_Id_T (&ev_list)[N])
{
   return true;
}

template<size_t N> const Message & Dread::Receive_Message(Event_Id_T (&ev_list)[N], uint32_t tout_ms)
{
   Message msg(0);
   return msg;
}

template<size_t N> const Message & Dread::Receive_Message(Event_Id_T (&ev_list)[N])
{
   Message * msg = nullptr;
   do
   {
      this->Receive_Message();
   }while( (nullptr == msg ));

   return &msg;
}
Message & Dread::Receive_Message(uint32_t tout_ms)
{
   Message * msg = nullptr;
   do
   {
      msg = &this->Receive_Message();
   }while( (nullptr == msg) && Get_Time_Elapsed() < tout_ms);

   return  *msg;
}

Message & Dread::Receive_Message(void)
{
   //TODO receive message
   static Message msg(0);
   return msg;
}

void Dread::Send_Message(const App_Id_T application, const Thread_Id_T thread,
      const Event_Id_T event, BDB_T const & data)
{
   Message msg(event, thread, application, data);
   //TODO send message
}

void Dread::Publish_Message(const Event_Id_T event, BDB_T const & data)
{
   Message msg(event, data);
   //TODO imp here

}

Dread::Dread(void){}
Dread::~Dread(void){}
/*=====================================================================================* 
 * dread.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
